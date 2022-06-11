#include <Servo.h>

String inputString;
unsigned int HighByte = 0;
unsigned int LowByte  = 0;

Servo base, shoulder, elbow, wrist;
void setup() {
  // put your setup code here, to run once:
  base.attach(9);
  //shoulder1.attach(9);
  shoulder.attach(6);
  elbow.attach(3);
  wrist.attach(13);

  Serial.begin(9600);

}

void loop() {
    while(Serial.available())
{
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar == '\n')
    {
      handle_incoming(inputString);
      Serial.println(inputString);
      inputString = "";
    }
  }
}

void handle_incoming(String inputString)
{
  char receivedChars[inputString.length()];
  for(int i=0;i<inputString.length();i++){
    receivedChars[i] = inputString[i];
  }
  
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(receivedChars,",");      // get the first part - the string
  float shoulder_angle = atoi(strtokIndx); // copy it to messageFromPC
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  float elbow_angle = atoi(strtokIndx);
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  float wrist_angle = atoi(strtokIndx);
  strtokIndx = strtok(NULL, "\n"); // this continues where the previous call left off
  float rotation_angle = atoi(strtokIndx); 
  Serial.println(shoulder_angle);
  Serial.println(elbow_angle);
  Serial.println(wrist_angle);
  Serial.println(rotation_angle);

  //phi is the "tool angle" 
  goto_angle(shoulder_angle,elbow_angle,wrist_angle,rotation_angle);
}

void goto_angle(float shoulder_angle, float elbow_angle, float wrist_angle,float rotation_angle)
{
  shoulder.write(shoulder_angle);
  delay(50);
  //shoulder2.write(180-shoulder_angle);
  //delay(50);
  elbow.write(elbow_angle);
  delay(50);
  wrist.write(wrist_angle);
  delay(50);
  base.write(rotation_angle);
  delay(50);
}
