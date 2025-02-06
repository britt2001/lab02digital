/*
 * lab2.0.c
 *
 * Created: 2/5/2025 11:17:53 PM
 * Author : Britany Barillas
 */ 
#define F_CPU 16000000UL 
#include "ADC/ADC.h"
#include "LCD/LCD.h"
#include "UART/UART.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void) {
	unsigned int adc_value1, adc_value2;
	int contador = 0;
	char buffer[16];
	char received_char;

	// Inicialización
	adc_init();
	lcd_init();
	uart_init(9600); // Inicializar UART con baudrate 9600

	while (1) {
		// Leer valores de los potenciómetros
		adc_value1 = adc_read(0); // Leer potenciómetro conectado a A0
		adc_value2 = adc_read(1); // Leer potenciómetro conectado a A1

		// Convertir valores a voltaje
		float voltage1 = adc_value1 * 5.0 / 1023; // Voltaje para A0
		float voltage2 = adc_value2 * 5.0 / 1023; // Voltaje para A1

		// Enviar datos al puerto UART
		snprintf(buffer, sizeof(buffer), "S1: %.2fV S2: %.2fV\r\n", voltage1, voltage2);
		uart_send_string(buffer);

		// Leer datos del UART
		if (UCSR0A & (1 << RXC0)) { // Verificar si hay datos disponibles
			received_char = uart_receive();
			if (received_char == '+') {
				contador++; // Incrementar contador
				} else if (received_char == '-') {
				contador--; // Decrementar contador
			}
		}

		// Mostrar valores en el LCD
		lcd_set_cursor(0, 0);
		snprintf(buffer, sizeof(buffer), "S1: %.2fV", voltage1);
		lcd_write_string(buffer);

		lcd_set_cursor(1, 0);
		snprintf(buffer, sizeof(buffer), "S2: %.2fV", voltage2);
		lcd_write_string(buffer);

		lcd_set_cursor(1, 10); // Mostrar contador como S3
		snprintf(buffer, sizeof(buffer), "S3: %d", contador);
		lcd_write_string(buffer);

		_delay_ms(500); // Actualizar cada 500ms
	}
}
