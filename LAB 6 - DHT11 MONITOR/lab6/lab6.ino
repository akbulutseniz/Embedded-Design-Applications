#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
int DhtPin = 2; // DhtPin olarak Dijital 2'yi belirliyoruz.
int btn = 3;
int lang_mode = 1;
dht11 dht_sensor; // dht_sensor adında bir DHT11 nesnesi oluşturduk.
boolean flag = true;
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  pinMode(btn, INPUT);
  digitalWrite(btn, HIGH);
}

void loop() {
  int chk = dht_sensor.read(DhtPin);
  float fah = dht_sensor.fahrenheit();
  float cel = (float)dht_sensor.temperature;
  float hum = (float)dht_sensor.humidity;
  String fah_str = String(fah,2);
  String cel_str = String(cel,2);
  String hum_str = String(hum,2);
  if (digitalRead(btn) == LOW) {

    if (flag) {
      if (lang_mode == 1 )lang_mode = 0;
      else lang_mode = 1;
    }
    flag = false;//dil değişemez

  } else {
    flag = true;//dil değişebilir
    if (lang_mode == 1) {
      lcd.setCursor(0, 0);
      lcd.print("TEM(F):");
      if(fah_str.length()==5)lcd.print(" ");
      if(fah_str.length()==4)lcd.print("  ");
      lcd.print(fah_str);
      lcd.print(" EN");
      lcd.setCursor(0, 1);
      lcd.print("HUM(%):");
      if(hum_str.length()==5)lcd.print(" ");
      if(hum_str.length()==4)lcd.print("  ");
      lcd.print(hum_str);
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("SIC(C):");
      if(cel_str.length()==5)lcd.print(" ");
      if(cel_str.length()==4)lcd.print("  ");
      cel_str.replace('.',',');
      hum_str.replace('.',',');
      lcd.print(cel_str);
      lcd.print(" TR");
      lcd.setCursor(0, 1);
      lcd.print("NEM(%):");
      if(hum_str.length()==5)lcd.print(" ");
      if(hum_str.length()==4)lcd.print("  ");
      lcd.print(hum_str);
    }
  }

}
