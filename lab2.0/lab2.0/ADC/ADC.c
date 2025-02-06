/*
 * ADC.c
 *
 * Created: 2/5/2025 11:20:55 PM
 *  Author: Britany Barillas
 */ 

#include "adc.h"
#include <avr/io.h>

void adc_init(void) {
	ADMUX = (1 << REFS0); // Referencia AVCC
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Habilitar ADC, prescaler 64
}

unsigned int adc_read(unsigned char channel) {
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // Seleccionar canal (0-7)
	ADCSRA |= (1 << ADSC); // Iniciar conversión
	while (ADCSRA & (1 << ADSC)); // Esperar que termine
	return ADC;
}
