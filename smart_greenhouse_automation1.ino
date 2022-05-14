#include <LiquidCrystal.h> 

LiquidCrystal lcd(7,6,5,4,3,2); 

#define trigger 12
#define echo 13

int tempsensor= A0;      
int photoresistor= A1;   
int sensorValue = 0;
char degree = 176;
long duration;
int distance; 

//acuators
int led =8;        
int ventilator=9;   
int bulb =10;        

void setup()
 {
  // initialize serial communication:
  Serial.begin(9600);
  lcd.begin(16,2);
  //outputs
  pinMode(led, OUTPUT);
  pinMode(ventilator, OUTPUT);
  pinMode(bulb, OUTPUT);
  pinMode(trigger, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echo, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  //inputs
  pinMode(photoresistor, INPUT);
  pinMode(tempsensor,INPUT);
}

void loop() {

  ///////////////temperature sensor
  
 int tmp = analogRead(tempsensor);//Reading data from the sensor.This voltage is stored as a 10bit number.
  float voltage = (tmp * 5.0)/1024;//(5*temp)/1024 is to convert the 10 bit number to a voltage reading.
  float milliVolt = voltage * 1000;//This is multiplied by 1000 to convert it to millivolt.
  float tmpCel =  (milliVolt-500)/10 ;//For TMP36 sensor. Range(−40°C to +125°C)
    
    lcd.setCursor(0,1);
    lcd.print("TEMP:");
  lcd.setCursor(6,1);
    lcd.print(tmpCel);

  if(tmpCel>28)
  {
    digitalWrite(ventilator,HIGH);
    delay(1000);
    digitalWrite(ventilator,LOW);
 
    lcd.setCursor(0,0);
   lcd.print(" VEN 1");
  }
  else{
    digitalWrite(ventilator,LOW); 
          lcd.setCursor(0,0);
   lcd.print(" VEN 0");
  }
  
  /////////////// LDR sensor code
  sensorValue = analogRead(photoresistor);  
 if(sensorValue<=511) 
 {
   digitalWrite(bulb,HIGH);

 }
  else {
    digitalWrite(bulb, LOW);

  }
  
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance <= 20)
  {
    digitalWrite(led,HIGH);
    lcd.setCursor(8,0);
   lcd.print("MOTOR 1");
  }
else
  {
digitalWrite(led,LOW);
  lcd.setCursor(8,0);
   lcd.print("MOTOR 0");
}
 //lcd.clear();
 //lcd.print("Distance:");
 //lcd.print(distance);
 //lcd.print("cm");
// lcd.setCursor(0,1);
 //lcd.print("Distance:");
 //lcd.print(distance/100);
 //lcd.print("m");
 delay(1000);
}