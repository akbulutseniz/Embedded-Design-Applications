int ledPin[] = {8, 9, 10, 11, 12}; //LED PİN DİZİSİ
int incrementValue = 0; //increment değeri
int waitTime = 0; //wait time değeri
int incrementedNum=0; //arttırılmış değer


void setup() {
  Serial.begin(9600); //serial 9600 ayarlanıyor
  for (int i = 0; i < 5; i++)
  {
    pinMode(ledPin[i], OUTPUT); //led pinlerine çıkış veriliyor
  }
}

void loop() {

  // Increment Value serialden alınıyor ve doğru değer gelene kadar dönüyor.
  while(true){
      if (Serial.available() > 0) {    // is a character available?
        Serial.println("Please enter increment value: ");
        incrementValue = Serial.readString().toInt();
        Serial.println(incrementValue);
        if ((incrementValue < 31) && (incrementValue > 0)) {
          Serial.println("increment value: ");
          Serial.println(incrementValue);
          break;
        }
        else if (incrementValue == '\n') {
          Serial.println("Null");
          continue;
        }
        else {
          Serial.println("Not valid!");
          continue;
        }
    } // end: if (Serial.available() > 0)
  }

  // Wait time serialdedn alınıyor ve doğru değer gelene kadar dönüyor.
  while(true){
      if (Serial.available() > 0) {    // is a character available?
        Serial.println("Please enter wait time: ");
        waitTime = Serial.readString().toInt();
        Serial.println(waitTime);
        if ((waitTime < 10001) && (waitTime > 0)) {
          Serial.println("wait time value: ");
          Serial.println(waitTime);
          break;
        }
        else if (waitTime == '\n') {
          Serial.println("Null");
          continue;
        }
        else {
          Serial.println("Not valid!");
          continue;
        }
    } // end: if (Serial.available() > 0)
  }

  for(int i=0;i<=10000;i+=waitTime){
      Serial.println(i);
      Serial.println(incrementedNum);
      if(incrementedNum<32){
          displayBinary(incrementedNum);
          delay(waitTime);
          incrementedNum+=incrementValue;
      }
      else{
          incrementedNum=incrementedNum%32;
          Serial.println(incrementedNum);
          displayBinary(incrementedNum);
          delay(waitTime);
          incrementedNum+=incrementValue;
      }
  }

}

// Değeri binarye çevrilip daha sonra binary değere göre ledlere high veren fonksiyon 
void displayBinary(byte numToShow)
{
  for (int i = 0; i < 5; i++)
  {
    if (bitRead(numToShow, i) == 1)
    {
      digitalWrite(ledPin[i], HIGH);
    }
    else
    {
      digitalWrite(ledPin[i], LOW);
    }
  }
}
