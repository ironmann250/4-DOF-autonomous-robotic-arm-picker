#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial rangesensor(12, 13); //rx,tx
SoftwareSerial arduino(14, 15); //rx,tx
Servo gripper;
float rotation_angle=0; //starting angle
const int max_length=290; //mm
const int TARGET_LENGTH=42; //mm
unsigned int HighByte = 0;
unsigned int LowByte  = 0;
unsigned int Len  = 0;
String command;
void setup() {
  Serial.begin(115200);
  rangesensor.begin(9600);
  arduino.begin(9600);
  gripper.attach(2);
}

void loop() {
  if (rotate_and_find())
  {
  delay(2000);
  gripper.write(110);
  delay(1000);
  extend_arm();
  }
  delay(500);
  
  
}
int extend_arm()
{
  float total_elbow=160;
  float total_shoulder=90;
  float total_wrist=80;
  float curr_elbow,curr_shoulder,curr_wrist;
  float steps=1.0;
  
  command="90,0,10,360\n"; //or write move_backward()
  delay(1000);
  gripper.write(110); //open 
  delay(500);
  arduino.print(command);
  Serial.println(command);
  
  
  curr_elbow=0.0;
  curr_shoulder=90.0;
  curr_wrist=10.0;
  
  while(curr_shoulder>=0)
  {
    curr_shoulder=curr_shoulder-steps;
    curr_elbow=curr_elbow+(steps*(total_elbow/total_shoulder));
    curr_wrist=curr_wrist+(steps*(total_wrist/total_shoulder));
    
    if (get_distance()>TARGET_LENGTH) //at 40 mm close wrist
    {
      command=String(curr_shoulder)+","+curr_elbow+","+curr_wrist+","+"360\n"; //move wrist open
      arduino.print(command);
    }
    else 
    {
      gripper.write(180); //close
      delay(500);
      command="90,0,10,360\n"; //close wrist
      arduino.print(command);
      Serial.println(command);
      return 1;
    }
    Serial.println(command);
    //delay(200);
  }
  return 0;
}

int get_distance()
{
  rangesensor.flush();
  rangesensor.write(0X55);                           // trig US-100 begin to measure the distance
  delay(100);                                  
  if (rangesensor.available() >= 2)                  // check receive 2 bytes correctly
  {
    HighByte = rangesensor.read();
    LowByte  = rangesensor.read();
    Len  = HighByte * 256 + LowByte;          // Calculate the distance
    if ((Len > 1) && (Len < 10000))
    {
      Serial.print("Distance: ");
      Serial.print(Len, DEC);          
      Serial.println("mm");                  
    }
    else
    {
      Len=10000;
    }
  }
  return Len;  
  }

  int rotate_and_find()
  {
    int mult;
    command="90,0,10,0\n"; //or write move_backward()
    gripper.write(110); //open 
    arduino.print(command);
    Serial.println(command);
    delay(500);
    rotation_angle=0;
//    if (rotation_angle>180)
//    {
//      mult=-1;
//      rotation_angle=180;
//    }
//    if (rotation_angle<0)
//    {
//      mult=1;
//      rotation_angle=0;
//    }
    while(rotation_angle<=180)
     {
       if (get_distance()<=max_length)
       {
         gripper.write(110); //open 
         return 1;
       }
       else
       {
         rotation_angle=rotation_angle+1;
         command=String("90,0,10,")+rotation_angle+"\n"; //or write move_backward()
         arduino.print(command);
         Serial.println(command);
       }
       //delay(100);
      }
      return 0;
  }
  
