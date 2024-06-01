#include <Servo.h>

Servo servo;
Servo mesafe;

const int trigPin = 16;
const int echoPin = 5;

long duration;
int distance;

#define BLYNK_TEMPLATE_ID "TMPL6II6A2kyc"
#define BLYNK_TEMPLATE_NAME "Akıllı Ev"
#define BLYNK_AUTH_TOKEN "bt3vmG9q6_C8KvbNDuh9J-Su_Y6iGYcf"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int IN1 =0;
const int IN2 = 2;

char ssid[] = "Koçak Family";
char pass[] = "kamerim61";

BLYNK_WRITE(V1){
  int value = param.asInt();
  if (value) {
    digitalWrite(IN1, HIGH);
    delay(5000);
    digitalWrite(IN1 , LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}
BLYNK_WRITE(V4){
  int slider = param.asInt();
  servo.write(slider);
}
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  mesafe.attach(15); 
  servo.attach(4);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop()
{
  for(int i=15;i<=165;i++){  
  mesafe.write(i);
  delay(30);
  distance = calculateDistance();

  for(int i=165;i>15;i--){  
  mesafe.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(duration);

  if(distance<=50){
    servo.write(20);
  }
  else if(distance<=100){
    servo.write(40);
  }
    else if(distance<=130){
    servo.write(60);
  }
    else if(distance<=150){
    servo.write(80);
  }
  
  Blynk.run();
}
  }
}

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;

}
  