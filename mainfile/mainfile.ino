#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

int forcePortOne = A1;
int forcePortTwo = A2;
boolean onePressed = false;
boolean twoPressed = false;
boolean newGamePressed = false;
int forceThresh = 3; //Decreases this to increase sensitivity

const int ultraOnePingPin = 7;
const int ultraOneEchoPin = 6;

int ultraTwo = 2;

int userScore1 = 0;
int userScore2 = 0;
boolean displayScore = false;

boolean isActive = true;
int winner = 0;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  myMotor->setSpeed(100);
}



void loop() {
  if (isActive) {
    playGame();
    //TODO: Move the needed ultrasonic code into the playGame method - Justin
  } else {
    Serial.print("Winner: ");
    Serial.print(winner);
    //WAIT FOR RESET AND RESET BOOLEAN TO PLAY THE GAME AGAIN
  }

  if (newGamePressed) {
    resetData();
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void playGame() {

  //Ultrasonic
  long duration, inches, cm;
  pinMode(ultraOnePingPin, OUTPUT);
  digitalWrite(ultraOnePingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultraOnePingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraOnePingPin, LOW);
  pinMode(ultraOneEchoPin, INPUT);
  duration = pulseIn(ultraOneEchoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (displayScore) {
    dispScore();
    displayScore = false; //This only executes when the score is modified - prevents the score from printing on every function call
  }

  if (userScore1 == 10) {
    winner = 1;
    isActive = false;
    displayScore = true;
    //User 1 wins, reset and suspend activity
  }

  if (userScore2 == 10) {
    winner = 2;
    isActive = false;
    displayScore = true;
    //User 2 wins, reset and suspend activity
  }

  int touchVal1 = analogRead(forcePortOne);
  int touchVal2 = analogRead(forcePortTwo);

  if (!twoPressed) {
    if (touchVal1 < forceThresh && touchVal2 > forceThresh) { //Force sensor 2 was pressed
      twoPressed = true;
      onePressed = false;
      Serial.print("two22222222222222222222222222222222222222\n");
        myMotor->step(170, FORWARD, DOUBLE);

      //Rotate towards 1
    }
  }

  if (!onePressed) {
    if (touchVal1 > forceThresh && touchVal2 < forceThresh) { //Force sensor 1 was pressed
      onePressed = true;
      twoPressed = false;
      Serial.print("one111111111111111111111111111111111111\n");
        myMotor->step(140, BACKWARD, DOUBLE);
      //Rotate towards 2
    }
  }
  
}

void resetData() {
  userScore1 = 0;
  userScore2 = 0;
  isActive = true;
  winner = 0;
  displayScore = false;
}

void dispScore() {
  //Change this to an LED based score later if needed
  Serial.println("Player 1: ");
  Serial.print(userScore1);
  Serial.println("Player 2: ");
  Serial.print(userScore2);
}

/*void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do code here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
  Serial.println("received.");
  // Here's where you can add code.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
  Serial.println("cm");
  ultraOneSent = false;
  }
  }*/

/*
    //Stepper Motor
    Stepper2.step(100, BACKWARD, MICROSTEP);
    Serial.print("single");
    myMotor->step(1000, FORWARD, SINGLE);
    myMotor->step(1000, BACKWARD, SINGLE);

    if(ultraOneSent == false){
     pinMode(ultraOnePingPin, OUTPUT);
    digitalWrite(ultraOnePingPin, LOW);
    digitalWrite(ultraOnePingPin, HIGH);
     digitalWrite(ultraOnePingPin, LOW);
        pinMode(ultraOneEchoPin, INPUT);
        ultraOneSent = true;
      }

      Serial.println(digitalRead(ultraOneEchoPin));

      if(digitalRead(ultraOneEchoPin) == HIGH){
        Serial.println(1098);
        ultraOneSent = false;
      }

      if(ultraOneSent == true){
        echoCheck();
      } else{
        ultraOneSent = true;
        sonar.ping_timer(echoCheck);

      }

      if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
        pingTimer += pingSpeed;      // Set the next ping time.
         // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
      }

      if(ultraVal1 > 0 && ultraVal2 <= 0) {
        userScore1++;
    //    onePressed = false;//need to reset the booleans if someone scored
    //    twoPressed = false;
    //
      } else if(ultraVal1 <= 0 && ultraVal2 > 0) {
        userScore2++;
    //    onePressed = false;//need to reset the booleans if someone scored
    //    twoPressed = false;
      }*/
