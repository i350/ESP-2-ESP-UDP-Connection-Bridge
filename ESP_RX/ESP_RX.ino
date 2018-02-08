/**
 * ESP Receiver (ESP8266 AP)
 */


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


const char* ssid = "i350_AP";
const char* password = "for_omar";

uint8_t connectedClients=0;
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacekt[] = "Hi there! Got the message :-)";  // a reply string to send back
String decodedMessage;


// Change pins to your application
const uint8_t led = 2;


String decodeMessage(String message)
{
  if (message == "f")
  {
    digitalWrite ( led, LOW );
    return "LED OFF";
  }
  else if (message == "n")
  {
    digitalWrite ( led, HIGH );
    return "LED ON";
  }
  else
  {
    return "Unknown Message";
  }
}
void setup()
{
  pinMode(led,OUTPUT);

  
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Configuring access point (%s) ....  ", ssid);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPConfig(IPAddress(192,168,1,1), IPAddress(192,168,1,1), IPAddress(255,255,255,0)) ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.softAPIP().toString().c_str(), localUdpPort);
}


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    decodedMessage=decodeMessage(incomingPacket);
    Serial.printf("Decoded command: %s\n", decodedMessage.c_str());

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacekt);
    Udp.endPacket();

    
  }

  // Check if new client connected
  if (connectedClients != WiFi.softAPgetStationNum())  
  {
    connectedClients = WiFi.softAPgetStationNum();
    Serial.printf("Stations connected = %d\n", connectedClients);
  }
}
