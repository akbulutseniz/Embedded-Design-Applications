#define trigPin 4
#define echoPin 2
#define buzzer  7
#define led     6
int Buzzer_LED_Freq_Max = 1000;
int Buzzer_LED_Freq_Min = 10;
int Dist_Min = 10;
int Dist_Max = 100;
int Current_Dist = 0;
int Current_Freq = 0;
int Update_Freq = 500;
int Update_LCD = 200;

long sure, mesafe;



void setup () {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.println("Arduino İle Mesafe Sensörü Uygulaması Başlatılıyor...");
  delay(3000);
}
void loop () {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  Current_Dist = (sure / 2) * 0.343;
  Current_Freq = (((Current_Dist-Dist_Min)/(Dist_Max-Dist_Min))*(Buzzer_LED_Freq_Max-Buzzer_LED_Freq_Min))+Buzzer_LED_Freq_Min;
  
  Serial.print(mesafe);
  Serial.println(" cm uzaklıkta");
  digitalWrite(buzzer, HIGH);
  digitalWrite(led, HIGH);
  delay(Current_Freq);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  delay(500);
}
