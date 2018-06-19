
#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

String UID;

void setup(void) {
  Serial.begin(9600);
  nfc.begin();
}

void loop(void) {
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    /*Serial.println(tag.getTagType());
    Serial.print("UID: "); */
    UID = tag.getUidString();
    UID.trim();//elimino gli spazi
    Serial.println(UID);
    
  }
  delay(5000);
}
