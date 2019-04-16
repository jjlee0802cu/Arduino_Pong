int forcePortOne = A1;
int forcePortTwo = A2;
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
  
  touchVal1 = analogRead(forcePortOne);
  touchVal2 = analogRead(forcePortTwo);
  
  if(touchVal1 < 10 && touchVal2 > 10){
    //Rotate towards 1
  } else if(touchVal1 > 10 && touchVal2 < 10){
    //Rotate towards 2
  }

  ultraVal1 = analogRead(ultraOne);
  ultraVal2 = analogRead(ultraTwo);

  if(ultraVal1 > 0 && ultraVal2 <= 0) {
    userScore1++;
  } else if(ultraVal1 <= 0 && ultraVal2 > 0) {
    userScore2++;
  }
}
