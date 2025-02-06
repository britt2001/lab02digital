/*
 * LCD.h
 *
 * Created: 2/5/2025 11:22:14 PM
 *  Author: Britany Barillas
 */ 


#ifndef LCD_H
#define LCD_H

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_write_char(char data);
void lcd_write_string(const char *str);
void lcd_set_cursor(unsigned char row, unsigned char col);

#endif
