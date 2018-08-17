//Installare la libreria RC4 che ho creato prima

//La carta da passare(dovresti avere come me una Mifare Classic 1K bianca) NON deve essere formattata come NDEF
//La formattazione per i tag NDEF non ci serve assolutamente a nulla. Non so se questo programma funzioni se la carta è formattata
//per le tag NDEF, potrebbe come non potrebbe. Teoricamente, dovrebbe farlo almeno che la key di autenticazione non è stata alterata
//durante la formattazione
//Teoricamente, potremmo cambiare le key di autenticazione standard e utilizzare la protezione già inclusa nelle Mifare
//Praticamente non sono riuscito a trovare un esempio di come cambiare le key usando il modulo NFC, ed in più è un sistema che è stato già hackerato, per cui..

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <RC4.h>

//Definizioni globali
unsigned char FafiRC4Key[] = {0x40, 0xF4, 0x29, 0x92, 0xA2, 0xDB, 0xAA, 0xE1, 0x87, 0x91, 0xA9, 0x11, 0x94, 0x10, 0x5A, 0x5C};
//16 bytes, la lunghezza non è statica e può essere cambiata
//Quando lanceremo il progetto, userò l'AES-256

PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

void costruisciBloccoCarta(unsigned char bloccoCarta[16], int Credito)
{
      memcpy(&bloccoCarta[0], "Alessi", strlen("Alessi")); //strlen("Alessi") = 6, posizioni 0-6 occupate
      *(int*)(&bloccoCarta[6]) = Credito; //4 bytes (sizeof(int) == 4), 6-10 posizioni occupate dal credito
      memcpy(&bloccoCarta[10], "Foroni", strlen("Foroni")); //10-16 occupate dalla keyword Foroni
}

bool verificaIntegritaBloccoCarta(unsigned char bloccoCarta[16], int &Credito)
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

   uint32_t firmwareVersion = nfc.getFirmwareVersion();
   if (!firmwareVersion) 
   {
        Serial.print("Lettore RFID non trovato");
        while (1); 
   }
   nfc.SAMConfig();
}

void loop() 
{
  Serial.println("Scrivere nella console S per scrivere il credito, R per leggerlo.");
  
  while(!Serial.available());

  char operazione = Serial.read();
  if(operazione == 'S')
  {
      Serial.println("Scrivere nella console il credito da caricare");
      
      while(!Serial.available());
      int credito = Serial.parseInt();

      //costruisco il blocco da scrivere nella carta
      unsigned char bloccoDaScrivere[16], bloccoDaScrivereCrittografato[16];
      costruisciBloccoCarta(bloccoDaScrivere, credito);

      //lo encrypto
      RC4(FafiRC4Key, sizeof(FafiRC4Key), bloccoDaScrivere, sizeof(bloccoDaScrivere), bloccoDaScrivereCrittografato);

      Serial.println("Passare la carta sul lettore");
      uint8_t success;
      uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  
      uint8_t uidLength; 
      success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
      if (success) 
      {
          Serial.print("UID della carta strisciata: ");
          nfc.PrintHex(uid, uidLength);
          Serial.println("");
          
		  //Mi autentico(protezione standard miflare) per il blocco 4(i blocchi 0-3 sono riservati alla carta)
          uint8_t MifareClassicCardDefaultKey[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };  
          success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, MifareClassicCardDefaultKey);
          if (success)
          {
		  //Scrivo il blocco 4 (i blocchi sono fatti da 16 bytes ciascuno)
              success = nfc.mifareclassic_WriteDataBlock(4, bloccoDaScrivereCrittografato);
              if(success)
                  Serial.println("Credito scritto con successo!");
              else
                  Serial.println("Errore nello scrivere il credito. Perfavore passa la carta di nuovo sul lettore");
          }
          else
              Serial.println("Errore nell'autenticazione del blocco dov'è presente il credito. Per caso è stata formattata per NDEF?");
      }
      else
          Serial.println("Errore nella lettura della carta");
  }
  else if(operazione == 'R')
  {
      Serial.println("Passare la carta sul lettore");
    
      uint8_t success;
      uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  
      uint8_t uidLength; 
      success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
      if (success) 
      {
            Serial.print("UID della carta strisciata: ");
            nfc.PrintHex(uid, uidLength);
            Serial.println("");
          
            //Mi autentico(protezione standard miflare) per il blocco 4(i blocchi 0-3 sono riservati alla carta)
            uint8_t MifareClassicCardDefaultKey[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };  
            success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, MifareClassicCardDefaultKey);
            if (success)
            {
                unsigned char bloccoCrittografato[16], bloccoDecrittografato[16];
				
				//Leggo il blocco 4
                success = nfc.mifareclassic_ReadDataBlock(4, bloccoCrittografato);
                if(success)
                {
                    //Decrypto il blocco
                    RC4(FafiRC4Key, sizeof(FafiRC4Key), bloccoCrittografato, sizeof(bloccoCrittografato), bloccoDecrittografato);

                    //Verifico la manomissione e mi prendo il credito dal blocco
                    int Credito = 0;
                    if(verificaIntegritaBloccoCarta(bloccoDecrittografato, Credito))
                    {
                        Serial.print("Il credito e' di ");
                        Serial.print(Credito);
                        Serial.println("");
                    }
                    else
                        Serial.println("Credito manomesso!");
                }
                else
                    Serial.println("Errore nel leggere il credito. Perfavore passa la carta di nuovo sul lettore");
            }
            else
                 Serial.println("Errore nell'autenticazione del blocco dov'è presente il credito. Per caso è stata formattata per NDEF?");
      }
      else
          Serial.println("Errore nella lettura della carta");
  }

  
   delay(100);
}
