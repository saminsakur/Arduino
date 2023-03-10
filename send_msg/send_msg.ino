#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

#define sensorPin A0

int sensor_thres = 900;

void setup()
{
  pinMode(sensorPin, INPUT);

  Serial.begin(9600);
  
 
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
}

void loop()
{
  read_sensor();
  delay(100);
}
void read_sensor()
{
  int sensor_val = analogRead(A0);
  Serial.print("Gas Level:");
  Serial.println(sensor_val);
  delay(1000);
  
  // if (sensor_val >= sensor_thres){
  if (1){
    Serial.println("Exceeded Gas Level!");
    send_sms();
  }
}
void send_sms(){
  Serial.println("Sending SMS...");
  mySerial.println("AT+CMGS=\"+8801711679545\""); 
  updateSerial();
  mySerial.print("GAS LEAKAGE DETECTED."); 
  updateSerial();
  mySerial.write(26); 

}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
