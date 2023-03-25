#include <LiquidCrystalTr.h>
#include <PrintTr.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int receivedInt; //prepare variable for input
String  r1Text="";
bool r1Status=0; //0==DISABLED / 1==ENABLED
bool r1Direction=0; //0==LEFT , 1==RIGHT
int r1Speed=1000;

String r2Text="";
bool r2Status=0; // 0==DISABLED / 1==ENABLED
bool r2Direction=0; //0==LEFT , 1==RIGHT
int r2Speed=1000;

char *statusArr[]={"DISABLED","ENABLED"};
char *dirArr[]={"LEFT","RIGHT"};

int deger=0;

char buffer[50];
void setup() {
    Serial.begin(9600); //setup console
    printMenu();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(r1Text);
    lcd.setCursor(0, 1);
    lcd.print(r2Text);
    delay(1000);
    
}
void loop() {
  recvInt(); //call function to read value from console
  PrintByInput(); //call function with SWITCH
}
void recvInt() {
  while(Serial.available() == 0) { } //wait for input from console
  receivedInt = Serial.parseInt(); // parse input to INT, other values are ignored
}

void  PrintByInput() {
          if (receivedInt != NULL) { //call SWITCH if input is available
            switch (receivedInt) { //print by input, otheway say !WRONG INPUT!
              case 1:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingOne();
              break;
              case 2:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingTwo();
              break;
              case 3:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingThree();
              break;
              case 4:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingFour();
              break;
              case 5:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingFive();
              break;
              case 6:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingSix();
              break;
              case 7:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingSeven();
              break;
              case 8:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              settingEight();
              break;
              case 9:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              printMenu();
              break;
              case 10:
              Serial.print("SELECTED SETTING NUMBER: ");
              Serial.println(receivedInt);
              Serial.print("SETTINGS SAVED AND EXIT!");
              lcd.setCursor(0, 0);
              lcd.print(r1Text);
              lcd.setCursor(0, 1);
              lcd.print(r2Text);
              scrollingText();
              break;
              default:
              Serial.println("!WRONG INPUT!");
              break;
            }
            receivedInt = NULL; //clear variable value
        }
}
//Print main menu
void printMenu(){
    Serial.println("---------------------------------------------");
    Serial.println("<MAIN MENU>");
    Serial.println("---------------------------------------------");
    Serial.println("9 – PRINT THIS STATUS SCREEN");
    Serial.println("10 – SAVE AND EXIT!");
    Serial.println("*******");
    Serial.println("LCD ROW 0 (UP)");
    Serial.println("*******");
    Serial.print("1 – TEXT                : ");
    Serial.println(r1Text);
    Serial.print("2 – SCROLLING STATUS    : ");
    Serial.println(statusArr[(int)r1Status]);
    Serial.print("3 – SCROLLING DIRECTION : ");
    Serial.println(dirArr[(int)r1Direction]);
    sprintf (buffer,"4 – SCROLLING SPEED (MS): %d MILLISECONDS",r1Speed);
    Serial.println(buffer);
    Serial.println("*******");
    Serial.println("LCD ROW 1 (DOWN)");
    Serial.println("*******");
     Serial.print("5 – TEXT                : ");
    Serial.println(r2Text);
    Serial.print("6 – SCROLLING STATUS    : ");
    Serial.println(statusArr[(int)r2Status]);
    Serial.print("7 – SCROLLING DIRECTION : ");
    Serial.println(dirArr[(int)r2Direction]);
    sprintf (buffer,"8 – SCROLLING SPEED (MS): %d MILLISECONDS",r2Speed);
    Serial.println(buffer);
    Serial.println("---------------------------------------------");
}
void settingOne(){
  Serial.println("PLEASE ENTER TEXT FOR ROW 0: "); 
  while(true){
      if (Serial.available()>0) {
        r1Text = Serial.readString();
        if (r1Text.length()<3) {
          Serial.println("UNDEFINED! Try Again!");
          settingOne();
        }
        else{
          Serial.println(r1Text);
          Serial.println("Entered value accepted!");
          break;
        }
    } 
  }
}
void settingTwo(){
      Serial.println("PLEASE ENTER 0 TO DISABLE OR 1 TO ENABLE SCROLLING: ");
      while(true){
        if (Serial.available()> 0) {
          deger = Serial.readString().toInt();
          if ((deger==1) || (deger==0)) {
            r1Status=deger;
            Serial.print("Entered Value: ");
            Serial.println(deger);
          }
          else {
            Serial.println("Not valid! Try Again!");
            settingTwo();
          }
          break;
      } 
   }
}
void settingThree(){
      Serial.println("PLEASE ENTER 0 FOR LEFT AND 1 FOR RIGHT SCROLLING DIRECTION: ");
      while(true){
        if (Serial.available() > 0) {
          deger = Serial.readString().toInt();
          if ((deger==1) || (deger==0)) {
            r1Direction=deger;
            Serial.print("Entered Value: ");
            Serial.println(deger);
          }
          else {
            Serial.println("Not valid! Try Again!");
            settingThree();
          }
          break;
      } 
    }
}
void settingFour(){
    Serial.println("PLEASE ENTER SCROLLING SPEED FOR ROW 0 (MS):");
    while(true){
        if (Serial.available() > 0) {
          deger = Serial.readString().toInt();
          if ((deger > 10000) || (deger < 1000)) 
          {
            Serial.println("Not valid!Try Again!");
            settingFour();
          }
          else 
          {
            r1Speed=deger;
            Serial.print("Entered Value: ");
            Serial.println(deger);
          }
          break;
      }
   }
}
void settingFive(){
   Serial.println("PLEASE ENTER TEXT FOR ROW 1: "); 
    while(true){
        if (Serial.available()>0) {
          r2Text = Serial.readString();
          if (r2Text.length()<3) {
            Serial.println("UNDEFINED! Try Again!");
            settingFive();
          }
          else{
            Serial.println(r2Text);
            Serial.println("Entered value accepted!");
          }
          break;
      } 
    }
}
void settingSix(){
      Serial.println("PLEASE ENTER 0 TO DISABLE OR 1 TO ENABLE SCROLLING:");
      while(true){
        if (Serial.available()> 0) {
          deger = Serial.readString().toInt();
          if ((deger==1) || (deger==0)) {
            r2Status=deger;
            Serial.print("Entered Value: ");
            Serial.println(deger);
          }
          else {
            Serial.println("Not valid! Try Again!");
            settingSix();
          }
          break;
      } 
   }
}
void settingSeven(){
    Serial.println("PLEASE ENTER 0 FOR LEFT AND 1 FOR RIGHT SCROLLING DIRECTION: ");
      while(true){
        if (Serial.available() > 0) {
          deger = Serial.readString().toInt();
          if ((deger==1) || (deger==0)) {
            r2Direction=deger;
            Serial.print("Entered Value: ");
            Serial.println(deger);
          }
          else {
            Serial.println("Not valid! Try Again!");
            settingSeven();
          }
          break;
      } 
    }
}
void settingEight(){
    Serial.println("PLEASE ENTER SCROLLING SPEED FOR ROW 0 (MS):");
    while(true){
        if (Serial.available() > 0) {
          deger = Serial.readString().toInt();
          if ((deger < 10000) && (deger > 1000)) {
              r2Speed=deger;
              Serial.print("Entered Value: ");
              Serial.println(deger);
          }
          else {
            Serial.println("Not valid!Try Again!");
            settingEight();
          }
          break;
      }
   }
}

void scrollingText(){
int j = 0;
  int k = 0;
  int counter = 0;
  while(true) {
    long start_time = micros();
    int i;
    if (counter % r1Speed == 0) {
      for (i = 0; i < 16; i++) {
        lcd.setCursor(i, 0);
        lcd.print(" ");
      }
      if (r1Text.length() > 16 ) {
        for (i = 0; i < 16; i++) {
          lcd.setCursor(i, 0);
          if((i+j)>0)lcd.print(r1Text.charAt((i + j) % r1Text.length()));
          else lcd.print(r1Text.charAt((r1Text.length()+(i + j)) % r1Text.length())); 
        }
      }
      else {
        for (i = 0; i < r1Text.length(); i++) {
          if((i+j)>0)lcd.setCursor((i + j) % 16, 0);
          else lcd.setCursor((16+(i + j)) % 16, 0);
          lcd.print(r1Text.charAt(i));
        }
      }
      if (r1Status == 1){
        if(r1Direction==0)j++;
        else j--;
      }
    }
    if (counter % r2Speed == 0 ) {
      
      for (i = 0; i < 16; i++) {
        lcd.setCursor(i, 1);
        lcd.print(" ");
      }
      if (r2Text.length() > 16) {
        for (i = 0; i < 16; i++) {
          lcd.setCursor(i, 1);
          if((i+k)>0)lcd.print(r2Text.charAt((i + k) % r2Text.length()));
          else lcd.print(r2Text.charAt((r2Text.length()+(i + k)) % r2Text.length()));
        }
      }
      else {
        for (i = 0; i < r2Text.length(); i++) {
          if((i+k)>0)lcd.setCursor((i + k) % 16, 1);
          else lcd.setCursor((16+(i + k)) % 16, 1);
          lcd.print(r2Text.charAt(i));
        }
      }
      if (r2Status == 1){
        if(r2Direction==0)k++;
        else k--;
      }
    }
    long end_time = micros();
    if ((1000 - (end_time - start_time)) > 0)delayMicroseconds(1000 - (end_time - start_time));
    counter++;
  }
}
