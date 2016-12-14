// 使用可變電阻控制 Servo 的旋轉角度
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>
// 引用 Servo Library
#include <Servo.h>

// 建立一個 Servo 物件
Servo myservo;
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define SSID "Xperia Z3_a925"                                   
#define PASS "077226685"     

ESP8266WebServer server(80);

char led_status[200];
char rBuf[50];
char gBuf[50];
char bBuf[50];
String webSite;

#define LEDR 5

void turnoff(){
  digitalWrite(LEDR, LOW);
}
void buildWeb(){
  
  webSite += "<html>";
  webSite+="<head>\n";
  webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>Form Controler</title>\n";
  webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
  webSite+="<script>";
  webSite+="$(document).ready(function(){";
  webSite+="$(\"[type = range]\").change(function(){";
  webSite+="var redval = $(\"#red\").val();";
  webSite+="$(\"#red-text\").text(redval);";
  webSite+="});";
  webSite+="});";
  webSite+="</script>";
  webSite+="</head>\n";
  webSite += "<body>";
  webSite += "<h1>Control form</h1>";
  webSite += "<form action=\"/form1\">";
  webSite += "<p>move : <span id = \"red-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"red\" name=\"R-led\" min=\"0\" max=\"180\" value=\"0\">";

  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</body></html>";
}

void handleRoot(){
  server.send(200,"text/html",webSite);
}

void ColorPicker(){
  int val = server.arg("R-led").toInt();
// val = analogRead(potpin);            // 讀取可變電阻(數值介於 0 到 1023)
  //val = map(val, 0, 1023, 0, 179);     // 把 0 - 1023 的數值按比例縮放為 0 - 180 的數值
  myservo.write(val);                  // 設定 Servo 旋轉角度
  delay(15);                           // 等待 Servo 旋轉指定的位置
  
 


  server.send(200,"text/html",webSite);
}
void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  
  Serial.begin(115200);
  // put your setup code here, to run once:
  turnoff();
  buildWeb();
  WiFi.begin(SSID, PASS); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("/",handleRoot);
  server.on("/form1",ColorPicker);
  server.onNotFound(handleNotFound);
  myservo.attach(5);  // Servo 接在 pin 9
  server.begin();
  Serial.println(WiFi.localIP());  
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
 
}

