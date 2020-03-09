/* 
// Arduino code to make motor run when there is no obstacle and stop when there is one by
// reading ultrasonic sensor input and control the motor driver based on it.
// This is done using HC-SR04 Ultrasonic Sensor and L293D Motor Driver
// April 2019
// Pyrena Luhur
// Tutorial used for code reference:
// https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
// https://www.instructables.com/id/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/
*/

/*
	Arduino Pin connection
	pin 10 - wheel motor, wire 1 
	pin 9 - wheel motor, wire 2

	pin 7 - echo in ultrasonic sensor HC-SR04
	pin 6 - trig in HC-SR04

	5V - VCC in HC-SR04, VCC 5V (16) in motor driver L293D 
	GND - GND in HC-SR04, GND in motor driver L293D 
*/

//L293D Motor Driver Constants
const int motorWheelA = 9;
const int motorWheelB= 10;

//HC-SR04 Ultrasonic Sensor Constants
const int trigPin = 6;
const int echoPin = 7;


long duration;
int distance;
const int distanceThreshold = 40;
const int refreshRate = 100;

//Pin Setup
void setup(){
	//setup motor driver - set pins as outputs
	pinMode(motorWheelA, OUTPUT);
	pinMode(motorWheelB, OUTPUT);

	//setup ultrasonic sensor
	pinMode(trigPin, OUTPUT); //trigPin as Output
	pinMode(echoPin, INPUT);  //echoPin as Input

	//Set baud rate
	Serial.begin(9600);
}


void loop(){
	//Ultrasonic sensor: calculate the distance between sensor and other object
	pollDistance();

	//if real distance is higher than distanceThreshold, let motor run
	if (distance > distanceThreshold){
		//turn motor on
		digitalWrite(motorWheelA, HIGH);
		digitalWrite(motorWheelB, LOW);
		delay(refreshRate);
		//update distance
		pollDistance();
	} else {
		//if real distance is lower or equal than distanceThreshold, stop motor
		digitalWrite(motorWheelA, LOW);
		digitalWrite(motorWheelB, LOW);
	}
}


//Helper functions

//Check the real distance from ultrasonic sensor input
void pollDistance(){
	// Clears the trigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);
	
	// Calculating the distance
	distance = duration * 0.034/2;

	// For testing: Prints the distance on the Serial Monitor
	Serial.print("Distance: ");
	Serial.println(distance);

	return ;
}
