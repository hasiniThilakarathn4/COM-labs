#include <avr/io.h>
#include <avr/interrupt.h>



int main(void){
	
	DDRD |= (1<<6);  //PWM pin as an output pin
	
	TCCR0A = (1<<WGM01) | (1<<WGM00); //for fast PWM mode
	TCCR0A |= (1<<COM0A1);

	TCCR0B = 0x03;	//1:64
	
	OCR0A = 127;
	
	 
	while (1){
	
		
	} 
	
	return 0;
}