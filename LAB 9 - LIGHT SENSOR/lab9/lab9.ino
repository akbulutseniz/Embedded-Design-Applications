const int ledPin = 10;
const int ldrPin = A3;
int LED_ACTIVATION_VALUE = 500;
int SERIAL_OUTPUT_FREQUENCY = 1000; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}
int count=1;
void loop() {
  
  int ldrStatus = analogRead(ldrPin);
  if(count==SERIAL_OUTPUT_FREQUENCY){
    writeSerial(ldrStatus);
    count=1;
  }
  else
  {
    count++;
  }
}

void writeSerial(int ldrStatus){
  if (ldrStatus <= LED_ACTIVATION_VALUE)
  {
    digitalWrite(ledPin, HIGH);
    Serial.print("LIGHT SENSOR :");
    Serial.println(ldrStatus);
    Serial.println("Its Dark,LED STATUS : ON");

  }
  else
  {
    digitalWrite(ledPin,LOW);
    Serial.print("LIGHT SENSOR :");
    Serial.println(ldrStatus);
    Serial.println("Its Bright,LED STATUS : OFF");
  }
}
