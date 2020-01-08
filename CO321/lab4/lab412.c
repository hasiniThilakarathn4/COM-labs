#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100




void delay_timer1(){

	
       TCNT1 = 40536;  //Load timer counter register
	
	   TCCR1A = 0x00;   //Set Timer0 under normal mode with 1:1024 prescaler
	   TCCR1B = 0x03;

while((TIFR1&0x01)==0);  //Wait till timer overflow bit (TOV0) is set_new_handler
	
	TCCR1A = 0x00;   //Clear timer setings (this stops the timer)
	TCCR1B = 0x00;
	
	TIFR1 = 0x01; 
	

	
}




int main(void){
	
	DDRD |= (1<<6);
	
	TCCR0A = (1<<WGM01) | (1<<WGM00); //fast PWM mode
	TCCR0A |= (1<<COM0A1);   //non-inverting mode

	TCCR0B = 0x03;     //prescaler 64
 
	while (1){
		int i=0,j=255;
		
			while(i<256){
			OCR0A = i;   //output compare register
		
		delay_timer1();
			i+=5;
		}
		
		while(j>=0){
			OCR0A = j;
		
		delay_timer1();
			j-=5;
		}
		
	} 
	return 0;
}