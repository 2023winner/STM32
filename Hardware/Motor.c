#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"

 //       1    2
//方向   B12   B14     	10
//方向   A5   A4 		2		B0 B1 


uint8_t speed,mode = 0;
extern int8_t Buf[32];

void Wheel_Control_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化
	
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure2.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStructure2.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure2);//初始化
}

 
//控制电机1的运动：mode为0是反转，1是正转，speed是速度值，最大值为1000
void Wheel1_Set(uint8_t mode,uint8_t speed)
{
	if(mode)//正转
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);//10
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//01
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
	}
	TIM_SetCompare3(TIM3,speed);
}

//控制电机2的运动：mode为0是反转，1是正转，speed是速度值，最大值为1000
void Wheel2_Set(uint8_t mode,uint8_t speed)
{
	if(mode)//正转
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);//10
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
	else
	{
	    GPIO_ResetBits(GPIOA,GPIO_Pin_5);//10
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	}
	TIM_SetCompare3(TIM2,speed);
 
}

//前进模式
void Goforward(uint8_t speed)
{
	Wheel1_Set(1,speed);
	Wheel2_Set(1,speed);
}

void Backward(uint8_t speed)
{
	Wheel1_Set(0,speed);
	Wheel2_Set(0,speed);
}

//停止
void Stop(void)
{
	Wheel1_Set(1,0);
	Wheel2_Set(1,0);
}

//原地左转
void Turnleft_round(uint8_t speed)
{
	Wheel1_Set(0,speed);
	Wheel2_Set(1,speed);
}

//原地右转
void Turnright_round(uint8_t speed)
{
	Wheel1_Set(1,speed);
	Wheel2_Set(0,speed);
}
 //直线左转
void Dir_TurnLeft(uint8_t speed)
{
	Wheel1_Set(1,0);
	Wheel2_Set(1,speed);
}
//直线右转
void Dir_TurnRight(uint8_t speed)
{
	Wheel1_Set(1,speed);
	Wheel2_Set(1,0);
}
//右侧通行
void Go_Right(uint8_t speed,uint8_t gap)
{
	Wheel1_Set(1,speed);
	Wheel2_Set(1,speed-gap);
}
//左侧通行
void Go_Left(uint8_t speed,uint8_t gap)
{
	Wheel1_Set(1,speed-gap);
	Wheel2_Set(1,speed);
}

void MPU_6050_Contral(void)
{
		if (Buf[1] > 0)//判断方向为前进还是后退
		{
			mode = 1;
		}
		else
		{
			mode = 0;
		}
		
		Wheel1_Set(mode,100 - Buf[0]);
		Wheel2_Set(mode,100 + Buf[0]);		
		OLED_ShowSignedNum(2, 1,100 - Buf[0], 5);
		OLED_ShowSignedNum(3, 1,100 + Buf[0], 5);
}
