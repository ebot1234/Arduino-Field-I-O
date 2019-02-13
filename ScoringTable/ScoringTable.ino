#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 0, 100, 40);
unsigned int localPort = 8888;
int dataArray[1];
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
int packetSize;

int field_estop = 5;
int red = 8;
int green = 6;
int blue = 9;
int orange = 7;
EthernetUDP Udp;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

  //Setup Input Pins
  pinMode(field_estop, INPUT);//Field Estop

  //Setup Output Pins
  pinMode(green, OUTPUT); //Green
  pinMode(orange, OUTPUT); //Orange
  pinMode(red, OUTPUT); //Red
  pinMode(blue, OUTPUT); //Blue
  
  delay(1500);
}

void loop() {
  packetSize = Udp.parsePacket();

  if(packetSize){
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println(packetBuffer);
    
    IPAddress serverIP(10, 0, 100, 5);
    int serverPort = 9050;

    if(field_estop == HIGH){
      Udp.beginPacket(serverIP, serverPort);
    char reply[] = "Received Data";
    Udp.write(reply);
    Udp.endPacket();
      }
    
    }
  delay(10);
}
