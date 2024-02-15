#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(0, 1); // RX, TX

//initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command;

int duration;
int distance;
int safeDistance;
int trig = A0;
int echo = A1;

int BR_LED = A4;
int BL_LED = A3;

int buzzer = A5;

void setup() {
  Serial.begin(9600);

  bluetoothSerial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(buzzer, OUTPUT);  
}

void loop() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration*0.034/2;

  safeDistance = distance;
  Serial.print("Distance");
  Serial.println(distance);
  
  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();

    Stop();

    if(safeDistance <= 15){
      Serial.println("Not safe");
      forward();
      delay(250);
    }
    else{
      switch (command) {
      case 'R': forward(); break;
      case 'L': back(); break;
      case 'B': left(); break;
      case 'F': right(); break;
      } 
    }
  }

  if(safeDistance <= 20){
    digitalWrite(buzzer, HIGH);
    Back_LightON();
    delay(100);
    digitalWrite(buzzer, LOW);
    Back_LightOFF();
  }
}

void Stop()//stop the motor when release the button
{
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0); 
  motor2.run(RELEASE);
  motor3.setSpeed(0); 
  motor3.run(RELEASE); 
  motor4.setSpeed(0);  
  motor4.run(RELEASE); 
}

void forward()//rotate the motor clockwise
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void back()//rotate the motor anti-clockwise 
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
}

void left()//rotate the first 2 anti-clockwise & rotate the last 2 clockwise
{
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void right()//rotate the first 2 clockwise & rotate the last 2 anti-clockwise
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255); 
  motor2.run(FORWARD);  
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255); 
  motor4.run(BACKWARD); 
}

void Back_LightON()
{
  digitalWrite(BR_LED, HIGH);
  digitalWrite(BL_LED, HIGH);
}
void Back_LightOFF()
{
  digitalWrite(BR_LED, LOW);
  digitalWrite(BL_LED, LOW);
}