#define seg 3
#define sens 2
#define led 9
int wait = 50;
void setup() {
  // put your setup code here, to run once:
  int i = 0;
  Serial.begin(9600);
  pinMode(sens, INPUT);
  pinMode(led,OUTPUT);
  for (i = 0; i < 6; i++) {
    pinMode(seg + i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(sens,LOW);
  delay(100);
  int sens_val = digitalRead(sens);
  //int sens_val = HIGH;
  int counter = 0;
  int i = 0;
  if ( sens_val == HIGH) {
    digitalWrite(led,HIGH);
    for (i = 0; i < wait; i++) {
      int j = 0;
      for (j = 0; j < 6; j++) {
        if (counter % 6 == j) {
          digitalWrite((seg + j), LOW);
        }
        else digitalWrite((seg + j), HIGH);
      }
      counter++;
      delay(100);
    }
  }
  else {
    digitalWrite(led,LOW);
    Serial.println("hello");
    for (i = 0; i < 6; i++) {
      digitalWrite(seg + i, HIGH);
    }
  }
}
