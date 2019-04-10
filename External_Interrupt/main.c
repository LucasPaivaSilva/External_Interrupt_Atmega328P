/*
 * External_Interrupt.c
 *
 * Created: 4/10/2019 2:28:11 PM
 * Author : Lucas
 */ 

#include <avr/io.h>
#include "def_principais.h"
#include <avr/interrupt.h>

#define LED PB5
ISR(INT0_vect);
ISR(INT1_vect);
int main()
{
	DDRD = 0x00; // PORTD entrada
	PORTD = 0xFF; // pull-ups habilitados
	DDRB = 0b00100000; // somente pino do LED como sa�da
	PORTB = 0b11011111; // desliga LED e habilita pull-ups
	EICRA = 1<<ISC01; // interrup. externas: INT0 na borda de descida, INT1 no n�vel zero.
	EIMSK = (1<<INT1)|(1<<INT0); // habilita as duas interrup��es
	sei(); // habilita interrup��es globais, ativando o bit I do SREG
	while(1){} // N�O FAZ NADA A N�O SER ESPERAR PELAS INTERRUP��ES!
}
//-----------------------------------------------------------------------------------
ISR(INT0_vect) //interrup��o externa 0, quando o bot�o � pressionado o LED troca de estado
{
	cpl_bit(PORTB,LED);
}
//-----------------------------------------------------------------------------------
ISR(INT1_vect) //interrup��o externa 1, mantendo o bot�o pressionado o LED pisca
{
	cpl_bit(PORTB,LED);
	_delay_ms(200); //tempo para piscar o LED
}
