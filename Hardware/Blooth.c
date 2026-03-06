#include "stm32f10x.h"  // 包含STM32的标准外设库头文件，根据你的STM32型号可能有所不同

// USART3初始化函数
void USART3_Configuration(void) {
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能USART3和GPIOB的时钟（假设TX在PB10，RX在PB11）
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置USART3的TX（PB10）为复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置USART3的RX（PB11）为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置USART3的参数，例如波特率9600，8位数据位，1个停止位，无奇偶校验
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    // 使能USART3
    USART_Cmd(USART3, ENABLE);
}

void USART3_SendChar(char data) {
    USART_SendData(USART3, (uint8_t)data);
    // 等待发送完成
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

void USART3_SendString(char *str) {
    while (*str) {
        USART3_SendChar(*str++);
    }
}

// 发送一个int8_t类型的数字
void USART3_SendInt8(int8_t data) {
    // 直接将int8_t数据作为字节发送
    USART_SendData(USART3, (uint8_t)data);
    // 等待发送完成
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

// 将单个int8_t数字转换为ASCII字符串并发送
void USART3_SendInt8AsASCII(int8_t number) {
    char buffer[5];  // 足够大以容纳数字、负号和终止符
    char *ptr = buffer + 4;  // 从缓冲区末尾开始填充
    *ptr = '\0';  // 添加字符串终止符

    // 处理负数情况
    if (number < 0) {
        USART3_SendChar('-');
        number = -number;
    }

    // 将数字转换为ASCII字符串
    do {
        *--ptr = (char)(number % 10) + '0';
        number /= 10;
    } while (number > 0);

    // 发送ASCII字符串
    USART3_SendString(ptr);
}

// 将单个int16_t数字转换为ASCII字符串并发送
void USART3_SendInt16AsASCII(int16_t number) {
    char buffer[7];  // 足够大以容纳-32768到32767之间的数字、负号、终止符
    char *ptr = buffer + 6;  // 从缓冲区末尾开始填充
    *ptr = '\0';  // 添加字符串终止符

    // 处理负数情况
    if (number < 0) {
        USART3_SendChar('-');
        number = -number;
    }

    // 将数字转换为ASCII字符串
    do {
        *--ptr = (char)(number % 10) + '0';
        number /= 10;
    } while (number > 0);

    // 发送ASCII字符串
    USART3_SendString(ptr);
}


