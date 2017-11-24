#include <SPI.h>
#include <Ethernet.h>
#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 5//pin 10
#define RST_PIN 9
#define SP_PIN 8
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192, 168, 0, 100); 

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

MFRC522 rfid(SS_PIN, RST_PIN);
#include <Servo.h> 
//inicializamos la varible

Servo servoMotor;
MFRC522::MIFARE_Key key;
int cont=1;

void setup() {
    
   //func();
   //delay(300);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  //servoMotor.attach(2);
  ;
  Serial.println("Esta en cero");
       
}

void loop()
{
  Serial.println("entro al loop");
  
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
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
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if(strID=="66:5C:24:7E" || strID=="E5:E3:F0:D1"){
    Serial.print("\nEntre al sector\n");
    cont++;
    Serial.print(cont);
    servoMotor.attach(3);
    //servoMotor2.attach(8);
    /*-----------------------------------------------*/
    if(cont%2==0){
      //si es 1,3,5,7,9
      // Desplazamos a la posición 90º
        servoMotor.write(110);
        //servoMotor2.write(90);
        // Esperamos 1 segu7ndo
        //delay(500);
    }else{
          //si 2,4,6,8,10
          servoMotor.write(0);
          //delay(300);
          //servoMotor2.write(0);
      // Esperamos 1 segundo
          //delay(500);
    }
  //servoMotor.attach(2);
  
      do{
        enviar();
        Serial.println("Con:");
        Serial.println(client.connected());
        Serial.println("loop");
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
          
        }else{
          Serial.println("Se repite");
        }
       
        // if the server's disconnected, stop the client:
        if (!client.connected()) {
          Serial.println();
          Serial.println("DESCONECTANDO");
          Serial.println(client.connected());
          client.stop();
          
        // do nothing forevermore:
        //for(;;)
         // ;
        }
      }while(!client.available());
      servoMotor.attach(0);//no se usan
      //servoMotor2.attach(4);//no se usan
  }else{
      Serial.print("\nAcceso no permitido a esta area\n");
    }
  
   rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  
}


void enviar(){
  //potenciometro=50;
  // start the serial library:
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0){
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(500);
  
 Serial.println("connecting...");
  // if you get a connection, report back via serial:
  //Serial.println(client.connected());
  //do{
  //////////////////////////INICIO DE LA CONECCIÓN A LA BD/////////////////////////////////////
      if (client.connect(server, 8080)){
        Serial.println("-----------------------EXITO---------------");
        Serial.println(client.connected());
        // Make a HTTP request:
        //client.print("GET /tutorial/conexion.php?chipid=123&temperatura=123");
        client.print("GET /tutorial/conexionFinal.php?codigo=1&tac=1");
        //client.print(potenciometro);
        client.println(" HTTP/1.0");
        //client.println("GET /ingenieros/comunicaciones/arduino/ethernet.php HTTP/1.0");
        client.println();
      } 
      else {
        // kf you didn't get a connection to the server:
        Serial.println("----------------------FALLO---------------");
        Serial.println(client.connected());
      }
  //////////////////////////FIN DE LA CONECCIÓN A LA BD/////////////////////////////////////
  delay(500); 
  //}while(!client.connected());   
} 
 
