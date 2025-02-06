/*
 * UART.c
 *
 * Created: 2/6/2025 3:29:47 PM
 *  Author: Britany Barillas
 */ 
#define F_CPU 16000000UL
#include "uart.h"
#include <avr/io.h>

void uart_init(unsigned int baudrate) {
	unsigned int ubrr = (F_CPU / (16UL * baudrate)) - 1; // Calcular UBRR
	UBRR0H = (unsigned char)(ubrr >> 8); // Parte alta
	UBRR0L = (unsigned char)ubrr;       // Parte baja
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Habilitar transmisión y recepción
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits de datos, 1 bit de parada
}

void uart_transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0))); // Esperar que el buffer esté vacío
	UDR0 = data;                      // Enviar datos
}

char uart_receive(void) {
	while (!(UCSR0A & (1 << RXC0))); // Esperar a recibir datos
	return UDR0;                     // Retornar datos recibidos
}

void uart_send_string(const char *str) {
	while (*str) {
		uart_transmit(*str++);
	}
}
