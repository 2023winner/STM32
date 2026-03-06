#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "PWM.h"
#include "Motor.h"
#include "PID.h"

float Pitch,Roll,Yaw;								//欧拉角，默认初始值为0，分别是：俯仰角、横滚角、偏航角
int16_t ax,ay,az,gx,gy,gz;							//加速度计和陀螺仪原始数据
int8_t Buf[32];
uint8_t KeyNum,avoid = 0;

u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

int main(void)
{


	OLED_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	PWM_Init();
	Wheel_Control_GPIO_Init();
	
	// 设置PID参数
	PID_Set_Params(3.0, 0.05, 0.5);
	// 设置目标角度（平衡位置）
	PID_Set_Target_Angle(0);
	
	while (1)
	{
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);						//获取动态数据
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		MPU_Get_Accelerometer(&ax,&ay,&az);
		
		// 计算PID输出
		int16_t pid_output = PID_Calculate(Pitch, gx);
		
		// 控制电机
		if (pid_output > 0)
		{
			// 向前
			Wheel1_Set(1, pid_output);
			Wheel2_Set(1, pid_output);
		}
		else if (pid_output < 0)
		{
			// 向后
			Wheel1_Set(0, -pid_output);
			Wheel2_Set(0, -pid_output);
		}
		else
		{
			// 停止
			Stop();
		}
		
		OLED_ShowSignedNum(2, 1, Pitch, 5);
		OLED_ShowSignedNum(3, 1, Roll, 5);
		OLED_ShowSignedNum(4, 1, Yaw, 5);
		OLED_ShowSignedNum(1, 8, pid_output, 5);
			
		Delay_ms(38);//延时38ms，与MPU6050采样频率同步
	}
}
