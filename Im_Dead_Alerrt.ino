/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
//#include "ESP8266WiFiGeneric.h"

//#include "WiFiClient.h"
//#include "WiFiUdp.h"

//#define dns_port 53

IPAddress addrx;

IPAddress dns(8, 8, 8, 8); 

//// A UDP instance to let us send and receive packets over UDP
//WiFiUDP udp;

////void testtx(void);
//void testtx(char* ssid);

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  Serial.println("Setup done");
}
  
void loop() {
  
//  char nets[3][50];
  String nets[3];
  char netc = 0;

//  for (int i =0; i < 3; i++) {
//    for (int j =0; j < 50; j++) {
//      nets[i][j] = 0;
//    }
//  }
  
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  netc = 0;
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      if((WiFi.encryptionType(i) == ENC_TYPE_NONE)&&(netc<3)){
        if(os_strncmp(WiFi.SSID(i).c_str(),"ESP",3)!=0){
  //          sprintf(&nets[netc][0],"%s",WiFi.SSID(i).c_str());
            nets[netc]=WiFi.SSID(i).c_str();
  
    //        Serial.println(nets[netc]);
    //        nets[netc]=(char*)WiFi.SSID(i);
            netc++;
          }
        }
      }
      delay(10);
    }
    
    while(WiFi.scanComplete()==WIFI_SCAN_RUNNING){};
//    WiFi.disconnect();
          Serial.print("Wifi Status:");
          Serial.println(WiFi.status());

    
    Serial.print("networks to txfrom : ");
    Serial.println(netc,DEC);
            delay(1000);

    
    if (netc){
      for (int x =0; x<netc; x++){
//        Serial.println(nets[x]);
//        sprintf(&nams[0],"%s",nets[x]);
////        testtx();
//        testtx(nets[x]);
////        testtx(nets[x]);
          char buff[100]={0,};
          sprintf(buff,"%08x.",ESP.getChipId());
        //  sprintf(buff,"ns.deadbattery.club");
          sprintf(buff+8,".id.deadbattery.club");
          //get a random server from the pool
          Serial.println(buff);
          Serial.println(nets[x]);
          Serial.println(sizeof(nets[x]));
          Serial.println(nets[x]);
          for (int i = 0; i < strlen(nets[x].c_str()); ++i) {
          Serial.printf("%02x ", nets[x].c_str()[i]);
        }
        Serial.println("");
          WiFi.begin(nets[x].c_str());
          while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
          } 
          Serial.println(WiFi.localIP());
          WiFi.config(WiFi.localIP(),WiFi.gatewayIP(),WiFi.subnetMask(),dns);
          WiFi.hostByName(buff, addrx); 
          Serial.println("HOST DNS SENT LOOKUP DONE");
          Serial.println(addrx);
            delay(1000);
          Serial.println(WiFi.status());
          WiFi.disconnect();
          Serial.println(WiFi.status());
          while (WiFi.status() != WL_IDLE_STATUS) {
            delay(500);
            Serial.println(WiFi.status());
          }
          delay(3000);

      }
    }
  Serial.println("");

  // Wait a bit before doing buzz?
  Serial.println("END");
  digitalWrite(2,LOW);
//  pinMode(2,INPUT);
          delay(3000);
  ESP.deepSleep(999 * 1000000,WAKE_RF_DEFAULT);
  
}

//void testtx(){
//  char buff[100]={0,};
//  sprintf(buff,"%08x.",ESP.getChipId());
////  sprintf(buff,"deadbattery.club");
//  sprintf(buff+8,".ns.deadbattery.club");
//  //get a random server from the pool
//  Serial.println(buff);
//  WiFi.begin(&nams[0]);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  } 
//  Serial.println(WiFi.localIP());
//  WiFi.hostByName(buff, addrx); 
//  Serial.println("HOST DNS SENT LOOKUP DONE");
//  Serial.println(addrx);
//    delay(1000);
//  Serial.println(WiFi.status());
//  WiFi.disconnect();
//  Serial.println(WiFi.status());
//  while (WiFi.status() != WL_IDLE_STATUS) {
//    delay(500);
//    Serial.println(WiFi.status());
//  }
//  delay(3000);
//  return;
//}

//void testtx(char* ssid){
//  char buff[100]={0,};
//  sprintf(buff,"%08x.",ESP.getChipId());
////  sprintf(buff,"deadbattery.club");
//  sprintf(buff+8,".ns.deadbattery.club");
//  //get a random server from the pool
//  Serial.println(buff);
//  WiFi.begin(ssid);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  } 
//  Serial.println(WiFi.localIP());
//  WiFi.hostByName(buff, addrx); 
//  Serial.println("HOST DNS SENT LOOKUP DONE");
//  Serial.println(addrx);
//    delay(1000);
//  Serial.println(WiFi.status());
//  WiFi.disconnect();
//  Serial.println(WiFi.status());
//  while (WiFi.status() != WL_IDLE_STATUS) {
//    delay(500);
//    Serial.println(WiFi.status());
//  }
//  delay(3000);
//  return;
//}

//
//void testtx(String ssid){
//  char buff[100]={0,};
//  sprintf(buff,"%08x.",ESP.getChipId());
////  sprintf(buff,"deadbattery.club");
//  sprintf(buff+8,".ns.deadbattery.club");
//  //get a random server from the pool
//  Serial.println(buff);
//  WiFi.begin(ssid.c_str());
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  } 
//  Serial.println(WiFi.localIP());
//  WiFi.hostByName(buff, addrx); 
//  Serial.println("HOST DNS SENT LOOKUP DONE");
//  Serial.println(addrx);
//    delay(1000);
//  Serial.println(WiFi.status());
//  WiFi.disconnect();
//  Serial.println(WiFi.status());
//  while (WiFi.status() != WL_IDLE_STATUS) {
//    delay(500);
//    Serial.println(WiFi.status());
//  }
//  delay(3000);
//  return;
//}

