#ifndef __IIC_H
#define __IIC_H

#define IIC_GPIO_PORT      GPIOB
#define IIC_SDA_GPIO_PIN   GPIO_Pin_12
#define IIC_SCL_GPIO_PIN   GPIO_Pin_11

#define IIC_SDA_L   GPIO_ResetBits(IIC_GPIO_PORT, IIC_SDA_GPIO_PIN)
#define IIC_SDA_H   GPIO_SetBits(  IIC_GPIO_PORT, IIC_SDA_GPIO_PIN)

#define IIC_SCL_L   GPIO_ResetBits(IIC_GPIO_PORT, IIC_SCL_GPIO_PIN)
#define IIC_SCL_H   GPIO_SetBits(  IIC_GPIO_PORT, IIC_SCL_GPIO_PIN)

#define IIC_SDA     GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA_GPIO_PIN)

#define IIC_OVER_TIME  2000

typedef enum
{
	I2C_OK = 0,
	I2C_FAIL = !I2C_OK
} I2c_State;

extern void i2c_init(void);
extern u8 i2c_read_single_byte(u8 addr, u8 cmd, vu8 * data);
extern u8 i2c_write_single_byte(u8 addr, u8 cmd, vu8 * data);

#endif

