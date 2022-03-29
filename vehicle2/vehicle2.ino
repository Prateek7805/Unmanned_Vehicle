#include <WiFi.h>
#include <ESPmDNS.h>
#include<ESPAsyncWiFiManager.h>
#include <WebSocketsServer.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_BMP085.h>
#include <TinyGPS++.h>
#include "webpage.h"
#include "DHT.h"
// called this way, it uses the default address 0x40
#define DHTPIN 27 

#define SERVOMIN  80 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define DHTTYPE DHT11
Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
Servo servoA;
Servo servoB;  
Servo rightServo;
Servo leftServo;
//vars

const int trigPin = 2;
const int echoPin = 5;
const uint8_t mq2 = 32;
const uint8_t mq5 = 33;
const uint8_t esc1 = 25;
const uint8_t esc2 = 26;
const uint8_t servoR = 23;
const uint8_t servoL = 4;
const uint8_t rain = 15;
const uint8_t gpsTx=17;
const uint8_t gpsRx=16;

uint16_t servo0 = 375;
uint16_t servo1 = 80;
uint16_t servo2 = 297;
uint16_t servo3 = 173;



bool grab = 0;
uint8_t SPEED = 0;
uint8_t servoLCount =0;
uint8_t servoRCount = 0;
//ultrasonic
long duration;
int distance;
//gps
float latitude =0.0;
float longitude =0.0;
//MQ
uint16_t mq2Val = 0;
uint16_t mq5Val = 0;
//BMP180
float bmpTemp= 0.0;
float bmpPressure =0.0;
float bmpAltitude =0.0;
//rain
uint16_t rainVal = 0;
//dht11
float h = 0.0;
float t = 0.0;
TinyGPSPlus gps;

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
      stopCar();
    }
    else if(payload[0]=='f'){
      forward();
    }
    else if(payload[0]=='b'){
      backward();
    }
    else if(payload[0]=='l'){
      left();
    }
    else if(payload[0]=='r'){
      right();
    }
    else if(payload[0]=='P'){
      servo0 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      servo0 = map(servo0, 125, 375, 375,125);
      pwm.setPWM(0, 0, servo0);
     // Serial.print("servo0");Serial.println(servo0);
      
    }
    else if(payload[0]=='R'){
      servo1 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      //Serial.print("servo1");Serial.println(servo1);
      pwm.setPWM(1, 0, servo1);
    }
    else if(payload[0]=='Y'){
      servo2 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      
      servo2 = map(servo2, 202, 386, 386,202);
      //Serial.print("servo2");Serial.println(servo2);
      pwm.setPWM(2, 0, servo2); 
    }
    else if(payload[0]=='K'){
      servo3 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      //Serial.print("servo3");Serial.println(servo3);
      pwm.setPWM(3, 0, servo3); 
    }
    else if(payload[0]=='G'){
       grab=!grab;
       uint16_t servo4=400;
       if(grab)
        servo4=200;
      //Serial.print("servo4");Serial.println(servo4);
      pwm.setPWM(4, 0, servo4); 
    }
    else if(payload[0]=='S'){
      uint16_t speed1 = (uint16_t) strtol((const char *)&payload[1], NULL, 10); 
      SPEED = speed1;
    }
  }
}

void setup(void)
{
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(mq2, INPUT);
   pinMode(mq5, INPUT);
   pinMode(rain, INPUT);
   Serial.begin(115200);
   servoA.attach(esc1);
   servoB.attach(esc2);
   rightServo.attach(servoR);
   leftServo.attach(servoL);
   
   AsyncWiFiManager wifiManager(&server,&dns);
   
   wifiManager.autoConnect("vehicle1");

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
  dht.begin();
  bmp.begin();
  Serial2.begin(9600, SERIAL_8N1, gpsRx, gpsTx);
  delay(10);
  stopCar(); 
}

unsigned long t1 = 0;

void loop(void)
{
 websockets.loop();
  while(millis()-t1>2000){
    sendJSON();
    t1=millis();
  }
}



void forward(){
  initRightLeftServo();
  servoA.write(90-SPEED);
  servoB.write(90-SPEED);
  delay(1);
}

void backward(){
  initRightLeftServo();
  servoA.write(90+SPEED);
  servoB.write(90+SPEED);
   delay(1);
}

void left(){
  servoRCount=0;
  if(servoLCount<2)
    servoLCount++;
  if(servoLCount==0){
    rightServo.write(90);
    leftServo.write(90);
  }
  else if(servoLCount==1){
    rightServo.write(120);
    leftServo.write(120);
  }
  else{
    rightServo.write(130);
    leftServo.write(130);
  }
  delay(1);
}

void right(){
  servoLCount =0;
if(servoRCount<2)
    servoRCount++;
  if(servoRCount==0){
    rightServo.write(90);
    leftServo.write(90);
  }
  else if(servoRCount==1){
    rightServo.write(60);
    leftServo.write(60);
  }
  else{
    rightServo.write(50);
    leftServo.write(50);
  }
  delay(1);
}

void stopCar(){
  servoA.write(90);
  servoB.write(90); 
  initRightLeftServo();
  delay(100);
  initServo();
}

void initRightLeftServo(){
  servoLCount =0;
  servoRCount =0;
  rightServo.write(90);
  leftServo.write(90);
}

void initServo(){
  
  for(int i=servo0; i<=375; i++){
    pwm.setPWM(0, 0, i); 
    delay(20);
  }
  servo0 = 375;
  for(int i=servo1; i>=80; i--){
    pwm.setPWM(1, 0, i); 
    delay(20);
  }
  servo1 = 80;
  if(servo2>=297){
  for(int i=servo2; i>=297; i--){
    pwm.setPWM(2, 0, i); 
    delay(20);
    }
  }
  else{
   for(int i=servo2; i<=297; i++){
    pwm.setPWM(2, 0, i); 
    delay(20);
    } 
  }
  servo2=297;

 if(servo3>=173){
  for(int i=servo3; i>=173; i--){
    pwm.setPWM(3, 0, i); 
    delay(20);
    }
  }
  else{
   for(int i=servo3; i<=173; i++){
    pwm.setPWM(3, 0, i); 
    delay(20);
    } 
  }
  servo3 = 173;
}

void sendJSON(){
  getAllVals();
  String JSON ="{";
  JSON+="\"latitude\":"+ String(latitude,6)+",";
  JSON+="\"longitude\":"+ String(longitude,6)+",";
  JSON+="\"mq2\":"+ String(mq2Val)+",";
  JSON+="\"mq5\":"+ String(mq5Val)+",";
  JSON+="\"temp\":"+ String(t)+",";
  JSON+="\"humid\":"+ String(h)+",";
  JSON+="\"pressure\":"+ String(bmpPressure)+",";
  JSON+="\"altitude\":"+ String(bmpAltitude)+",";
  JSON+="\"rain\":"+ String(rainVal)+",";
  JSON+="\"rain\":"+ String(rainVal)+",";
  JSON+="\"distance\":"+ String(distance);
  JSON+="}";
  char JSON_char[JSON.length()+1];
  JSON.toCharArray(JSON_char, JSON.length()+1);
  websockets.broadcastTXT(JSON_char, JSON.length());
 // Serial.println(JSON);
  //send json here
}

void getAllVals(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
 // Serial.print("Distance: ");
 // Serial.println(distance);
  distance= duration*0.034/2;

  
   //Serial.print("Temperature = ");
   bmpTemp =bmp.readTemperature();
 // Serial.print(bmpTemp);
  //Serial.println(" *C");
    
  //Serial.print("Pressure = ");
  bmpPressure = bmp.readPressure();
//  Serial.print(bmpPressure);
  //Serial.println(" Pa");
    
  // Calculate altitude assuming 'standard' barometric 
  // pressure of 1013.25 millibar = 101325 Pascal
 // Serial.print("Altitude = ");
  bmpAltitude = bmp.readAltitude();
 // Serial.print(bmpAltitude);
  //Serial.println(" meters");
  // Read temperature as Celsius (the default)
  h = dht.readHumidity();
  t = dht.readTemperature();
//  Serial.print(F("Humidity: "));
  //Serial.println(h);
 // Serial.print(F("%  Temperature: "));
 // Serial.println(t);
  mq2Val = digitalRead(mq2);
  mq5Val = digitalRead(mq5);
  rainVal = !digitalRead(rain);
 // Serial.print(F("MQ2: "));
  //Serial.println(mq2Val);
 // Serial.print(F("MQ5: "));
 //Serial.println(mq5Val);
  //Serial.print(F("rainVal: "));
  //Serial.println(rainVal);
  bool breakFlag = 0;
  unsigned long t2=millis();
  while(Serial2.available()>0){
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()){
      //Serial.print("Latitude= "); 
      latitude=gps.location.lat();
      longitude=gps.location.lng();
      //Serial.print(latitude, 6);
     // Serial.print(" Longitude= "); 
      //Serial.println(longitude, 6);
      breakFlag = 1;
    }
    if(breakFlag)
      break;
    if(millis()-t2>5000)//timeOut
      break;
  }
}
