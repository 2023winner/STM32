# STM32平衡小车项目

## 项目简介
这是一个基于STM32F103C8T6微控制器的平衡小车项目，使用MPU6050传感器进行姿态检测，通过PID算法实现小车的平衡控制。

## 硬件组成
- STM32F103C8T6主控板
- MPU6050六轴传感器
- 直流电机（带编码器）
- TB6612FNG电机驱动模块
- OLED显示屏
- 蓝牙模块（可选）
- NRF24L01无线模块（可选）
- 自定义PCB板（基于TPS54335ADDA电源方案）

## 软件功能
- 姿态检测与平衡控制
- 电机速度控制
- OLED显示（姿态数据、速度等）
- 蓝牙通信（可选）
- 无线遥控（可选）

## 项目结构
```
├── Hardware/         # 硬件驱动模块
│   ├── Mpu6050/      # MPU6050传感器驱动
│   ├── Motor.c/h     # 电机控制
│   ├── PID.c/h       # PID算法
│   ├── PWM.c/h       # PWM生成
│   ├── OLED.c/h      # OLED显示
│   └── 其他硬件驱动
├── Library/          # STM32标准库
├── Start/            # 启动文件
├── System/           # 系统相关
├── User/             # 用户代码
│   └── main.c        # 主函数
├── .gitignore        # Git忽略文件
├── Makefile          # 编译配置
├── project.uvprojx   # Keil项目文件
└── README.md         # 项目说明
```

## 编译与烧录
1. 使用Keil MDK-ARM打开`project.uvprojx`文件
2. 编译项目生成`balance_car.hex`文件
3. 使用ST-Link或其他编程器烧录到STM32开发板

## 控制方式
- 可通过蓝牙APP进行控制
- 可通过NRF24L01无线模块进行控制
- 可通过按键进行简单控制

## 注意事项
- 首次使用需要调整PID参数以获得最佳平衡效果
- 确保电机驱动电路连接正确
- 锂电池供电时注意安全

## 声明
- MPU6050姿态解算代码来源于网络，如有侵权，请联系我删除

## 许可证
MIT License

## 贡献
欢迎提交Issue和Pull Request来改进这个项目！

## PCB设计
- 项目使用自定义PCB板，基于TPS54335ADDA电源方案
- 包含完整的硬件设计，包括电源部分、电机驱动、MPU6050等
- PCB设计已在嘉立创开源硬件平台发布

## 嘉立创项目链接
- [32平衡小车（TPS54335ADDA）](https://oshwhub.com/2023asdxc/32-ping-heng-xiao-che-tps54335adda)

## 注意事项
- 电机要求带有编码器，单纯的步进电机无法实现该项目
- 安装电机时请注意安装孔与所购买电机的安装孔是否一致
- PCB设计使用STLINK进行烧录