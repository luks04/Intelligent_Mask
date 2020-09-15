#include <WebServer.h>
#include <WiFi.h>

const char* ssid = "Write you WiFi SSID";
const char* password = "Write your password if it exists";

String sHistory = String("");

WebServer server(80);

int mqPin = 36;
int mqSignal = 0;

void setup() {
  pinMode(mqPin, INPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Gestionar las distintas consultas o peticiones al servidor local
  server.on("/", handleOnConnect);
  server.on("/encendido", encender);
  server.on("/apagado", apagar);
  server.onNotFound(handle_NotFound);

  server.begin();
  delay(50);
}

void loop()
{
  server.handleClient();
}

void handleOnConnect()
{
  server.send(200, "text/html", SendHTML("white;\"></button></p><br>"));
}

void encender()
{
  mqSignal = analogRead(mqPin);
  sHistory = colorValue(mqSignal) + ";\"></button> &nbsp" + signalValue(mqSignal) + "</p><br>";
  Serial.print(mqSignal); Serial.println(" ppm");
  Serial.println("Tomando datos");
  server.send(200, "text/html", SendHTML(sHistory));
}

void apagar()
{
  Serial.println("Apagado");
  server.send(200, "text/html", SendHTML("white;\"></button></p><br><p>Intelligent Mask Apagada Exitosamente</p>"));
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(String signalMq)
{
  String webPageString = "<!DOCTYPE html>\n<html lang=\"en\">\n\n<head>\n  <meta charset=\"UTF-8\">\n  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n  <title>Intelligent Mask</title>\n\n  <style>\n    #resBox {\n      width: 800px;\n      height: 300px;\n      background-color: white;\n      overflow: scroll;\n      display: inline-block;\n      margin-bottom: 30px;\n    }\n\n    .btn {\n      border: none;\n      color: white;\n      cursor: pointer;\n      border-radius: 8px;\n    }\n\n    .btnIniciar {\n      background-color: #3db824;\n      height: 50px;\n      width: 150px;\n    }\n\n    .btnDetener {\n      background-color: #cf1414;\n      height: 50px;\n      width: 150px;\n    }\n\n    .btnRefresh {\n      background-color: #1580e2;\n      height: 40px;\n      width: 40px;\n    }\n\n    .colorResult {\n      height: 20px;\n      width: 50px;\n      text-align: justify;\n    }\n\n    body {\n      margin: 0px auto;\n      text-align: center;\n      font-family: 'Lato', sans-serif;\n    }\n\n    h1 {\n      font-weight: 300;\n      letter-spacing: 2px;\n      font-size: 48px;\n    }\n\n    h3 {\n      letter-spacing: 1px;\n      font-size: 14px;\n    }\n\n    p {\n      font-size: 20px;\n      text-align: justify;\n    }\n\n    .header {\n      position: relative;\n      text-align: center;\n      background: linear-gradient(60deg, rgba(84, 58, 183, 1) 0%, rgba(0, 172, 193, 1) 100%);\n      color: white;\n    }\n\n    .inner-header {\n      height: 35vh;\n      width: 100%;\n      margin: 0;\n      padding: 0;\n    }\n\n    .flex {\n      display: flex;\n      justify-content: center;\n      align-items: center;\n      text-align: center;\n    }\n\n    .waves {\n      position: relative;\n      width: 100%;\n      height: 15vh;\n      margin-bottom: -7px;\n      /*Fix for safari gap*/\n      min-height: 100px;\n      max-height: 150px;\n    }\n\n    .content {\n      position: relative;\n      height: 20vh;\n      text-align: center;\n      background-color: white;\n    }\n\n    .parallax>use {\n      animation: move-forever 25s cubic-bezier(.55, .5, .45, .5) infinite;\n    }\n\n    .parallax>use:nth-child(1) {\n      animation-delay: -2s;\n      animation-duration: 7s;\n    }\n\n    .parallax>use:nth-child(2) {\n      animation-delay: -3s;\n      animation-duration: 10s;\n    }\n\n    .parallax>use:nth-child(3) {\n      animation-delay: -4s;\n      animation-duration: 13s;\n    }\n\n    .parallax>use:nth-child(4) {\n      animation-delay: -5s;\n      animation-duration: 20s;\n    }\n\n    @keyframes move-forever {\n      0% {\n        transform: translate3d(-90px, 0, 0);\n      }\n\n      100% {\n        transform: translate3d(85px, 0, 0);\n      }\n    }\n\n    @media (max-width: 768px) {\n      .waves {\n        height: 40px;\n        min-height: 40px;\n      }\n\n      .content {\n        height: 30vh;\n      }\n\n      h1 {\n        font-size: 24px;\n      }\n\n      h3 {\n        letter-spacing: 1px;\n        font-size: 14px;\n      }\n\n      p {\n        font-size: 16px;\n        text-align: justify;\n      }\n\n      #resBox {\n\n        width: 300px;\n        height: 300px;\n        background-color: white;\n        overflow: scroll;\n        display: inline-block;\n        margin-bottom: 30px;\n      }\n    }\n  </style>\n\n</head>\n\n<body>\n  <div class=\"header\">\n    <div class=\"inner-header flex\">\n      <path fill=\"#FFFFFF\" stroke=\"#000000\" stroke-width=\"10\" stroke-miterlimit=\"10\" d=\"M57,283\" />\n      <g>\n        <path fill=\"#fff\"\n          d=\"M250.4,0.8C112.7,0.8,1,112.4,1,250.2c0,137.7,111.7,249.4,249.4,249.4c137.7,0,249.4-111.7,249.4-249.4 C499.8,112.4,388.1,0.8,250.4,0.8z M383.8,326.3c-62,0-101.4-14.1-117.6-46.3c-17.1-34.1-2.3-75.4,13.2-104.1\nc-22.4,3-38.4,9.2-47.8,18.3c-11.2,10.9-13.6,26.7-16.3,45c-3.1,20.8-6.6,44.4-25.3,62.4c-19.8,19.1-51.6,26.9-100.2,24.6l1.8-39.7      c35.9,1.6,59.7-2.9,70.8-13.6c8.9-8.6,11.1-22.9,13.5-39.6c6.3-42,14.8-99.4,141.4-99.4h41L333,166c-12.6,16-45.4,68.2-31.2,96.2    c9.2,18.3,41.5,25.6,91.2,24.2l1.1,39.8C390.5,326.2,387.1,326.3,383.8,326.3z\" />\n      </g>\n      </svg>\n      <h1>INTELLIGENT MASK</h1>\n    </div>\n    <h3>2020 | Lucas Patiño</h3>\n    <div>\n      <svg class=\"waves\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" viewBox=\"0 24 150 28\" preserveAspectRatio=\"none\" shape-rendering=\"auto\">\n        <defs>\n          <path id=\"gentle-wave\" d=\"M-160 44c30 0 58-18 88-18s 58 18 88 18 58-18 88-18 58 18 88 18 v44h-352z\" />\n        </defs>\n        <g class=\"parallax\">\n          <use xlink:href=\"#gentle-wave\" x=\"48\" y=\"0\" fill=\"rgba(255,255,255,0.7\" />\n          <use xlink:href=\"#gentle-wave\" x=\"48\" y=\"3\" fill=\"rgba(255,255,255,0.5)\" />\n          <use xlink:href=\"#gentle-wave\" x=\"48\" y=\"5\" fill=\"rgba(255,255,255,0.3)\" />\n          <use xlink:href=\"#gentle-wave\" x=\"48\" y=\"7\" fill=\"#fff\" />\n        </g>\n      </svg>\n    </div>\n  </div>\n  <div class=\"content\">\n    <h1>¡BIENVENIDO!</h1>\n    <button class=\"btn btnIniciar\" onclick=\"turnON()\">INICIAR</button>\n    <button class=\"btn btnDetener\" onclick=\"turnOFF()\">DETENER</button>\n    <br><br>\n    <div>\n      <div id=\"resBox\">\n        <p id=\"p1\"><button class=\"btn colorResult\" style=\"background-color: ";
  webPageString = webPageString + signalMq;
  webPageString = webPageString + "\n      </div>\n    </div>\n  </div>\n\n  <script>\n    var colorAns = document.getElementById(\"p1\").outerHTML.substr(68, 7);\n    if (colorAns == \"#20c712\") {\n      window.alert(\"Calidad del aire: Buena\");\n    } else if (colorAns == \"#ffed00\") {\n      window.alert(\"Calidad del aire: Regular\");\n    } else if (colorAns == \"#ff8a00\") {\n      window.alert(\"¡Atención! Calidad del aire: Mala\");\n    } else if (colorAns == \"#e81414\") {\n      window.alert(\"¡Precaución! Calidad del aire: Muy mala\");\n    }\n\n    function turnON() {\n      window.location.href = \"/encendido\";\n    }\n\n    function turnOFF() {\n      window.location.href = \"/apagado\";\n    }\n  </script>\n</body>\n\n</html>";
  return webPageString;
}

String signalValue(int mqSignal)
{
  String sVal;
  if(mqSignal <= 520){
    sVal = String(mqSignal) + String(" : Calidad del aire: Buena");
  } else if(mqSignal >= 521 && mqSignal <= 610){
    sVal = String(mqSignal) + String(" : Calidad del aire: Regular");
  } else if(mqSignal >= 611 && mqSignal <= 799){
    sVal = String(mqSignal) + String(" : Calidad del aire: Mala");
  } else if(mqSignal >= 800){
    sVal = String(mqSignal) + String(" : Calidad del aire: Muy mala");
  }
  return sVal;
}

String colorValue(int mqSignal)
{
  String colorSignal;
  if(mqSignal <= 520){
    colorSignal = "#20c712";
  } else if(mqSignal >= 521 && mqSignal <= 610){
    colorSignal = "#ffed00";
  } else if(mqSignal >= 611 && mqSignal <= 799){
    colorSignal = "#ff8a00";
  } else if(mqSignal >= 800){
    colorSignal = "#e81414";
  }
  return colorSignal;
}
