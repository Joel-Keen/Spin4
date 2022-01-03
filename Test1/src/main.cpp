#include <avr/io.h>

void init_pwmtimer(){
  TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM13) | _BV(WGM12);
  OCR1A = 0x00ff;
  OCR1B = 4;
  DDRD=0xff;
  PORTD=0;
}

void init_ADC(){
  ADMUX=_BV(MUX0);
  ADCSRA=_BV(ADEN);
}

int main(){
  init_pwmtimer();
  init_ADC();
  while(1){
    ADCSRA|=_BV(ADSC);
    while(ADCSRA&_BV(ADSC));
    uint16_t setPt=0xffff/ADC;
    uint16_t minPulseWidth=0x08; //minPulseWidth corresponds to max speed
    if(setPt<minPulseWidth) setPt=minPulseWidth; 
    OCR1A=setPt;
  }

} 