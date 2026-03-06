#ifndef __MOTOR_H_
#define __MOTOR_H_

void Wheel_Control_GPIO_Init(void);
void Goforward(uint8_t speed);
void Stop(void);
void Turnleft_round(uint8_t speed);
void Turnright_round(uint8_t speed);
void Dir_TurnLeft(uint8_t speed);
void Dir_TurnRight(uint8_t speed);
void Go_Right(uint8_t speed,uint8_t gap);
void Go_Left(uint8_t speed,uint8_t gap);
void Backward(uint8_t speed);
void MPU_6050_Contral(void);
void Wheel1_Set(uint8_t mode , uint8_t speed);
void Wheel2_Set(uint8_t mode , uint8_t speed);
void Wheel3_Set(uint8_t mode , uint8_t speed);
void Wheel4_Set(uint8_t mode , uint8_t speed);
#endif
