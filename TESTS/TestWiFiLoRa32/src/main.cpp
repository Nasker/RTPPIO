#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 17;
IRsend irsend(kIrLed);

const uint32_t codeON = 0xFFE01F;
const uint32_t codeOFF = 0xFF609F;
const uint32_t codeUP = 0xFFA05F;
const uint32_t codeDOWN = 0xFF20DF;

char ssid[] = "CLOTENCSACOLLBATO";
char pass[] = "Xmp13051985!";

WiFiUDP Udp;
const IPAddress outIp(192,168,1,100);
const unsigned int outPort = 9999;  
const unsigned int localPort = 8888;
OSCErrorCode error;

void handleMessage(OSCMessage &msg, int code, String color){
  bool state = msg.getFloat(0)==0;
  digitalWrite(BUILTIN_LED, state);
  if(state){
    Serial.print(color);
    irsend.sendNEC(code);
  }
}

void handleBlueButton(OSCMessage &msg) {
  handleMessage(msg, codeON, "BLUE!");
}

void handleYellowButton(OSCMessage &msg) {
  handleMessage(msg, codeUP, "YELLOW!");
}

void handleRedButton(OSCMessage &msg) {
  handleMessage(msg, codeOFF, "RED!");
}

void handleGreenButton(OSCMessage &msg) {
  handleMessage(msg, codeDOWN, "GREEN!");
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);    // turn *on* led

  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);

  irsend.begin();
}

void loop() {
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      char address[32];
      msg.getAddress(address);
      Serial.printf("Received message %s\n", address);
      msg.dispatch("/1/push1", handleBlueButton);
      msg.dispatch("/1/push2", handleYellowButton);
      msg.dispatch("/1/push3", handleRedButton);
      msg.dispatch("/1/push4", handleGreenButton);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}