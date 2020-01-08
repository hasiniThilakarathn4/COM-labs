#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

unsigned int count;


ISR(TIMER0_OVF_VECT){
	count ++;
	
	if(count==5){
	PORTB ^= (1<<5);
	TCNT0 = 100;
	count=0;
	}
	
	TCNT0 = 0x00;
}

ISR(TIMER1_OVF_VECT){
	TCNT1 = 34286;
	PORTB ^= (1<<6);
}




int main(){
	
	DDRB = 0xFF;
	
	sei();
	TIMSK0 = 0x01;
	
	TCNT0 = 100;
	
	TCCR0A = 0x00;
	TCCR0B = 0x05; //1024
	
	
	
	
	TIMSK1 = 0x01;
	
	TCNT1 = 34286;
	
	TCCR1A = 0x00;
	TCCR1B = 0x04; //256
	while(1){
	}
return 0;	
}