#include <PWMServo.h>
#include <core/core.h>
 
PWMServo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{
  pinMode(13, OUTPUT);
  Serial.println("Start setup");
  Serial.begin(115200);
  myservo.attach(0);  // attaches the servo on pin 20
  Serial.println("Done setup");
} 
 
 
void loop() 
{
  // myservo.write(90);
  //myservo.write(120);
  //delay(2000);
  //myservo.write(135);
  //delay(2000);
  for(pos = 60; pos < 135; pos += 1)  // goes from 10 degrees to 170 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(30);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 135; pos>=60; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(30);                       // waits 15ms for the servo to reach the position 
  }
}

int main() {
  setup();
  while (1) {
    loop();
  }
}