# STM32 平衡小车项目

基于 STM32F103C8T6 微控制器的平衡小车项目，使用 MPU6050 传感器进行姿态检测，通过 PID 算法实现小车的平衡控制。

## ✨ 功能特点

- 🤖 自平衡能力 - 实时 PID 控制
- 📡 多种控制方式 - 蓝牙/NRF24L01
- 📱 实时数据显示 - OLED 屏幕
- 🔧 自定义 PCB 设计 - 稳定可靠
- 📦 模块化设计 - 易于维护

## 📦 安装

### 硬件准备

1. STM32F103C8T6 开发板
2. MPU6050 传感器
3. TB6612FNG 电机驱动
4. OLED 显示屏
5. 直流电机带编码器

### 软件环境

1. 安装 STM32CubeIDE 或 Keil MDK
2. 安装 Python 3.x（用于上位机）
3. 安装依赖：
```bash
pip install pyserial matplotlib
```
## 🚀 使用方法

### 烧录固件

1. 使用 ST-Link 连接开发板
2. 编译项目
3. 烧录到 STM32

### 上位机使用

```bash
python 上位机/balance_car_gui.py
```

### PID 参数调整

通过串口发送命令调整 PID 参数：
```
Kp:10.5
Ki:0.1
Kd:2.0
```
## 🛠️ 技术栈

- C
- STM32
- PID Control
- MPU6050
- Python

## 📁 目录结构

```
STM32_Balance_Car/
├── src/              # 源代码目录
├── docs/             # 文档目录
├── tests/            # 测试文件
├── examples/         # 示例代码
├── README.md         # 项目说明
└── .gitignore        # Git 忽略文件
```

## ⚠️ 注意事项

首次使用请先在安全环境下测试平衡参数。
## 📄 许可证

本项目采用 MIT 许可证 - 详见 LICENSE 文件
