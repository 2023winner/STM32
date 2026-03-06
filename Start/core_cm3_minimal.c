#include <stdint.h>

/* 最小化的core_cm3实现，只包含必要的函数 */

/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
uint32_t __get_MSP(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, msp" : "=r" (result));
    return result;
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
void __set_MSP(uint32_t topOfMainStack)
{
    __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack));
}

/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
uint32_t __get_PSP(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, psp" : "=r" (result));
    return result;
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
void __set_PSP(uint32_t topOfProcStack)
{
    __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack));
}

/**
 * @brief  Return the Base Priority value
 *
 * @return BasePriority
 *
 * Return the content of the base priority register
 */
uint32_t __get_BASEPRI(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, basepri_max" : "=r" (result));
    return result;
}

/**
 * @brief  Set the Base Priority value
 *
 * @param  basePri  BasePriority
 *
 * Set the base priority register
 */
void __set_BASEPRI(uint32_t basePri)
{
    __asm volatile ("MSR basepri, %0" : : "r" (basePri));
}

/**
 * @brief  Return the Priority Mask value
 *
 * @return PriMask
 *
 * Return state of the priority mask bit from the priority mask register
 */
uint32_t __get_PRIMASK(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, primask" : "=r" (result));
    return result;
}

/**
 * @brief  Set the Priority Mask value
 *
 * @param  priMask  PriMask
 *
 * Set the priority mask bit in the priority mask register
 */
void __set_PRIMASK(uint32_t priMask)
{
    __asm volatile ("MSR primask, %0" : : "r" (priMask));
}

/**
 * @brief  Return the Fault Mask value
 *
 * @return FaultMask
 *
 * Return the content of the fault mask register
 */
uint32_t __get_FAULTMASK(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, faultmask" : "=r" (result));
    return result;
}

/**
 * @brief  Set the Fault Mask value
 *
 * @param  faultMask  faultMask value
 *
 * Set the fault mask register
 */
void __set_FAULTMASK(uint32_t faultMask)
{
    __asm volatile ("MSR faultmask, %0" : : "r" (faultMask));
}

/**
 * @brief  Return the Control Register value
 * 
 * @return Control value
 *
 * Return the content of the control register
 */
uint32_t __get_CONTROL(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, control" : "=r" (result));
    return result;
}

/**
 * @brief  Set the Control Register value
 *
 * @param  control  Control value
 *
 * Set the control register
 */
void __set_CONTROL(uint32_t control)
{
    __asm volatile ("MSR control, %0" : : "r" (control));
}

/**
 * @brief  Reverse byte order in integer value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in integer value
 */
uint32_t __REV(uint32_t value)
{
    uint32_t result;
    __asm volatile ("rev %0, %1" : "=r" (result) : "r" (value));
    return result;
}

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in unsigned short value
 */
uint32_t __REV16(uint16_t value)
{
    uint32_t result;
    __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value));
    return result;
}

/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
int32_t __REVSH(int16_t value)
{
    int32_t result;
    __asm volatile ("revsh %0, %1" : "=r" (result) : "r" (value));
    return result;
}
