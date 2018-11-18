#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "ROS_NETWORK";
const char* password = "12345678";

ESP8266WebServer server(80);

const int led = LED_BUILTIN;

const int switch_pin = 15;
long lastRead = 0;
int adcInput = 0;
long nextEvent = 0;

void handleRoot() {
  server.send(200, "text/html", "/set<br>/status<br>/voltage");
}

void handleSet(){
  String time_millis = server.arg("time");
  nextEvent = time_millis.toInt() + millis();
  handleStatus();
  digitalWrite(led, HIGH);
}

void handleStatus(){
  server.send(200, "application/json", "{ \"uptime\": " + String(millis()) +  ", \"next_event\": " + String(nextEvent) +  ", \"voltage\": " + String(adcInput) + " }");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  pinMode(led, OUTPUT);
  pinMode(switch_pin, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/voltage", [](){
    server.send(200, "text/plain", String(adcInput));
  });

  server.on("/status", handleStatus);

  server.on("/set", handleSet);
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){

  if(millis() - 1000 > lastRead){
    lastRead = millis();
    adcInput = analogRead(A0);  
  }

  if(nextEvent > 0 && millis() > nextEvent){
    nextEvent = 0;
    digitalWrite(switch_pin, HIGH);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(switch_pin, LOW);
    digitalWrite(led, LOW);
  }
  
  server.handleClient();
}
