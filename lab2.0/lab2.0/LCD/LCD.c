/*
 * LCD.c
 *
 * Created: 2/5/2025 11:22:29 PM
 *  Author: Britany Barillas
 */ 

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

// Definición de pines
#define LCD_DATA PORTD
#define LCD_CTRL PORTB
#define RS PB0
#define EN PB1

void lcd_command(unsigned char cmd) {
	LCD_DATA = cmd;            // Enviar comando
	LCD_CTRL &= ~(1 << RS);    // RS en bajo para comando
	LCD_CTRL |= (1 << EN);     // Habilitar EN
	_delay_ms(2);
	LCD_CTRL &= ~(1 << EN);    // Deshabilitar EN
}

void lcd_write_char(char data) {
	LCD_DATA = data;           // Enviar datos
	LCD_CTRL |= (1 << RS);     // RS en alto para datos
	LCD_CTRL |= (1 << EN);     // Habilitar EN
	_delay_ms(2);
	LCD_CTRL &= ~(1 << EN);    // Deshabilitar EN
}

void lcd_write_string(const char *str) {
	while (*str) {
		lcd_write_char(*str++);
	}
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
	unsigned char pos[] = {0x80, 0xC0}; // Dirección inicial para filas 0 y 1
	lcd_command(pos[row] + col);
}

void lcd_init(void) {
	DDRD = 0xFF;               // Configurar PORTD como salida para datos
	DDRB = (1 << RS) | (1 << EN); // Configurar RS y EN como salida
	_delay_ms(20);             // Tiempo de inicio
	lcd_command(0x38);         // Modo 8 bits
	lcd_command(0x0C);         // Encender display, sin cursor
	lcd_command(0x06);         // Incrementar cursor
	lcd_command(0x01);         // Limpiar pantalla
}