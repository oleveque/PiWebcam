//Function to convert Microsecond in counter value
#define MICROS2PWM(x) (x/4)

void setup() {
  //PWM mode (mode 2): COM1x1:0 = b10
  //Waveform (mode 9): WGMn3:0 = b1001
  //Prescaler (/64): CS2:0 = b011
  TCCR1A = 0xAA;
  TCCR1B = 0x1B;
  TCCR1C = 0;

  //Max counter value = 5000
  ICR1 = 5000;

  //Define PWM output port
  DDRB |= 1<<5; //D9
  DDRB |= 1<<6; //D10
  DDRB |= 1<<7; //D11

  //Define PWM value in microsecond
  OCR1A = MICROS2PWM(1675); //D9
  OCR1B = MICROS2PWM(1450); //D10
  OCR1C = MICROS2PWM(1500); //D11
}

void loop() {
  //Nothing
}

