
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
  Website += "<body style=\"margin: 0px; background: #0e0e0e;\"><img style=\"-webkit-user-select: none;margin: auto;\" src=\"http://192.168.43.4/\" width=\"810px\" height=\"608px\"></body>\n";
  Website += "</body>\n";
  Website += "<style>\n";
  Website += "#div1{\n";
  Website += "width:1200px;\n";
  Website += "margin:0 auto;\n";
  Website += "margin-top:50px;\n";
  Website += "font-size:400%;\n";
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
