#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);

int GASA0 = A0;
int gasvalue;

void setup() {
  
                      // initialize thet(); 
 mySerial.begin(9600);
 Serial.begin(9600);
 delay(5000);     
}

void loop() {
  int sensorVal = analogRead(GASA0);
  // int gasvalue=(analogSensor-50)/10;
  int gasVal = map(sensorVal, 0, 1023, 0, 255);
  Serial.println(gasVal);
  // Checks if it has reached the threshold value
  if (gasVal >= 150)
  {
    SendTextMessage();
  }
  delay(500);

}

void SendTextMessage()
{
  Serial.println("Sending SMS...\r");

  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+8801711679545\"\r\n");  // change to the phone number you using
  updateSerial();
  mySerial.println("Gas Leaking!\r\n");//the content of the message
  updateSerial();
  // mySerial.println((char)26);//the stopping character
  Serial.write(0x1a);
  updateSerial();  
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
