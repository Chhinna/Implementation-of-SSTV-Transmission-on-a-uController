#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1#include "eeprom.h"
#include <avr/io.h>
#include <stdint.h>
#include "common.h"
#include <stdio.h>

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ00);
	}	void main( void )
	{ unsigned char z;
      uint32_t g= 0;
		USART_Init(MYUBRR);
		while(1){
			z = USART_Receive();
			
			//eeprom_write_bytes(g , 1 , z);
			
			USART_Transmit(z);
			
			g++;
	}return(0);}

