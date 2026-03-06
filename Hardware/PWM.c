#include "stm32f10x.h"                  // Device header

//PWMB B0 TIM3_3
//PWMA A2 TIM2_3

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	
	//控制A发动机
	GPIO_InitTypeDef GPIOA_InitStructure;
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOA_InitStructure);
	
	TIM_InternalClockConfig(TIM2);//选择内部时钟模式
	TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStructure;//定义结构体
	TIM2_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频
	TIM2_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择向下计数
	TIM2_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR 自动重装数 计数器溢出频率：CK_CNT_OV = CK_CNT/(PSC + 1)/(ARR + 1)
	TIM2_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;//PSC 7200分频
	TIM2_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级计数器特有置零不用
	TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseInitStructure);

	TIM_OCInitTypeDef TIM2_OCInitStructure;
	TIM_OCStructInit(&TIM2_OCInitStructure);
	
	TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM2_OCInitStructure.TIM_Pulse = 0;   //CCR
	
    //控制B类发动机
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruvture;
	TIM_TimeBaseInitStruvture.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruvture.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruvture.TIM_Period=100-1;//ARR
	TIM_TimeBaseInitStruvture.TIM_Prescaler=36-1;//PSC
	TIM_TimeBaseInitStruvture.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruvture);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;    //CCR

    TIM_OC3Init(TIM2,&TIM_OCInitStructure);//初始化通道三
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//初始化通道三
	
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}
  