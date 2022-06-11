/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo base;  // create servo object to control a servo
Servo leftuarm;
Servo rightuarm;
Servo larm;
Servo hand;
// twelvekjmkl servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  base.attach(11);  // attaches the servo on pin 9 to the servo object
  leftuarm.attach(10);
  rightuarm.attach(9);
  larm.attach(6);
  hand.attach(3);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    base.write(pos);              // tell servo to go to position in variable 'pos'
    //leftuarm.write(pos);  
    //rightuarm.write(180-pos);  
    //larm.write(pos);  
    //hand.write(pos);  
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    base.write(pos);              // tell servo to go to position in variable 'pos'
    //leftuarm.write(pos);  
    //rightuarm.write(180-pos);  
    //larm.write(pos);  
    //hand.write(pos);  
    delay(15);                      // waits 15 ms for the servo to reach the position
  }
}
