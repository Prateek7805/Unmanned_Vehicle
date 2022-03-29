#include <WiFi.h>
#include <ESPmDNS.h>
#include<ESPAsyncWiFiManager.h>
#include <WebSocketsServer.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "webpage.h"
// called this way, it uses the default address 0x40


#define SERVOMIN  80 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Servo myservo;  
uint8_t pin_led =12;


AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);
DNSServer dns;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
   if(type == WStype_TEXT){
    if(payload[0]=='s'){
      
    }
    else if(payload[0]=='f'){
      
    }
    else if(payload[0]=='b'){
      
    }
    else if(payload[0]=='l'){
      
    }
    else if(payload[0]=='r'){
      
    }
    else if(payload[0]=='P'){
      uint16_t servo0 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      Serial.print("servo0");Serial.println(servo0);
      pwm.setPWM(0, 0, servo0); 
    }
    else if(payload[0]=='R'){
      uint16_t servo1 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      Serial.print("servo1");Serial.println(servo1);
       pwm.setPWM(1, 0, servo1); 
    }
    else if(payload[0]=='Y'){
      uint16_t servo2 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      Serial.print("servo2");Serial.println(servo2);
      pwm.setPWM(2, 0, servo2); 
    }
    else
    for(int i = 0; i<length; i++){
       Serial.print((char)payload[i]);
      Serial.println();
    }
   Serial.printf("Command: %c",payload[0]);
  }
}

void setup(void)
{
  
   Serial.begin(115200);
   AsyncWiFiManager wifiManager(&server,&dns);
   myservo.attach(pin_led);
    wifiManager.autoConnect("vehicle1","12345678");

  server.on("/", [](AsyncWebServerRequest * request)
  { 
    request->send_P(200, "text/html", mainPage);
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}


void loop(void)
{
 websockets.loop();
 if(Serial.available() > 0){
    char c[] = {(char)Serial.read()};
    websockets.broadcastTXT(c, sizeof(c));
  } 
}
