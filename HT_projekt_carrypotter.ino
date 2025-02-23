/*
  File: 
  Author: Elin Wallgren
  Date: 18/2 - 2025
  Description: a line tracking tranport robot
*/




//including all the libraries
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); //whish letters will be included

//initiates all the global constants and variables
const int sensorPinLeft = 2;
const int sensorPinRight = 4;
const int sensorPinForward = 5;
const int motorPinLeft = 6;
const int motorPinRight = 7;
const int circlePin = 9;

int val;
int number = 1;



/*
  Starting the serial monitor and declares the pinModes to all inputs and outputs
*/
void setup() {

//Startar serial och säger vilket typ av data som ska komma från alla digitala pins
  Serial.begin(9600);
  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinRight, INPUT);
  pinMode(sensorPinForward, INPUT);

  pinMode(motorPinLeft, OUTPUT);
  pinMode(motorPinRight, OUTPUT);

  u8g.setFont(u8g_font_unifont);
}

/*
  Reads the value from the Line Sensors and checks which sensor value is HIGH or LOW. Based on their values, different functions start.
*/

void loop() {

  float valLeft = digitalRead(sensorPinLeft); //Reads the value from each line sensor
  float valRight = digitalRead(sensorPinRight);


  if(valLeft == LOW && valRight == LOW){ //if no sensors are HIGH, the robot drives forward
    forward();
  } else if(valRight == HIGH){ //if the line is to the right, start the function left
    left();
  } else if(valLeft == HIGH){ //if the line if to the left, start the function right
    right();
  } 

  delay(200);
}


/*
  startes the right wheel but not the left one, which turns tha car. To keep driving forward on the line, there is short period of time where bort wheels are driving and then they both stop before the next sensor reading.

*/

void left() {
  Serial.println("Right detected");
  digitalWrite(motorPinRight, HIGH);
  digitalWrite(motorPinLeft, LOW);
  oledWrite(5, 20, "Turning right!");
  delay(300);
  digitalWrite(motorPinRight, HIGH);
  digitalWrite(motorPinLeft, HIGH);
  delay(50);
  digitalWrite(motorPinRight, LOW);
  digitalWrite(motorPinLeft, LOW);
  delay(400);

}

/*
  startes the left wheel but not the right one, which turns tha car. To keep driving forward on the line, there is short period of time where bort wheels are driving and then they both stop before the next sensor reading.

*/

void right() {
  Serial.println("Left detected");
  digitalWrite(motorPinRight, LOW);
  digitalWrite(motorPinLeft, HIGH);
  oledWrite(5, 20, "Turning left!");
  delay(100);
  digitalWrite(motorPinRight, HIGH);
  digitalWrite(motorPinLeft, HIGH);
  delay(50);
  digitalWrite(motorPinRight, LOW);
  digitalWrite(motorPinLeft, LOW);
  delay(400);

}

/*
  startes bort wheels, making the car drive forward and then stops both before the next sensor reading
*/

void forward() {
  Serial.println("Forward march!");
  digitalWrite(motorPinRight, HIGH);
  digitalWrite(motorPinLeft, HIGH);
  oledWrite(5, 20, "Forward march!");
  delay(100);
  digitalWrite(motorPinRight, LOW);
  digitalWrite(motorPinLeft, LOW);
  delay(400);


}


/*
  Writes text to the Oled-screen
  Takes three parameters:
  x = the x-coordinate, where the text should be
  y = the y-coordinate, where the text should be
  String text = what should be written on the screen
  returns text the the oled-screen
*/

void oledWrite(int x, int y, String text){
  u8g.firstPage(); //clears the screen
  do {
    u8g.drawStr(x, y, text.c_str()); //draws the new text
  } while (u8g.nextPage());

  number ++;

}

//skärm funkar ej
//switch?b


