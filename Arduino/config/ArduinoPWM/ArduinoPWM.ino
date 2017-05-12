#include <Servo.h>

#define MIDDLE_ROULIS 1450
#define MIDDLE_TANGUAGE 1500
#define MIDDLE_LACET 1675

#define SPEED 0.03
#define MAX 19500
#define MIN -19500

Servo roulis;
Servo tanguage;
Servo lacet;

int R = 0;
int T = 0;
int L = 0;

float RR = 0;
float TT = 0;

char lastByte;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  
  roulis.attach(10);
  roulis.writeMicroseconds(MIDDLE_ROULIS);

  tanguage.attach(11);
  tanguage.writeMicroseconds(MIDDLE_TANGUAGE);

  lacet.attach(9);
  lacet.writeMicroseconds(MIDDLE_LACET);
}

void loop() {
    char firstByte = (char)Serial.read();
    
    if (firstByte == '#') {
      TT = 0;
      RR = 0;
      lastByte = '#';
      R = Serial.parseInt();
      T = Serial.parseInt();
      L = Serial.parseInt();
      roulis.writeMicroseconds(MIDDLE_ROULIS - R);
      tanguage.writeMicroseconds(MIDDLE_TANGUAGE - T);
      lacet.writeMicroseconds(MIDDLE_LACET - L);
    }
    
    else if (firstByte == '@') {
      lastByte = '@';
      lacet.writeMicroseconds(MIDDLE_LACET);
    }
    else if (firstByte == 'U' || lastByte == 'U') {
      TT++;
      lastByte = 'U';
      tanguage.writeMicroseconds(MIDDLE_TANGUAGE - (int)round(TT*SPEED));
    }
    else if (firstByte == 'D' || lastByte == 'D') {
      TT--;
      lastByte = 'D';
      tanguage.writeMicroseconds(MIDDLE_TANGUAGE - (int)round(TT*SPEED));
    }
    else if (firstByte == 'R') {
      lastByte = 'R';
      lacet.writeMicroseconds(MIDDLE_LACET + 1500*SPEED);
    }
    else if (firstByte == 'L') {
      lastByte = 'L';
      lacet.writeMicroseconds(MIDDLE_LACET - 1500*SPEED);
    }
    else if (firstByte == 'W' || lastByte == 'W') {
      RR++;
      lastByte = 'W';
      roulis.writeMicroseconds(MIDDLE_ROULIS - (int)round(RR*SPEED));
    }
    else if (firstByte == 'V' || lastByte == 'V') {
      RR--;
      lastByte = 'V';
      roulis.writeMicroseconds(MIDDLE_ROULIS - (int)round(RR*SPEED));
    }
    
    if (TT > MAX) TT = MAX;
    if (TT < MIN) TT = MIN;
    if (RR > MAX) RR = MAX;
    if (RR < MIN) RR = MIN;
}
