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
int16_t cmd;

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
      
      cmd = MIDDLE_LACET - L;
      OCR1A = MICROS2PWM(cmd);
      
      cmd = MIDDLE_ROULIS - R;
      OCR1B = MICROS2PWM(cmd);
      
      cmd = MIDDLE_TANGUAGE - T;
      OCR1C = MICROS2PWM(cmd);
    }
    
    else if (firstByte == '@') {
      lastByte = '@';
      OCR1A = MICROS2PWM(MIDDLE_LACET);
    }
    else if (firstByte == 'U' || lastByte == 'U') {
      TT++;
      lastByte = 'U';
      cmd = MIDDLE_TANGUAGE - (int)round(TT*SPEED);
      OCR1C = MICROS2PWM(cmd);
    }
    else if (firstByte == 'D' || lastByte == 'D') {
      TT--;
      lastByte = 'D';
      cmd = MIDDLE_TANGUAGE - (int)round(TT*SPEED);
      OCR1C = MICROS2PWM(cmd);
    }
    else if (firstByte == 'R') {
      lastByte = 'R';
      cmd = MIDDLE_LACET + 1500*SPEED;
      OCR1A = MICROS2PWM(cmd);
    }
    else if (firstByte == 'L') {
      lastByte = 'L';
      cmd = MIDDLE_LACET - 1500*SPEED;
      OCR1A = MICROS2PWM(cmd);
    }
    else if (firstByte == 'W' || lastByte == 'W') {
      RR++;
      lastByte = 'W';
      cmd = MIDDLE_ROULIS - (int)round(RR*SPEED);
      OCR1B = MICROS2PWM(cmd);
    }
    else if (firstByte == 'V' || lastByte == 'V') {
      RR--;
      lastByte = 'V';
      cmd = MIDDLE_ROULIS - (int)round(RR*SPEED);
      OCR1B = MICROS2PWM(cmd);
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

