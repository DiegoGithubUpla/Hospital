#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);
#include <Servo.h>
 
// Declaramos la variable para controlar el servo
Servo servoMotor;
MFRC522::MIFARE_Key key;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  servoMotor.attach(4);
}
int cont=1;
void loop() {
  Serial.println("entro al loop");
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  Serial.print("Tap card key: ");
  Serial.println(strID);
  if(strID=="66:5C:24:7E"){
    Serial.print("\nEntre al sector\n");
    cont++;
    Serial.print(cont);
    /*-----------------------------------------------*/
    if(cont%2==0){
      //si es 1,3,5,7,9
      // Desplazamos a la posición 90º
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
    }else{
      //si 2,4,6,8,10
      servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
    }
      
  
  
  
  // Desplazamos a la posición 180º
  //servoMotor.write(180);
  // Esperamos 1 segundo
  //delay(1000);
    /*-----------------------------------------------*/
    }else{
      Serial.print("\nAcceso no permitido a esta area\n");
    }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
