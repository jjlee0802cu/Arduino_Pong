int forcePortOne = A1;
int forcePortTwo = A2;
boolean onePressed = false;
boolean twoPressed = false;

int ultraOne = A3;
int ultraTwo = A4;
//Two touch sensors connected to A1, and A2.
//Two ultrasonic sensors connected to A3 and A4.

int userScore1 = 0;
int userScore2 = 0;

void setup() {
  Serial.begin(9600);
}



void loop() {

  if(userScore1 == 10) {
    //User 1 wins, reset and suspend activity
  }

  if(userScore2 == 10) {
    //User 2 wins, reset and suspend activity
  }
  
  int touchVal1 = analogRead(forcePortOne);
  int touchVal2 = analogRead(forcePortTwo); 

  if(!twoPressed){
    if(touchVal1 < 10 && touchVal2 > 10){//Force sensor 2 was pressed
      twoPressed = true;
      onePressed = false;
      Serial.print("two\n");
      //Rotate towards 1
    }
  }
  
  if(!onePressed){
    if(touchVal1 > 10 && touchVal2 < 10){ //Force sensor 1 was pressed
      onePressed = true;
      twoPressed = false;
      Serial.print("one\n");
      //Rotate towards 2
    }
  }
  

  int ultraVal1 = analogRead(ultraOne);
  int ultraVal2 = analogRead(ultraTwo);

  if(ultraVal1 > 0 && ultraVal2 <= 0) {
    userScore1++;
//    onePressed = false;//need to reset the booleans if someone scored
//    twoPressed = false;
  } else if(ultraVal1 <= 0 && ultraVal2 > 0) {
    userScore2++;
//    onePressed = false;//need to reset the booleans if someone scored
//    twoPressed = false;
  }
}
