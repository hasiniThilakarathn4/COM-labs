#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	
	DDRD |= (1<<6);
	
	TCCR0A = (1<<WGM01) | (1<<WGM00);
	TCCR0A |= (1<<COM0A1);

	TCCR0B = 0x03;
	
	//OCR0A = 63;
	
	
	sei(); 
	while (1){
		int i,j;
		for(i=0;i<256;i++){
			OCR0A = i;
			
		}
		
		
		
	} 
	return 0;
}