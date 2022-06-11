#include <Servo.h>


Servo bases; 
Servo leftuarm;
Servo rightuarm;
Servo larm;
Servo hands;

float l1=176.0;
float l2=133.0;
float a1,a2,a3;
void setup() {
  Serial.begin(9600);
  //bases.attach(10);  
  //leftuarm.attach(11);
  rightuarm.attach(9);
  larm.attach(6);
  //hands.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
 
      inversekinematics(float(176),float(133));
      //Serial.print(i);Serial.print(", ");Serial.print(j);Serial.print(" ,");
      Serial.print(a1);Serial.print(", ");Serial.print(a2);Serial.print("\n");
      rightuarm.write(a1);
      larm.write(a2);
   

}

void inversekinematics(float x, float y)
{
  
  a2=acos((sq(x)+ sq(y) - sq(l1) - sq(l2)) / (2*l1*l2));
  a1=atan(y / x) - atan((l2*sin(a2)) / (l1+ l2*cos(a2)));
  delay(50);
  a1= (a1*180)/PI;
  a1= (a2*180)/PI;
}
