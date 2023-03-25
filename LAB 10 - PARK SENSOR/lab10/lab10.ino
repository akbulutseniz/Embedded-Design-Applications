#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

long prev_millis = 0;
long prev_millis2 = 0;

int Buzzer_LED_Freq_Max = 1000;
int Buzzer_LED_Freq_Min = 10;
int Dist_Max = 100;
int Dist_Min = 10;
int Current_Dist = 0;
int Current_Freq = 0;
int Update_Freq = 500;
int Update_LCD = 200;
long duration;
int safetyDistance;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(buzzer, LOW);
}

void loop() {
  if ((millis() - prev_millis) >= Update_Freq) {
    Current_Freq = abs((((Current_Dist - Dist_Min) / (Dist_Max - Dist_Min)) * (Buzzer_LED_Freq_Max - Buzzer_LED_Freq_Min)) + Buzzer_LED_Freq_Min);
    prev_millis = millis();

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
    Current_Dist = duration * 0.034 / 2;

    safetyDistance = Current_Dist;
    if (safetyDistance <= Dist_Min) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledPin, HIGH);
    }
    if (safetyDistance > Dist_Min && safetyDistance < Dist_Max) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledPin, HIGH);
      //delay(Current_Freq);
      digitalWrite(buzzer, LOW);
      digitalWrite(ledPin, LOW);
      //delay(Current_Freq);
    }
    if (safetyDistance >= Dist_Max) {
      digitalWrite(buzzer, LOW);
      digitalWrite(ledPin, LOW);
    }

    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(Current_Dist);
    Serial.print("Current_Freq: ");
    Serial.println(Current_Freq);
  }

  if ((millis() - prev_millis) >= Update_LCD) {
    prev_millis = millis();
    lcd.setCursor(0, 0);
    lcd.print("DISTANCE :");
    lcd.print("  ");
    if (Current_Dist < 100) {
      lcd.print(Current_Dist);
      lcd.print(" ");
    }
    else {
      lcd.print(Current_Dist);
    }

    lcd.setCursor(0, 1);
    lcd.print("FREQUENCY :");
    lcd.print("  ");
    if (Current_Freq < 100) {
      lcd.print(Current_Freq);
      lcd.print(" ");
    }
    else {
      lcd.print(Current_Freq);
    }
  }
}
