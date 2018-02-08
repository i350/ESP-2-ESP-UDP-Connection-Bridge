/**
 * ESP Receiver (ESP8266 AP)
 */


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


const char* ssid = "i350_AP";
const char* password = "for_omar";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets

String message;
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
}


void loop()
{
  if (Serial.available() > 0) {
    // get incoming byte:
    message = Serial.readString();
    Udp.beginPacket(IPAddress(192,168,1,1),localUdpPort);
    Udp.write(message.c_str(),sizeof(message));
    Udp.endPacket();
  }
}
