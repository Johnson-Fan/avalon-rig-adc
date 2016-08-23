#include "Includes.h"

static void i2c_delay(u32 t_us)
{
	vu32 i = 0;

	for (i = 0; i < t_us; i++)
		__ASM("NOP");
}

static void set_i2c_sda_out(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStructure);
}

static void set_i2c_sda_in(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStructure);
}

static void i2c_start(void)
{
	IIC_SDA_H;
	IIC_SCL_H;
	i2c_delay(2);
	IIC_SDA_L;
	i2c_delay(2);
	IIC_SCL_L;
	i2c_delay(1);
}

static void i2c_stop(void)
{
	IIC_SCL_L;
	i2c_delay(1);
	IIC_SDA_L;
	i2c_delay(1);
	IIC_SCL_H;
	i2c_delay(2);
	IIC_SDA_H;
	i2c_delay(1);
	IIC_SCL_L;
	i2c_delay(1);
}

static u8 i2c_ack(void)
{
	u32 tmp_err = 0;

	IIC_SCL_L;
	set_i2c_sda_in();
	i2c_delay(1);
	IIC_SCL_H;

	while (IIC_SDA) {
		if (++tmp_err > IIC_OVER_TIME) {
			set_i2c_sda_out();
			i2c_delay(1);
			i2c_stop();
			return (I2C_FAIL);
		}
	}

	i2c_delay(1);
	IIC_SCL_L;
	set_i2c_sda_out();
	i2c_delay(1);

	return(I2C_OK);
}

static void i2c_send_noack(void)
{
	IIC_SCL_L;
	IIC_SDA_H;
	i2c_delay(2);
	IIC_SCL_H;
	i2c_delay(2);
	IIC_SCL_L;
	i2c_delay(1);
}

static void i2c_send_byte(u8 data)
{
	u8 i = 0;

	for (i = 0; i < 8; i++) {
		IIC_SCL_L;
		i2c_delay(2);
		if (data & 0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;

		i2c_delay(2);
		IIC_SCL_H;
		data <<= 1;
		i2c_delay(2);
	}

	IIC_SCL_L;
	i2c_delay(1);
}

static u8 i2c_receive_byte(void)
{
	u8 i = 0;
	u8 tmp_dt = 0;

	IIC_SCL_L;
	IIC_SDA_H;
	set_i2c_sda_in();
	i2c_delay(1);

	for (i = 0; i < 0x08; i++) {
		tmp_dt <<= 0x01;
		IIC_SCL_H;
		i2c_delay(2);
		if (IIC_SDA)
			tmp_dt |= 0x01;

		IIC_SCL_L;
		i2c_delay(2);
	}

	set_i2c_sda_out();
	IIC_SDA_H;
	i2c_delay(1);

	return (tmp_dt);
}

void i2c_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_GPIO_PIN | IIC_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStructure);

	GPIO_ResetBits(IIC_GPIO_PORT, IIC_SCL_GPIO_PIN);
	GPIO_SetBits(IIC_GPIO_PORT, IIC_SDA_GPIO_PIN);
}

u8 i2c_read_single_byte(u8 addr, u8 cmd, u8 *data)
{
	u8 ack = 0;

	i2c_start();
	i2c_send_byte(addr);
	ack = i2c_ack();
	if (ack != I2C_OK)
		return I2C_FAIL;

	i2c_send_byte(cmd);
	ack = i2c_ack();
	if (ack != I2C_OK)
		return I2C_FAIL;

	i2c_start();
	i2c_send_byte(addr + 1);
	ack = i2c_ack();
	if (ack != I2C_OK)
		return I2C_FAIL;

	*data = i2c_receive_byte();
	i2c_send_noack();
	i2c_stop();

	return I2C_OK;
}

u8 i2c_write_single_byte(u8 addr, u8 cmd, u8 *data)
{
	u8 ack = 0;

	i2c_start();
	i2c_send_byte(addr);
	ack = i2c_ack();
	if (ack != I2C_OK)
		return I2C_FAIL;

	i2c_send_byte(cmd);
	ack = i2c_ack();
	if (ack != I2C_OK)
		return I2C_FAIL;

	i2c_send_byte(*data);
	ack = i2c_ack();
	if (ack != I2C_OK)
		return I2C_FAIL;

	i2c_stop();

	return (I2C_OK);
}

