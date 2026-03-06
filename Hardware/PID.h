#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"

// PID控制计算
int16_t PID_Calculate(float current_angle, float gyro_rate);

// 设置PID参数
void PID_Set_Params(float p, float i, float d);

// 设置目标角度
void PID_Set_Target_Angle(float angle);

// 设置角度校准值
void PID_Set_Angle_Offset(float offset);

// 重置PID状态
void PID_Reset(void);

#endif
