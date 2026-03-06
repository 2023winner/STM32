@echo off

REM 构建和烧录STM32平衡小车项目

echo ===================================
echo STM32平衡小车构建和烧录脚本
echo ===================================

REM 检查是否安装了ARM GCC工具链
where arm-none-eabi-gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo 错误：未找到ARM GCC工具链，请先安装
    echo 建议安装：GNU Arm Embedded Toolchain
    echo 下载地址：https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
    pause
    exit /b 1
)

echo 找到ARM GCC工具链

REM 检查是否安装了STM32CubeProgrammer
where STM32_Programmer_CLI >nul 2>nul
if %errorlevel% neq 0 (
    echo 警告：未找到STM32CubeProgrammer，将无法烧录
    echo 建议安装：STM32CubeProgrammer
    echo 下载地址：https://www.st.com/en/development-tools/stm32cubeprog.html
)

REM 构建项目
echo.
echo 正在构建项目...
make clean
make all

if %errorlevel% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

echo 构建成功！

REM 烧录项目
echo.
echo 正在烧录项目...
echo 请确保STM32开发板已通过SWD连接到电脑

where STM32_Programmer_CLI >nul 2>nul
if %errorlevel% equ 0 (
    STM32_Programmer_CLI -c port=SWD -w balance_car.hex -v -rst
    if %errorlevel% neq 0 (
        echo 烧录失败！
        pause
        exit /b 1
    )
    echo 烧录成功！
) else (
    echo 跳过烧录：未找到STM32CubeProgrammer
    echo 请使用其他烧录工具烧录 balance_car.hex 文件
)

echo.
echo 操作完成！
pause
