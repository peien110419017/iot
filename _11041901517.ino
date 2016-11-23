/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "yipei1517";
const char *password = "";

ESP8266WebServer server(80);
char led_status[50];
String webSite;

#define LEDR 5
#define LEDG 4
#define LEDB 14

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}
void buildWeb(){
  
  webSite += "<!DOCTYPE html>";
  webSite += "<head><meta charset = \"utf-8\">";
  webSite += "<title> NodeMCU 網頁測試 </title>";
  webSite += "<style>";
  webSite += "body{background-color:#D1BBFF; font-family: Arial, Helvetica, Sans-Serif; Color: #000088;}";
  webSite += "div{width:500px; text-align: center; margin: 50 auto;}";
  webSite += "</style>";
  webSite += "</head>";
  webSite += "<body>";
  webSite += "<div>";
  webSite += "<h1>RGB LED Control form</h1>";
  webSite += "<p id=\"ledStatus\">You can select a RGB LED color ...</p>";
  webSite += "<form action=\"form1\">";
  webSite += "<input type=\"radio\" id=\"red\" name=\"led\" value=\"red\"><label for=\"red\">Color Red</label>";
  webSite += "<input type=\"radio\" id=\"green\" name=\"led\" value=\"green\"><label for=\"green\">Color Green</label>";
  webSite += "<input type=\"radio\" id=\"blue\" name=\"led\" value=\"blue\"><label for=\"blue\">Color blue</label><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</div>";
  webSite += "</body></html>";
}
void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus(){
  if(server.arg("led") == "red"){
     snprintf(led_status,50,"Now, RGB LED color is red...");
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,LOW);
  }
  else if(server.arg("led") == "green"){
     snprintf(led_status,50,"Now, RGB LED color is green...");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,LOW);
  }
  else if(server.arg("led") == "blue"){
     snprintf(led_status,50,"Now, RGB LED color is blue...");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,HIGH);
  }
server.send (200,"text/html",led_status );
}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  turnoff();
  buildWeb();
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}



/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
/* 
void handleRoot() {
	server.send(200, "text/html", "hello from esp8266!");
}
void handleNotFound() {
  server.send(404, "text/html", "404 Error!");
}


void setup() {
	delay(1000);
	Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  
	Serial.println("");
	Serial.print("Connected to ");
 Serial.println(ssid);
  Serial.print("IP address: ");
	/* You can remove the password parameter if you want the AP to be open. */

/*	server.on("/", handleRoot);
 server.on("/inline", [](){
  server.send(200, "text/html", "This works as well");
  });
 server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
	server.handleClient();
}*/
