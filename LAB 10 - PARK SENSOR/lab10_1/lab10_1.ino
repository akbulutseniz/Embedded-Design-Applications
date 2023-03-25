#include <LiquidCrystal_I2C.h>

#define trigPin 7
#define echoPin 6
#define pinBuzzer 9

double Dist_Max = 100;
double Dist_Min = 10;

double Current_Dist = 0;
double Current_Freq = 0;

int Update_Freq = 500;
int Update_LCD = 200;

int freq_time = millis(), lcd_time = millis(), buzzer_led_time = millis();

double Buzzer_LED_Freq_Max = 1000;
double Buzzer_LED_Freq_Min = 10;

bool isActive = false;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

void setup()
{
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  int start = millis();
  
  if (start - freq_time > Update_Freq){
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    Current_Dist = (duration/2) / 29.1; // Speed of sound wave divided by 2 (go and back)
    double a = ((Current_Dist - Dist_Min)/(Dist_Max - Dist_Min));

    double b = (Buzzer_LED_Freq_Max - Buzzer_LED_Freq_Min);

    Current_Freq =a*b+Buzzer_LED_Freq_Min;
    
    freq_time = start;
    
  }
  
  if (!isActive && Current_Freq < Buzzer_LED_Freq_Min){
     tone(pinBuzzer, 2000);
     isActive = true;
    buzzer_led_time = start;
  }
  else if (isActive && Current_Freq > Buzzer_LED_Freq_Max){
    noTone(pinBuzzer);
    isActive = false;
    buzzer_led_time = start;
  }
  else if (Current_Freq > Buzzer_LED_Freq_Min && Current_Freq < Buzzer_LED_Freq_Max){
    
      if (start - buzzer_led_time > Current_Freq){

        if (isActive){

          //digitalWrite(pinBuzzer, LOW);
          noTone(pinBuzzer);
        }
        else if (!isActive){

          //digitalWrite(pinBuzzer, HIGH);
          tone(pinBuzzer, 1000);
        }      

        isActive = !isActive;
        buzzer_led_time = start;
      }
  }
  
  if (start - lcd_time > Update_LCD){
  
    Serial.print("Distance: ");
    Serial.println(Current_Dist);
    
    Serial.print("Frequency: ");
    Serial.println(Current_Freq);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.print(Current_Dist);
    lcd.setCursor(0,1);
    lcd.print("Frequency: ");
    lcd.print(Current_Freq);

    
    lcd_time = start;
  }
  
  }
