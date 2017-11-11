#include <WiFiEsp.h> //Libreria para comunicarse facilmente con el modulo ESP01
#include <SoftwareSerial.h> //Libreria para poder emular un puerto serial
SoftwareSerial Serial1(3, 2); // RX | TX
char ssid[] = "matilda2";            // SSID (Nombre de la red WiFi)
char pass[] = "mi24an16die17dia6";        // Contraseña
int status = WL_IDLE_STATUS;     // Estado del ESP. No tocar
String strhost = "192.168.1.40";//o server
String strurl = "/tutorial/conexion.php";
char server[] = "192.168.1.40"; //Servidor al que nos conectaremos
char key[] = "";    //Api key
 
WiFiEspClient client;  //Iniciar el objeto para cliente 
 //////////////////////////////7
boolean conectaTJ;
boolean conectaBD;
int var;
//////////////////////////////////7
void setup()
{
  
  Serial.println("paso por aqui 2");
  Serial.begin(115200);
  Serial1.begin(115200);
  WiFi.init(&Serial1);
 do{
    conectaTJ=true;
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("EL VALOR DE WL_NO_SHIELD ES: ");
      Serial.println(WL_NO_SHIELD);
      Serial.println("Modulo no presente. Reinicie el Arduino y el ESP01 (Quite el cable que va de CH_PD a 3.3V y vuelvalo a colocar)");
      //Loop infinito 
     }else{
      Serial.println("SE HA DETECTADO EL MODULO");
      conectaTJ=false;
     }
 }while(conectaTJ);    
  //Intentar conectar a la red wifi

 do{
    Serial.print("Intentando conectar a la red WiFi: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    Serial.print("lectura:");//2//2//2//2//1 paso
    Serial.println(status);
    client.connected();
}while(status != WL_CONNECTED);


do{
  var=client.connect(server, 8080);
  conectaBD=true;
  if(var==1){
    conectaBD=false;
  }
}while(conectaBD);
  
}
int i;
void loop(){
      String datos="chipid=123&temperatura=123";
//////////////////////////////////BORRAME//////////////////////////////////
 
 for(i=0;i<5;i++){
  client.print(String("POST ") + strurl + " HTTP/1.1" + "\r\n" + 
               "Host: " + strhost + "\r\n" +
               "Accept: */*" + "*\r\n" +
               "Content-Length: " + datos.length() + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
               "\r\n" + datos);
        datos="chipid=12&temperatura=12"; 
 }
                             
               
          delay(10);             
          
          Serial.print("Enviando datos a SQL...");

        

  /*
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  
  }
 */
  //Desconexion
  Serial.println(var);
  if (!client.connected()) {//entra si ocurre un error
    Serial.println();
    Serial.println("Desconectando del servidor...");
    client.stop();
  }
    // Reintentar
    Serial.println();
    Serial.println("Reintentar? <y>/<n>");
    boolean y=false;
    while(y==false)
    {
      String x = Serial.readString();
      x.trim();
      y=(x=="y" ? true : false);
    }
    
  }
   
