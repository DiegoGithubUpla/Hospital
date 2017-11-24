long distancia;
#include <Servo.h>
Servo servoMotorCor;
long tiempo;
const int ledPin=2;
const int ldrPin=A0;
int ldrStatus;
int top;
void setup(){
  Serial.begin(9600);
  pinMode(4, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
  pinMode(ledPin,OUTPUT);
  pinMode(ldrPin,INPUT);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotorCor.attach(7);
 
  // Inicializamos al ángulo 0 el servomotor
  servoMotorCor.write(0);
}

void loop(){
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
      for (int i = 0; i <= 180; i++)
  {
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
              for (int i = 180; i > 0; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotorCor.write(i);
    // Hacemos una pausa de 25ms
    delay(10);
  }

              /////////////////////////////////
          }
  
  
  delay(100);
}
