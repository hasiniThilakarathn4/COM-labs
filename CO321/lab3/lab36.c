#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char count =0;

ISR (TIMER0_OVF_vect){    
	count++;
	if(count==250){
		PORTB= PORTB ^ (1 << 5);
		TCNT0 = 131;
		count=0;
	}

}


int main(void){
	DDRB = 0xFF;
	
	TCCR0A=0x00; //Normal mode
	TCCR0B = 0x04; //256 prescaler
	TCNT0 = 131; 
	TIMSK0 = 0x01;   
	
	sei();
	while(1){
	}
}