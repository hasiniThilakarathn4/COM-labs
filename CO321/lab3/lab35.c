#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#define BLINK_DELAY_MS 100

unsigned char count =0;

void delay_timer0(){
	count=0;
	while(count<11){
       TCNT0 = 131;  //Load timer counter register
	
	   TCCR0A = 0x00;   //Set Timer0 under normal mode with 1:1024 prescaler
	   TCCR0B = 0x04;

while((TIFR0&0x01)==0);  //Wait till timer overflow bit (TOV0) is set_new_handler
	
	TCCR0A = 0x00;   //Clear timer setings (this stops the timer)
	TCCR0B = 0x00;
	
	TIFR0 = 0x01; 
	count++;
	}
	
}


ISR(TIMER1_OVF_vect){

	PORTB = PORTB ^(1<<5);
  
}


int main (void){
	DDRB =0xFF;

	sei();
	TIMSK1 = 0x01;
	
	TCNT1 = 3036;  //Load timer counter register
	
	TCCR1A = 0x00;   
	TCCR1B = 0x04;
	
	
	
	 int z;
	while(1){
		for(z=4;z>0;z--){
			PORTB = PORTB | (1<<z);
			
			delay_timer0();
			
			PORTB = PORTB &~(1<<z);
			delay_timer0();
		}
		
		for(z=2;z<4;z++){
			PORTB = PORTB | (1<<z);
			
			delay_timer0();
			
			PORTB = PORTB &~(1<<z);
			delay_timer0();
		}
	}
}
	