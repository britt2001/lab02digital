/*
 * UART.h
 *
 * Created: 2/6/2025 3:29:36 PM
 *  Author: Britany Barillas
 */ 


#ifndef UART_H
#define UART_H

void uart_init(unsigned int baudrate);
void uart_transmit(char data);
char uart_receive(void);
void uart_send_string(const char *str);

#endif
