#include "stm32f10x.h"

void USART3_Configuration(void);
void USART3_SendInt8(int8_t data);
void USART3_SendInt8AsASCII(int8_t number);
void USART3_SendInt16AsASCII(int16_t number);
void USART3_SendString(char *str);
