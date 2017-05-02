#define MICROS2PWM(x) (x/4)

#define MIDDLE_ROULIS 1450
#define MIDDLE_TANGUAGE 1500
#define MIDDLE_LACET 1675

#define SPEED 0.03
#define MAX 19500
#define MIN -19500

int R = 0;
int T = 0;
int L = 0;

float RR = 0;
float TT = 0;

char lastByte;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  
  init_PWM();
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
      //roulis.writeMicroseconds(MIDDLE_ROULIS - R);
      //tanguage.writeMicroseconds(MIDDLE_TANGUAGE - T);
      //lacet.writeMicroseconds(MIDDLE_LACET - L);

      OCR1A = MICROS2PWM(MIDDLE_LACET - L);
      OCR1B = MICROS2PWM(MIDDLE_ROULIS - R);
      OCR1C = MICROS2PWM(MIDDLE_TANGUAGE - T);
    }
    
    else if (firstByte == '@') {
      lastByte = '@';
      //lacet.writeMicroseconds(MIDDLE_LACET);
      OCR1A = MICROS2PWM(MIDDLE_LACET);
    }
    else if (firstByte == 'U' || lastByte == 'U') {
      TT++;
      lastByte = 'U';
      //tanguage.writeMicroseconds(MIDDLE_TANGUAGE - (int)round(TT*SPEED));
      OCR1C = MICROS2PWM(MIDDLE_TANGUAGE - (int)round(TT*SPEED));
    }
    else if (firstByte == 'D' || lastByte == 'D') {
      TT--;
      lastByte = 'D';
      //tanguage.writeMicroseconds(MIDDLE_TANGUAGE - (int)round(TT*SPEED));
      OCR1C = MICROS2PWM(2000);
    }
    else if (firstByte == 'R') {
      lastByte = 'R';
      //lacet.writeMicroseconds(MIDDLE_LACET + 1500*SPEED);
      OCR1A = MICROS2PWM(MIDDLE_LACET + 1500*SPEED);
    }
    else if (firstByte == 'L') {
      lastByte = 'L';
      //lacet.writeMicroseconds(MIDDLE_LACET - 1500*SPEED);
      OCR1A = MICROS2PWM(MIDDLE_LACET - 1500*SPEED);
    }
    else if (firstByte == 'W' || lastByte == 'W') {
      RR++;
      lastByte = 'W';
      //roulis.writeMicroseconds(MIDDLE_ROULIS - (int)round(RR*SPEED));
      OCR1B = MICROS2PWM(MIDDLE_ROULIS - (int)round(RR*SPEED));
    }
    else if (firstByte == 'V' || lastByte == 'V') {
      RR--;
      lastByte = 'V';
      //roulis.writeMicroseconds(MIDDLE_ROULIS - (int)round(RR*SPEED));
      OCR1B = MICROS2PWM(MIDDLE_ROULIS - (int)round(RR*SPEED));
    }
    
    if (TT > MAX) TT = MAX;
    if (TT < MIN) TT = MIN;
    if (RR > MAX) RR = MAX;
    if (RR < MIN) RR = MIN;
}

void init_PWM() {
  //Définition du prescaler, du Fast PWM
  TCCR1A = 0xAA;
  TCCR1B = 0x1B;
  TCCR1C = 0;
  ICR1 = 5000;

  //Definition port de sortie
  DDRB |= 1<<5;
  DDRB |= 1<<6;
  DDRB |= 1<<7;

  //Definition largeur d'impulsion
  OCR1A = MICROS2PWM(MIDDLE_LACET);
  OCR1B = MICROS2PWM(MIDDLE_ROULIS);
  OCR1C = MICROS2PWM(MIDDLE_TANGUAGE);
}

