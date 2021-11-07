#include <SoftwareSerial.h>
#include <TimeLib.h>

SoftwareSerial bluetooth(0,1);
#define echoPin 13 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 10 //attach pin D3 Arduino to pin Trig of HC-SR04
#define ledPin 6

// defines variables
float timeenter;
float timeleave;
float timeexit;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
float violation = 0;
int state = 1;
int counter = 0;
boolean check = false;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(ledPin,OUTPUT);
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  bluetooth.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  //bluetooth.begin(9600);


}
void loop() {
  boolean close = false;
  int delaytime = 1000;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

    // Clears the trigPin condition
  Serial.print(bluetooth.available());
  if(bluetooth.available() > 0){
    state = bluetooth.read();
  }
   
  
  if(state == '1'){
    if(distance<=100){
     digitalWrite(ledPin,HIGH);
     
     timeenter = millis();
      bluetooth.println("You are NOT social distancing!");
      check = true;
  
     
    }
  
    else{
      digitalWrite(ledPin,LOW);
      close = false;
       timeleave = millis();
       bluetooth.println("You are social distancing, good job!");
   
       
      }
  }
 
  
  else if(state == '0'){
    Serial.println(distance);
  }
  

}
