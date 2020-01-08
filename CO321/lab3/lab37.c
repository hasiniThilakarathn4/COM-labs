#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char count;
ISR(TIMER1_OVF_vect){ // Timer1 overflow interrupt  handler 
	TCNT1 = 34286;
	PORTB = PORTB ^ (1<<5);
}

ISR(TIMER0_OVF_vect){ // Timer0 overflow interrupt  handler 
    count ++;
	if (count == 5){
		
		PORTB = PORTB ^ (1<<4);
		TCNT0 = 131;
		count = 0;
	}
	
	TCNT0 = 0x00;
}

int main(void) {
	DDRB = 0xFF; 
	

	//Timer0
	count = 0; 
	TCCR0A = 0x00;
	TCCR0B = 0x04; 
	TIMSK0 = 0x01; 
	TCNT0 = 100;


	//Timer1
	TCCR1A = 0x00; 
	TCCR1B = 0x04; 
	TIMSK1 = 0x01; 
	TCNT1 = 34286;

	sei(); 
	while (1){} 
	return 0;
}