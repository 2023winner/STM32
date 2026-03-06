#include "stm32f10x.h"                  // Device header
#include "mpu6050.h"

// PID参数
float Kp = 3.5;  // 比例系数
float Ki = 0.02; // 积分系数
float Kd = 0.8;  // 微分系数

// 角度偏差
float angle_error = 0;
float angle_error_last = 0;
float angle_error_sum = 0;

// 目标角度（平衡位置）
float target_angle = 0;

// 角度校准值
float angle_offset = 0;

// 积分限幅
#define INTEGRAL_LIMIT 100

// PID控制计算
int16_t PID_Calculate(float current_angle, float gyro_rate)
{
    // 应用角度校准
    current_angle -= angle_offset;
    
    // 计算角度偏差
    angle_error = current_angle - target_angle;
    
    // 计算积分项（带限幅）
    angle_error_sum += angle_error;
    if (angle_error_sum > INTEGRAL_LIMIT) angle_error_sum = INTEGRAL_LIMIT;
    if (angle_error_sum < -INTEGRAL_LIMIT) angle_error_sum = -INTEGRAL_LIMIT;
    
    // 计算微分项
    float angle_error_diff = angle_error - angle_error_last;
    
    // 保存当前偏差
    angle_error_last = angle_error;
    
    // PID计算
    float pid_output = Kp * angle_error + Ki * angle_error_sum + Kd * angle_error_diff;
    
    // 限制输出范围
    if (pid_output > 100) pid_output = 100;
    if (pid_output < -100) pid_output = -100;
    
    return (int16_t)pid_output;
}

// 设置PID参数
void PID_Set_Params(float p, float i, float d)
{
    Kp = p;
    Ki = i;
    Kd = d;
}

// 设置目标角度
void PID_Set_Target_Angle(float angle)
{
    target_angle = angle;
}

// 设置角度校准值
void PID_Set_Angle_Offset(float offset)
{
    angle_offset = offset;
}

// 重置PID状态
void PID_Reset(void)
{
    angle_error = 0;
    angle_error_last = 0;
    angle_error_sum = 0;
}
