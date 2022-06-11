#include <Servo.h>
#include <SoftwareSerial.h>
#define rxPin 11
#define txPin 10
float curr_rotation_angle=0;
Servo base, shoulder1,shoulder2, elbow, wrist;
SoftwareSerial esp32(rxPin, txPin); //tx, rx (trig,echo)

long duration;
float elbow_length = 133.7; //mm
float shoulder_length = 204; //mm
String inputString;
unsigned int HighByte = 0;
unsigned int LowByte  = 0;
unsigned int Len  = 0;

void setup() {
  // put your setup code here, to run once:
  base.attach(9);
  shoulder1.attach(6);
  //shoulder2.attach(11);
  elbow.attach(3);
  wrist.attach(13);

  Serial.begin(9600);
  esp32.begin(9600);
  goto_angle(90,0,10,0);
}

void loop() {
  //extend_arm();
//   digitalWrite(pingPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(pingPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  Serial.print(duration / 29 / 2);
//  Serial.println(" cm");
//  delay(300);
  
  //get_distance2();
  while(esp32.available())
{
    char inChar = (char)esp32.read();
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
  if (rotation_angle==360.0)
  {
    rotation_angle=curr_rotation_angle;
  }
  else
  {
    curr_rotation_angle=rotation_angle;
  }
  Serial.println(shoulder_angle);
  Serial.println(elbow_angle);
  Serial.println(wrist_angle);
  Serial.println(rotation_angle);

  //phi is the "tool angle"
  goto_angle(shoulder_angle,elbow_angle,wrist_angle,rotation_angle);
}

void goto_angle(float shoulder_angle, float elbow_angle, float wrist_angle,float rotation_angle)
{
  shoulder1.write(shoulder_angle);
  delay(15);
  //shoulder2.write(180-shoulder_angle);
  //delay(15);
  elbow.write(elbow_angle);
  delay(15);
  wrist.write(wrist_angle);
  delay(15);
  if (rotation_angle==360)
  {
    rotation_angle=curr_rotation_angle;
  }
  else
  {
    curr_rotation_angle=rotation_angle;
  }
  base.write(rotation_angle);
  delay(15);
}

void extend_arm()
{
  float total_elbow=160;
  float total_shoulder=90;
  float curr_elbow,curr_shoulder;
  float steps=1.0;
  goto_angle(90,0,0,360);
  goto_angle(90,0,0,360);
  goto_angle(90,0,0,360);
  goto_angle(90,0,0,360);
  curr_elbow=0.0;
  curr_shoulder=90.0;
  while(curr_shoulder>=0)
  {
    curr_shoulder=curr_shoulder-steps;
    curr_elbow=curr_elbow+(steps*(total_elbow/total_shoulder));
    goto_angle(curr_shoulder,curr_elbow,45,360);
    Serial.println(calc_length(curr_shoulder,curr_elbow,45)/1);
    //delay(100);
  }
  
}

float calc_length(float shoulder_angle, float elbow_angle, float wrist_angle)
{
 float elbow_offset=-90; //degrees
 return (elbow_length*sin((deg2rad(elbow_angle+elbow_offset))))+
 (shoulder_length*cos(deg2rad(shoulder_angle)));
}


double deg2rad(float deg)
{
 // deg = rad * 57296 / 1000;
  double rad = deg * 1000 / 57296;
  //Serial.println(deg);
  return rad;
}
