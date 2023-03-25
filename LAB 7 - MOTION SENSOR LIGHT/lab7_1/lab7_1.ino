int pirsensor = 0;
int remainingTime = 17;

int dp = 8;
int a = 9;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;

int led = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(12, INPUT);
  
  pinMode(dp, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}


void loop()
{

  pirsensor = digitalRead(12);
  if (pirsensor == HIGH)
  {
    digitalWrite(13, HIGH);
    
    for(int time = remainingTime; time >= 0; time--){
    
      if(time >= 10){
        int mod = time % 6;

        switch(mod){
          case 1:
            digitalWrite(dp,HIGH);

            digitalWrite(a,HIGH);
            break;
          case 2:
            digitalWrite(dp,HIGH);

            digitalWrite(b,HIGH);
            break;
          case 3:
            digitalWrite(dp,HIGH);

            digitalWrite(c,HIGH);
            break;
          case 4:
            digitalWrite(dp,HIGH);

            digitalWrite(d,HIGH);
            break;
          case 5:
            digitalWrite(dp,HIGH);

            digitalWrite(e,HIGH);
            break;
          case 0:
            digitalWrite(dp,HIGH);

            digitalWrite(f,HIGH);
            break;
        }
      }
      else{
          byte segCode[10][8] = {
        // 7 segment code table
        //  a  b  c  d  e  f  g  .
          { 1, 1, 1, 1, 1, 1, 0, 0},  // 0
          { 0, 1, 1, 0, 0, 0, 0, 0},  // 1
          { 1, 1, 0, 1, 1, 0, 1, 0},  // 2
          { 1, 1, 1, 1, 0, 0, 1, 0},  // 3
          { 0, 1, 1, 0, 0, 1, 1, 0},  // 4
          { 1, 0, 1, 1, 0, 1, 1, 0},  // 5
          { 1, 0, 1, 1, 1, 1, 1, 0},  // 6
          { 1, 1, 1, 0, 0, 0, 0, 0},  // 7
          { 1, 1, 1, 1, 1, 1, 1, 0},  // 8
          { 1, 1, 1, 1, 0, 1, 1, 0}   // 9
        };

          digitalWrite(dp,HIGH);
          digitalWrite(a,segCode[time][0]);
          digitalWrite(b,segCode[time][1]);
          digitalWrite(c,segCode[time][2]);
          digitalWrite(d,segCode[time][3]);
          digitalWrite(e,segCode[time][4]);
          digitalWrite(f,segCode[time][5]);
          digitalWrite(g,segCode[time][6]);

      }
    
    
     delay(1000);
    
    digitalWrite(dp,HIGH);
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    }
    
    
    
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, LOW);
  }
    
}
