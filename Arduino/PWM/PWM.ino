void setup() {
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
  OCR1A = 2500;
  OCR1B = 2500;
  OCR1C = 2500;
}

void loop() {
  OCR1B = 200;
}

