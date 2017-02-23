//www.elegoo.com
//2016.06.13
/************************************************/
#include <Servo.h>
/************************************************/

class ServoExtended
{
  // By Jude Gustafson 2-22-2017
  public:
  Servo servo; //the servo we are extending
  int digPin;      // the pin we are going to put our servo on
  int servoSpeed;     // the speed our servo runs at in milliseconds - the servos we are using take two ms per degree
  int powerSupply;    // I know we are only using one at the moment but this is for later support default to one
  int orientation;                 // current orientation of the servo before we move it
  unsigned long travelTime;   // the computed the in ms that it will take for our servo to get to its destination
 
  
  ServoExtended(int pin, int speedInMS = 2.6, int ps = 1, int orient = 0)
  {
  digPin = pin;
  //servo.attach(digPin);
  //servo.write(0); 
    
  servoSpeed = speedInMS;
  powerSupply = ps;
  
  orientation = orient; 
  travelTime = 0;
  }
 
 
  void attach(int pin)
  {
    servo.attach(pin);
  }
  void write(int goal)
  {
    int destination = (orientation + goal);
    int changeAmount = abs(destination);
    //Serial.println("orientation");
    //Serial.println(orientation);
    //Serial.println("goal");
    //Serial.println(goal);
    //Serial.println("destination");
    //Serial.println(destination);
    servo.write(destination);
    orientation = destination;
    travelTime = (changeAmount * servoSpeed);
  }
};

//Servo myservo;
//Servo myservo3;
//Servo myservo4;

ServoExtended myservo(10);
ServoExtended myservo2(9);
ServoExtended myservo3(8);
ServoExtended myservo4(7);

ServoExtended servoPair1[] = {myservo,myservo3};
ServoExtended servoPair2[] = {myservo2,myservo4};
Servo currentServos[2];
int currentServoIndex = -1;
int servoSpeedInMS = 2;
int startMillis = 0;
long endMillis = 0;
int cascadeLength = 12;
int currentOrientation = 0;
int servoDegreesCascade[] = {
  30, 30, -30, -30, 30, 30, -30, -30, 30, 30, -30, -30};


boolean servosAreMoving = false;

/************************************************/
void setup()
{
  myservo.attach(10);//attachs the servo on pin 9 to servo object
  myservo.servo.write(0);//back to 0 degrees 
//  myservo3.attach(9);//attachs the servo on pin 9 to servo object
//  myservo3.write(0);//back to 0 degrees
//  myservo2.attach(6);//attachs the servo on pin 9 to servo object
//  myservo2.write(0);//back to 0 degrees
  myservo4.attach(7);//attachs the servo on pin 9 to servo object
  myservo4.servo.write(0);//back to 0 degrees
  Serial.begin(9600);
  delay(3000);//wait for a second
}
/*************************************************/
void loop()
{
  
    if (currentServoIndex == -1 || currentServoIndex == cascadeLength) {
      currentServoIndex = 0;
      return;
     }
     
    if(servosAreMoving) {
      if(millis() >= endMillis) {
          servosAreMoving = false;
        }
        return;
      }

      //delay(2000);
    if (currentServoIndex == 0 || currentServoIndex % 2 == 0) {
        moveServo(servoPair1[0], servoDegreesCascade[currentServoIndex]);
        //moveServo(servoPair2[2], servoDegreesCascade[currentServoIndex]);
    }
    else {
        moveServo(servoPair2[1], servoDegreesCascade[currentServoIndex]);
      Serial.println(currentServoIndex);
      Serial.println(servoDegreesCascade[currentServoIndex]);
        //moveServo(servoPair2[3], servoDegreesCascade[currentServoIndex]);
    }

   
    currentServoIndex ++;
    




  
//  myservo.write(45);
//  myservo2.write(45);//goes to 15 degrees 
//  myservo3.write(45);//goes to 15 degrees 
//  delay(500);//wait for a second
//  myservo.write(0);
//  myservo2.write(0);//goes to 30 degrees 
//  myservo3.write(0);//goes to 30 degrees 
//  delay(100);//wait for a second.33
//  myservo.write(90);
//  myservo2.write(90);//goes to 45 degrees
//  myservo3.write(90);//goes to 30 degrees  
//  delay(750);//wait for a second.33
//  myservo.write(0);
//  myservo2.write(0);//goes to 45 degrees 
//  myservo3.write(0);//goes to 30 degrees 
//  delay(100);//wait for a second.33
//  myservo.write(180);
//  myservo2.write(180);//goes to 60 degrees
//  myservo3.write(180);//goes to 30 degrees 
//  delay(1000);//wait for a second.33
}

void moveServo(ServoExtended servo,int goal) {
    
    servosAreMoving = true;
    servo.write(goal);
    if(servo.travelTime + millis() > endMillis) {
    
    //Serial.println("travelTime");
    //Serial.println(servo.travelTime);
      endMillis = millis() + servo.travelTime;
    }
    //delay(1000);
    //delay(333);
}

/**************************************************/

