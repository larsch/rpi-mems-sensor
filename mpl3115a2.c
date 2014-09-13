#include <bcm2835.h>

void MPL3115A2_WRITE_REGISTER(uint8_t reg, uint8_t value)
{
	char buf[2] = { reg, value };
	bcm2835_i2c_setSlaveAddress(0x60);
	bcm2835_i2c_write(buf, 2);
}

uint8_t MPL3115A2_READ_REGISTER(uint8_t reg)
{
	char buf[1];
	char regaddr = reg;
	bcm2835_i2c_setSlaveAddress(0x60);
	bcm2835_i2c_read_register_rs(&regaddr, buf, 1);
	return buf[0];
}

void MPL3115A2_Active()
{
	uint8_t v = MPL3115A2_READ_REGISTER(0x26);
	v = v | 0x01;
	MPL3115A2_WRITE_REGISTER(0x26, v);
}

void MPL3115A2_Standby()
{
	uint8_t v = MPL3115A2_READ_REGISTER(0x26);
	v = v & ~0x01;	
	MPL3115A2_WRITE_REGISTER(0x26, v);
}

uint8_t MPL3115A2_Initialized = 0;

void MPL3115A2_Init_Alt()
{
	MPL3115A2_Initialized = 0;
	uint32_t b = 0x000009c4;
	bcm2835_i2c_begin();
	bcm2835_i2c_setClockDivider(b);
	uint32_t c = MPL3115A2_READ_REGISTER(12);
	if (c == 0xc4)
	{
		MPL3115A2_Initialized = 1;
		MPL3115A2_WRITE_REGISTER(0x26, 0xb8);
		MPL3115A2_WRITE_REGISTER(0x27, 0x00);
		MPL3115A2_WRITE_REGISTER(0x28, 0x17);
		MPL3115A2_WRITE_REGISTER(0x29, 0x00);
		MPL3115A2_WRITE_REGISTER(0x2a, 0x00);
		MPL3115A2_WRITE_REGISTER(0x13, 0x07);	
	}
}

int MPL3115A2_Read_Alt()
{
	int a = 0;
	if (MPL3115A2_Initialized == 1) {
		a = MPL3115A2_READ_REGISTER(0x01);
		a <<= 8;
		int b = MPL3115A2_READ_REGISTER(0x02);
		a = a + b;
		a <<= 8;
		int c = MPL3115A2_READ_REGISTER(0x03);
		a = a + c;
	}
	return a;
}

void MPL3115A2_Init_Bar()
{
	bcm2835_i2c_begin();
	bcm2835_i2c_setClockDivider(0x9c4);
	uint8_t c = MPL3115A2_READ_REGISTER(12);
	if (c == 0xc4) {
		MPL3115A2_Initialized = 1;
		MPL3115A2_WRITE_REGISTER(0x26, 0x38);
		MPL3115A2_WRITE_REGISTER(0x27, 0x00);
		MPL3115A2_WRITE_REGISTER(0x28, 0x11);
		MPL3115A2_WRITE_REGISTER(0x29, 0x00);
		MPL3115A2_WRITE_REGISTER(0x2a, 0x00);
		MPL3115A2_WRITE_REGISTER(0x13, 0x07);
	}
}

int MPL3115A2_Read_Temp() {
	int a = 0;
	if (MPL3115A2_Initialized == 1) {
		a = (MPL3115A2_READ_REGISTER(0x04) << 8) + MPL3115A2_READ_REGISTER(0x05);
	}
	return a;
}
