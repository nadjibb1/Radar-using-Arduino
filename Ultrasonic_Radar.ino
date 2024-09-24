#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Creates a lcd object for controlling the LCD
Servo myServo; // Creates a servo object for controlling the servo motor
const int trigPin = 2; // Define on which pin is the sensor Trig pin attached
const int echoPin = 3; // Define on which pin is the sensor Echo pin attached
const float speedOfSound = 0.0343; // cm/µS
const int maxRange = 400; // cm
const int timeForServoToGetIntoPosition = 500; // mS
const int intervalBetweenDegrees = 1000; // mS
const int intervalBetweenMeasurements = 2000; // mS
const int NUMBER_OF_DEGREES = 5;
int degrees[NUMBER_OF_DEGREES] = {0, 45, 90, 135, 180};
// List of degrees to take measurments for
long duration; // to hold the duration value later
int distance; // to hold the distance value later
void setup()
{
pinMode(trigPin, OUTPUT); // Set up trigPin as output
pinMode(echoPin, INPUT); // Set up echoPin as input
lcd.init(); // Start the LCD
lcd.backlight(); // And turn on the backlight
myServo.attach(5); // Defines on which pin is the servo motor attached
}
void loop() {
for (int i = 0; i < NUMBER_OF_DEGREES; i++) {
// For each degree in the array

myServo.write(degrees[i]); // Turn the servo to the degree
delay(timeForServoToGetIntoPosition); // Wait for Servo to get into position
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
// Read the echoPin, returns the sound wave travel time in microseconds
distance = duration * speedOfSound / 2; // Calculate the distance
// Print the current degree
lcd.setCursor(0, 0);
lcd.print("Degree: ");
lcd.print(degrees[i]);
lcd.print(" ");
// Print the corresponding distance
lcd.setCursor(0, 1);
lcd.print("Distance: ");
lcd.print(distance);
lcd.print(" cm ");
delay(intervalBetweenDegrees);
}
delay(intervalBetweenMeasurements);
}
