#include "Includes.h"

/* Printf use the USART1 */
#define UART_NUM USART1

int fputc(int ch, FILE *f)
{
	USART_SendData(UART_NUM, (u8) ch);

	while(!(USART_GetFlagStatus(UART_NUM, USART_FLAG_TXE) == SET))
	{
	}

	return ch;
}

int fgetc(FILE *f)
{
	while(!(USART_GetFlagStatus(UART_NUM, USART_FLAG_RXNE) == SET))
	{
	}

	return (USART_ReceiveData(UART_NUM));
}

