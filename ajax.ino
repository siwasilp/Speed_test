#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80); // 80 is the port number
IPAddress local_IP(192, 168, 43, 9);
IPAddress gateway(192, 168, 43, 100);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
const char* ssid = "00000000";
const char* password = "00000000";

String Website, data, XML, Javascript;
int inc = 0;

void javascriptContent() {
  Javascript = "<SCRIPT>\n";
  Javascript += "var xmlHttp=createXmlHttpObject();\n";
  Javascript += "function createXmlHttpObject(){\n";
  Javascript += "if(window.XMLHttpRequest){\n";
  Javascript += "xmlHttp=new XMLHttpRequest();\n";
  Javascript += "}else{\n";
  Javascript += "xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
  Javascript += "}\n";
  Javascript += "return xmlHttp;\n";
  Javascript += "}\n";
  Javascript += "\n";
  Javascript += "function response(){\n";
  Javascript += "xmlResponse=xmlHttp.responseXML;\n";
  Javascript += "xmldoc = xmlResponse.getElementsByTagName('data');\n";
  Javascript += "message = xmldoc[0].firstChild.nodeValue;\n";
  Javascript += "document.getElementById('div1').innerHTML=message;\n";
  Javascript += "}\n";
  Javascript += "function process(){\n";
  Javascript += "xmlHttp.open('PUT','xml',true);\n";
  Javascript += "xmlHttp.onreadystatechange=response;\n";
  Javascript += "xmlHttp.send(null);\n";
  Javascript += "setTimeout('process()',200);\n";
  Javascript += "}\n";
  Javascript += "</SCRIPT>\n";

}

void WebsiteContent() {
  javascriptContent();

  Website = "<html>\n";
  Website += "<head>\n";
  Website += "<meta name=\"viewport\" content=\"width = device - width, minimum - scale = 0.1\">\n";
  Website += "</head>\n";
  Website += "<body style=\"margin: 0px; background: #111111;\"><img style=\"-webkit-user-select: none;margin: auto;\" src=\"http://192.168.43.4/\" width=\"850px\" height=\"648px\"></body>\n";
  Website += "</body>\n";
  Website += "<iframe allowtransparency=\"true\" style=\"background: #FFF000;\" src=\"http://192.168.43.3/\" width=\"200px\"></iframe>";
  Website += "<iframe allowtransparency=\"true\" style=\"background: #FFF000;\" src=\"http://192.168.43.2/\" width=\"200px\"></iframe>";
  Website += "</body>\n";
  Website += "<style>\n";
  Website += "#div1{\n";
  Website += "width:200px;\n";
  Website += "margin:0 auto;\n";
  Website += "margin-top:50px;\n";
  Website += "font-size:500%;\n";
  Website += "color:powderblue;\n";
  Website += "}\n";
  Website += "</style>\n";
  Website += "<body onload='process()'>";
  Website += "<div id='div1'>" + data + "</div></body></html>";

  Website += Javascript;
  server.send(200, "text/html", Website);
}
void XMLcontent() {

  XML = "<?xml version='1.0'?>";
  XML += "<data>";
  XML += data;
  XML += "</data>";

  server.send(200, "text/xml", XML);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)delay(500);
  WiFi.mode(WIFI_STA);
  Serial.print(WiFi.localIP());
  server.on("/", WebsiteContent);
  server.on("/xml", XMLcontent);
  server.begin();


}

void loop() {
  inc = inc + 1;
  data = (String)inc + " Km/hr";
  server.handleClient();
}
