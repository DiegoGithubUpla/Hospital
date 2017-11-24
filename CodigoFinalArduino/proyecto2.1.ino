#include <SPI.h>
#include <Ethernet.h>
#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 5//pin 10
#define RST_PIN 9
#define SP_PIN 8
////////////////ultra/////////////
  long distancia;
#include <Servo.h>
Servo servoMotorCor;
long tiempo;
const int ledPin=2;
const int ldrPin=A0;
int ldrStatus;
int top;


/////////////////////////////7
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192, 168, 0, 100); 

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

MFRC522 rfid(SS_PIN, RST_PIN);
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
  //servoMotor.attach(3);

  ////////ultra//////////////
    Serial.begin(9600);
  pinMode(4, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
  pinMode(ledPin,OUTPUT);
  pinMode(ldrPin,INPUT);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotorCor.attach(7);
 
  // Inicializamos al ángulo 0 el servomotor
  servoMotorCor.write(0);


  //////////////////////////
       
}

void loop()
{
  Serial.println("entro al loop");
  ////////////ultra////////////

abrirsintac();


  //////////////////////////////
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
        servoMotor.write(0);
        abrircontac();
        //servoMotor2.write(90);
        // Esperamos 1 segu7ndo
        //delay(500);
    }else{
          //si 2,4,6,8,10
          servoMotor.write(110);
          
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
        client.print("GET /tutorial/conexionFinal.php?codigo=1&tac=2");
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

 void abrirsintac(){
    digitalWrite(4,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(4, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo=pulseIn(8, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia= int(0.017*tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");
  if(distancia<6){
      Serial.println("Abrir puerta");
      ////////////////////////////
      for (int i = 180; i > 0; i--){
          // Desplazamos al ángulo correspondiente
          servoMotorCor.write(i);
          // Hacemos una pausa de 25ms
          delay(10);
      }
      ////////////////////////////
      delay(5000);
      ///////////laser//////////
       top=0;
      do{
         ldrStatus=analogRead(ldrPin);
          if(ldrStatus<=300){
            digitalWrite(ledPin,HIGH);
            Serial.println("HAY ALGO EN LA PUERTA,MANTENER PUERTA ABIERTA");
            delay(500);//espero 0,5 sg más
           }else{
              digitalWrite(ledPin,LOW);
              top=1;
              Serial.println("no hay nada en la puerta");
            }
      }while(top==0);     
              Serial.println("Cerrar puerta");
              ////////////////////////////////
              for (int i = 0; i <= 180; i++){
                  // Desplazamos al ángulo correspondiente
                  servoMotorCor.write(i);
                  // Hacemos una pausa de 25ms
                  delay(10);
               }   
              /////////////////////////////////
   }
  delay(100);
  }

  void abrircontac(){
    for (int i = 180; i > 0; i--){
          // Desplazamos al ángulo correspondiente
          servoMotorCor.write(i);
          // Hacemos una pausa de 25ms
          delay(10);
      }
      ////////////////////////////
      delay(5000);
      ///////////laser//////////
       top=0;
      do{
          ldrStatus=analogRead(ldrPin);
          if(ldrStatus<=300){
            digitalWrite(ledPin,HIGH);
            Serial.println("HAY ALGO EN LA PUERTA,MANTENER PUERTA ABIERTA");
            delay(500);//espero 0,5 sg más
           }else{
              digitalWrite(ledPin,LOW);
              top=1;
              Serial.println("no hay nada en la puerta");
           }
      }while(top==0);     
              Serial.println("Cerrar puerta");
              ////////////////////////////////
              for (int i = 0; i <= 180; i++){
                  // Desplazamos al ángulo correspondiente
                  servoMotorCor.write(i);
                  // Hacemos una pausa de 25ms
                  delay(10);
               }   
    }
