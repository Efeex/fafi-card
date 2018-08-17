//Installare la libreria RC4 presente nella directory fafi-card / nfc_prove

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <RC4.h>
#include <NfcAdapter.h>

//Definizioni globali
#define DIMENSIONE_MESSAGGIO_NDEF 16


unsigned char FafiRC4Key[] = {0x40, 0xF4, 0x29, 0x92, 0xA2, 0xDB, 0xAA, 0xE1, 0x87, 0x91, 0xA9, 0x11, 0x94, 0x10, 0x5A, 0x5C};
//16 bytes, la lunghezza non è statica e può essere cambiata
//TODO: Key dipendente dall'UUID della carta per prevenire la copia del credito di una carta all'altra

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);  // Indicates the Shield you are using

void costruisciMessaggioNdef(unsigned char messaggioNdef[DIMENSIONE_MESSAGGIO_NDEF], int Credito)
{
      memcpy(&messaggioNdef[0], "Alessi", strlen("Alessi")); //strlen("Alessi") = 6, posizioni 0-6 occupate
      *(int*)(&messaggioNdef[6]) = Credito; //4 bytes (sizeof(int) == 4), 6-10 posizioni occupate dal credito
      memcpy(&messaggioNdef[10], "Foroni", strlen("Foroni")); //10-16 occupate dalla keyword Foroni
}

char GetCharHexLow(unsigned char c)
{
  return "0123456789ABCDEF"[0x0F & c];
}

char GetCharHexHigh(unsigned char c)
{
  return "0123456789ABCDEF"[(0xF0 & c) >> 4];
}

unsigned char Char2Hex(char hexDigit)
{
  hexDigit = toupper(hexDigit);
  return (hexDigit >= 'A') ? hexDigit - 'A' + 10 : hexDigit - '0';
}

void GetCharsFromHex(unsigned char* hex, char* string, int len)
{
  for (int i = 0, j = 0; i < len; i++, j += 2)
  {
    string[j] = GetCharHexHigh(hex[i]);
    string[j + 1] = GetCharHexLow(hex[i]);
  }
}

void GetHexFromChars(char* string, unsigned char* hex, int len)
{
  for (int i = 0, j = 0; i < len; i++, j += 2)
  {
    unsigned char hexHigh = Char2Hex(string[j]);
    unsigned char hexLow = Char2Hex(string[j + 1]);

    hex[i] = (unsigned char)(hexLow + (hexHigh << 4));
  }
}

bool verificaIntegritaMessaggioNdef(unsigned char bloccoCarta[DIMENSIONE_MESSAGGIO_NDEF], int &Credito)
{
    if(memcmp(&bloccoCarta[0], "Alessi", strlen("Alessi")) == 0 &&
       memcmp(&bloccoCarta[10], "Foroni", strlen("Foroni")) == 0)
    {
        Credito = *(int*)(&bloccoCarta[6]);
        return true;
    }
    return false;
}

void setup() 
{
   Serial.begin(9600);
   nfc.begin();
}

void loop() 
{
  Serial.println("Scrivere nella console S per scrivere il credito, R per leggerlo.");

  //Aspetto fino a che non viene scritta una risposta
  while(!Serial.available());

  //La leggo
  char operazione = Serial.read();
  if(operazione == 'S')
  {
      Serial.println("Scrivere nella console il credito da caricare");

      //Aspetto una risposta
      while(!Serial.available());
      
      //Leggo l'intero(TODO: parseInt è lento, meglio leggere carattere e convertirlo manualmente
      int credito = Serial.parseInt();

      //Costruisco il blocco da scrivere nella carta
      unsigned char messaggioNdef[DIMENSIONE_MESSAGGIO_NDEF], messaggioNdefCrittografato[DIMENSIONE_MESSAGGIO_NDEF];
      costruisciMessaggioNdef(messaggioNdef, credito);

      //Lo encrypto
      RC4(FafiRC4Key, sizeof(FafiRC4Key), messaggioNdef, sizeof(messaggioNdef), messaggioNdefCrittografato);

      //Lo trasformo in una stringa di caratteri che rappresenta i byte in hex
      char messaggioNdefHex[(DIMENSIONE_MESSAGGIO_NDEF * 2)/*ogni byte viene rappresentato con 2 caratteri*/ + 1/*terminatore stringa*/] = {0};
      GetCharsFromHex(messaggioNdefCrittografato, messaggioNdefHex, DIMENSIONE_MESSAGGIO_NDEF);

      Serial.println("Passare la carta sul lettore");
      
      //Aspetto la lettura della carta
      //boolean success = false;

      //while(!success)
      //{
          if (nfc.tagPresent())
          {
              NdefMessage message = NdefMessage();
              message.addTextRecord(messaggioNdefHex, ""); //Uso la funzione addTextRecord della libreria diretta, in modo tale da specificare no encoding
              boolean success = nfc.write(message);
              if(success)
                  Serial.println("Credito scritto con successo!");
              else
                  Serial.println("Errore nello scrivere il credito. Perfavore passa la carta di nuovo sul lettore");
          }
      //}
  }
  else if(operazione == 'R')
  {
     Serial.println("Passare la carta sul lettore");
     if (nfc.tagPresent())
     {
          NfcTag tag = nfc.read();
          if (tag.hasNdefMessage()) // If your tag has a message
          {
               NdefMessage message = tag.getNdefMessage();

               if(message.getRecordCount() == 1)
               {
                   NdefRecord record = message.getRecord(0); //Il credito è al record 0

                   //Leggo il messaggio ndef
                   int payloadLength = record.getPayloadLength();
                   byte payload[payloadLength];
                   record.getPayload(payload);

                   //payload[0] contiene la length del nome dell'encoder. Siccome il nostro encoder è "", payload[0] = 0x00
                   byte messaggioNdef[DIMENSIONE_MESSAGGIO_NDEF];
                   char* payload_inizio = (char *)&payload[1]; //Per la ragione scritta prima, il nostro payload inizia a payload[1]
                   //Converto da stringa ad array di byte
                   GetHexFromChars(payload_inizio, messaggioNdef, DIMENSIONE_MESSAGGIO_NDEF);
 
                   //Decrypto il blocco
                   byte messaggioNdefDecrittografato[DIMENSIONE_MESSAGGIO_NDEF];
                   RC4(FafiRC4Key, sizeof(FafiRC4Key), messaggioNdef, sizeof(messaggioNdef), messaggioNdefDecrittografato);

                   //Verifico l'integrità del credito e lo scrivo
                   int Credito;
                   if(verificaIntegritaMessaggioNdef(messaggioNdefDecrittografato, Credito))
                   {
                        Serial.print("Il credito e' di: ");
                        Serial.println(Credito);
                   }
                   else
                       Serial.println("Credito manomesso!");
               }
               else
                   Serial.println("Carta manomessa!");
          }
          else
              Serial.println("Nella carta non vi è credito!");
     }
  }
}
