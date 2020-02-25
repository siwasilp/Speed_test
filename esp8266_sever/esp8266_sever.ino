#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define INTERVAL_MESSAGE1 1000
void print_time(unsigned long time_millis);
unsigned long time_1 = 0;
byte led  = D0;
ESP8266WebServer server(80); // 80 is the port number

const char* ssid = "00000000";
const char* password = "00000000";

String Website, data, XML, Javascript;
int inc = 0;

int echo1 = D6;
int trig1 = D5;

int echo2 = D7;
int trig2 = D8;

long duration , cm;
float xxx, yyy, count, dir = 0;
float length_x = 10;
long u1, u2;
IPAddress local_IP(192, 168, 43, 9);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional


void setup() {
  pinMode(echo1, OUTPUT);
  pinMode(trig1, INPUT);
  pinMode(echo2, OUTPUT);
  pinMode(trig2, INPUT);
  Serial.begin(9600);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)delay(500);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.localIP());
  server.on("/", WebsiteContent);
  server.on("/xml", XMLcontent);
  server.begin();
}
float v, x = 0;
void loop()
{
  get_data();
  data = "[ " + (String)count + " sec ] Speed  " + (String)x + " Km/hr";
  Serial.println(data);
  server.handleClient();
  
}

void print_time(unsigned long time_millis){
    Serial.print("Time: ");
    Serial.print(time_millis/1000);
    Serial.print("s - ");
}
