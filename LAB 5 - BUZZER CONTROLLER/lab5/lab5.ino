int soundDuration=0;
int silenceDuration=0;
int finishDuration=0;
String soundString=" ";
int buzzer = 3;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  getInputs();
  int duration=0;
    int i=0;
     while(i<soundString.length()-1){
     Serial.print("Duration :");
     Serial.println(duration);
     char temp=soundString.charAt(i);
     if(temp=='0'){
          digitalWrite(buzzer,LOW);
          Serial.println(temp);
          delay(soundDuration);
          duration+=soundDuration;
          Serial.print("Duration :");
          Serial.println(duration);
      }
      else if(temp=='1'){
           digitalWrite(buzzer,HIGH);
           Serial.println(temp);
           delay(soundDuration);
           duration+=soundDuration;
           Serial.print("Duration :");
           Serial.println(duration);
      }
      i++;
      if(i!=soundString.length()-1){
        Serial.println("SILENT");
      }
      else{
        Serial.println("FINISH");
      }
      digitalWrite(buzzer,LOW);
      delay(silenceDuration);
      duration+=silenceDuration;
    }
}

void getInputs(){
  Serial.println("---------------------------");
  Serial.println("Enter the required values.");
  Serial.println("---------------------------");

  getSoundDuration();
  getSilenceDuration();
  getFinishDuration();
  getSoundString();
}

void getSoundDuration(){
  Serial.print("PLEASE ENTER SOUND DURATION (MS): "); 
  while(true){
      if (Serial.available() > 0) {   
        soundDuration = Serial.readString().toInt();
        Serial.println(soundDuration);
        if ((soundDuration < 1000) && (soundDuration > 0)) {
          Serial.println(soundDuration);
          break;
        }
        else if (soundDuration == '\n') {
          Serial.println("Null");
          getSoundDuration();
        }
        else {
          Serial.println("Not valid! Enter Again!");
          getSoundDuration();
        }
    }
  }
}

void getSilenceDuration(){
  Serial.print("PLEASE ENTER SILENCE DURATION (MS): ");
   while(true){
      if (Serial.available() > 0) {    
        silenceDuration = Serial.readString().toInt();
        Serial.println(silenceDuration);
        if ((silenceDuration < 1000) && (silenceDuration > 0)) {
          Serial.println(silenceDuration);
          break;
        }
        else if (silenceDuration == '\n') {
          Serial.println("Null");
          getSilenceDuration();
        }
        else {
          Serial.println("Not valid! Enter Again!");
          getSilenceDuration();
        }
    }
  }
}

void getFinishDuration(){
   Serial.print("PLEASE ENTER FINISH DURATION (MS): ");
   while(true){
      if (Serial.available() > 0) {    
        finishDuration = Serial.readString().toInt();
        Serial.println(finishDuration);
        if ((finishDuration < 10000) && (finishDuration > 0)) {
          Serial.println(finishDuration);
          break;
        }
        else if (finishDuration == '\n') {
          Serial.println("Null");
          getFinishDuration();
        }
        else {
          Serial.println("Not valid! Enter Again!");
          getFinishDuration();
        }
    }
  }
}

void getSoundString(){
  Serial.print("PLEASE ENTER SOUND STRING   : ");
  while(true){
      if (Serial.available() > 0) {    
        soundString = Serial.readString();
        Serial.println(soundString);
        int flag=0;
        int i =0;
        while(i<soundString.length()-1){
          char temp=soundString.charAt(i);
          if(temp=='0' || temp=='1'){
            
          }
          else{
            flag=1;
          }
          i++;
        }
        if(flag==0){
          Serial.println(soundString);
          break;
        }
        else if(flag==1){
          Serial.println("Not valid! Enter Again!");
          getSoundString();
        }
        else
        {
          Serial.println("Null");
          getFinishDuration();
        }
    }
  }
}
