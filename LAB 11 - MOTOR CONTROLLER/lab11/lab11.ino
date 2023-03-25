#define A 6
#define B 5
#define C 2
#define D 3
#define E 4
#define FF 7
#define G 8
#define DP 9 // mode
#define common_cathode 0
#define common_anode 1
bool segMode = common_cathode; // set this to your segment type, my segment is common_cathode
int seg[] {A, B, C, D, E, FF, G, DP}; // segment pins
byte chars = 35; // max value in the array "Chars"
byte Chars[11][9] {
  {'0', 1, 1, 1, 1, 1, 1, 0, 0}, //0
  {'1', 0, 1, 1, 0, 0, 0, 0, 0}, //1
  {'2', 1, 1, 0, 1, 1, 0, 1, 0}, //2
  {'3', 1, 1, 1, 1, 0, 0, 1, 0}, //3
  {'4', 0, 1, 1, 0, 0, 1, 1, 0}, //4
  {'5', 1, 0, 1, 1, 0, 1, 1, 0}, //5
  {'6', 1, 0, 1, 1, 1, 1, 1, 0}, //6
  {'7', 1, 1, 1, 0, 0, 0, 0, 0}, //7
  {'8', 1, 1, 1, 1, 1, 1, 1, 0}, //8
  {'9', 1, 1, 1, 1, 0, 1, 1, 0}, //9
  {'a', 1, 1, 1, 0, 1, 1, 1, 0}, //A/10
};

int enA = 11;
int in1 = 10;
int in2 = 12;
const int buttonIncrease = A0;
const int buttonDecrease = A1;
int buttonIncState = 0;
int buttonDecState = 0;
int incFlag = 0;
int decFlag = 0;
int pressed = 0;
int mode = 0;
int modeChange = 0;
//int mode1 = 0;
//int mode2 = 0;
//int mode3 = 0;
//int mode4 = 0;
float limit = 0;
float percantage = 10;
float perPWM = 0;
float motorLowerPWMLimit = 130;
float motorUpperPWMLimit = 255;


void setup() {
  // set segment pins as OUTPUT
  pinMode(seg[0], OUTPUT);
  pinMode(seg[1], OUTPUT);
  pinMode(seg[2], OUTPUT);
  pinMode(seg[3], OUTPUT);
  pinMode(seg[4], OUTPUT);
  pinMode(seg[5], OUTPUT);
  pinMode(seg[6], OUTPUT);
  pinMode(seg[7], OUTPUT);

  // Motor speed increment and decrement buttons
  pinMode(buttonIncrease, INPUT);
  pinMode(buttonDecrease, INPUT);

  // motor pwm
  pinMode(enA, OUTPUT);
  //motor pins for rotation
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //motor stopped
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  Serial.begin(9600);
  motorPercantage(percantage);

}

void loop() {
  buttonIncState  = digitalRead(buttonIncrease);
  buttonDecState  = digitalRead(buttonDecrease);

  if (buttonIncState) {
    // If the button pressed flag will be 1 and button's pressed state cannot increment the mode value more than once.
    if (incFlag == 0) {
      if (mode != int(limit)) {
        mode += 1;
        modeChange = 0;
      }
      incFlag = 1;
    }
  } else {
    incFlag = 0;
  }
  if (buttonDecState) {
    // If the button pressed flag will be 1 and button's pressed state cannot decrement the mode value more than once.
    if (decFlag == 0) {
      if (mode != int(-1 * limit)) {
        mode -= 1;
        modeChange = 0;
      }
      decFlag = 1;
    }
  } else {
    decFlag = 0;
  }
  if (mode < 0) {
    // mode value can be negative and it cannot be printed to 7 segment display so we will multiply with -1.
    if (mode == 10) {
      Print('a');
    }
    Print(-1 * mode);
  } else {
    if (mode == -1) {
      Print('a');
    }
    Print(mode);
  }
  motorMode(mode); // Motor operations
}
void motorPercantage(float percentage) {
  limit = 100 / percentage;
  perPWM = ((motorUpperPWMLimit - motorLowerPWMLimit) / (limit - 1));
  Serial.println(perPWM);
  Serial.println(limit);
}
void motorRotation(int mode) {
  if (mode > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (mode < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

}
void motorMode(int mode) {
  if (mode != 0) {
    if (modeChange == 0) {
      Serial.println(130 + int(perPWM * (abs(mode) - 1)));
      motorRotation(mode);
      modeChange = 1;
      analogWrite(enA, 255);
      delay(20);
    }
    analogWrite(enA, 130 + int(perPWM * (abs(mode) - 1)));
  } else {
    motorRotation(mode);
  }
  //  // BURADANS ONRASINI YAP
  //  if (mode == -4) {
  //    mode3 = 0;
  //    motorRotation(mode);
  //    if (mode4 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode4 = 1;
  //    }
  //    analogWrite(enA, 255);
  //  }
  //  else if (mode == -3) {
  //    mode2 = 0;
  //    mode4 = 0;
  //    motorRotation(mode);
  //    if (mode3 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode3 = 1;
  //    }
  //    analogWrite(enA, 210);
  //  }
  //  else if (mode == -2) {
  //    mode1 = 0;
  //    mode3 = 0;
  //    motorRotation(mode);
  //    if (mode2 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode2 = 1;
  //    }
  //    analogWrite(enA, 170);
  //  }
  //  else if (mode == -1) {
  //    mode2 = 0;
  //    motorRotation(mode);
  //    if (mode1 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode1 = 1;
  //    }
  //    analogWrite(enA, 130);
  //  }
  //  else if (mode == 0) {
  //    mode1 = 0;
  //    digitalWrite(in1, LOW);
  //    digitalWrite(in2, LOW);
  //  }
  //  else if (mode == 1) {
  //    mode2 = 0;
  //    motorRotation(mode);
  //    if (mode1 == 0) {
  //      Serial.println("MODE1");
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode1 = 1;
  //    }
  //    analogWrite(enA, 130);
  //  }
  //  else if (mode == 2) {
  //    mode1 = 0;
  //    mode3 = 0;
  //    motorRotation(mode);
  //    if (mode2 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode2 = 1;
  //    }
  //    analogWrite(enA, 170);
  //  }
  //  else if (mode == 3) {
  //    mode2 = 0;
  //    mode4 = 0;
  //    digitalWrite(in1, HIGH);
  //    digitalWrite(in2, LOW);
  //    if (mode2 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode2 = 1;
  //    }
  //    analogWrite(enA, 210);
  //  }
  //  else if (mode == 4) {
  //    mode1 = 0;
  //    motorRotation(mode);
  //    if (mode2 == 0) {
  //      analogWrite(enA, 255);
  //      delay(20);
  //      mode2 = 1;
  //    }
  //    analogWrite(enA, 255);
  //  }
}
void setState(bool mode) //sets the hole segment state to "mode"
{ for (int i = 0; i <= 6; i++)
  {
    digitalWrite(seg[i], mode);
  }
}
void Print(int num) // print any number on the segment
{
  setState(segMode);//turn off the segment
  if (num > chars || num < 0 ) // if the number is not declared
  {
    for (int i = 0; i <= 6; i++)
    {
      digitalWrite(seg[i], HIGH);
      delay(100);
      digitalWrite(seg[i], LOW);
    }
    for (int i = 0; i <= 2; i++)
    {
      delay(100);
      setState(HIGH);
      delay(100);
      setState(LOW);
    }
  } else // else if the number declared, print it
  {
    if (segMode == 0) { //for segment mode
      for (int i = 0; i < 8; i++)
      {
        digitalWrite(seg[i], Chars[num][i + 1]);
      }
    }
    else {
      for (int i = 0; i < 8; i++)
      { digitalWrite(seg[i], !Chars[num][i + 1]);
      }
    }
  }
}
