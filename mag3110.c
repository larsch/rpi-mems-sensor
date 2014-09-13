#include <stdint.h>
#include <stdlib.h>
#include "mag3110.h"
#include <bcm2835.h>

int MAG3110_WRITE_REGISTER(char reg, char val) {
	char x = reg;
	char c = val;
	bcm2835_i2c_setSlaveAddress(14);
	bcm2835_i2c_write(&x, 2);
}

char MAG3110_READ_REGISTER(char reg) {
	char* ch = malloc(1);
	bcm2835_i2c_setSlaveAddress(14);
	bcm2835_i2c_read_register_rs(&reg, ch, 1);
	return ch[0];
}

int MAG3110_BULK_READ(char reg, char count, char* data) {
	bcm2835_i2c_setSlaveAddress(14);
	bcm2835_i2c_read_register_rs(&reg, data, count);
	return *data;
}

char MAG3110_Initialized = 0;

int MAG3110_Init() {
	char v = 0;
	bcm2835_i2c_begin();
	bcm2835_i2c_setClockDivider(2500);
	MAG3110_WRITE_REGISTER(16, 0);
	v = MAG3110_READ_REGISTER(7);
	if (v == 0xc4) {
		MAG3110_WRITE_REGISTER(17, 128);
		MAG3110_Initialized = 1;
	}
	return MAG3110_Initialized;
}

char MAG3110_ReadRawData(char* data) {
	char a = 0;
	short b = 0;
	if (MAG3110_Initialized == 1) {
		MAG3110_WRITE_REGISTER(17, 128);
		MAG3110_WRITE_REGISTER(16, 2);
		do {
			a = MAG3110_READ_REGISTER(0);
		} while ((a & 7) != 7);
		MAG3110_BULK_READ(1, 6, data);
	}
	return 1;
}

int MAG3110_ReadAsInt() {
	/* not used from Python script */
	return 0;
}

int16_t MAG3110_ReadRawData_x() {
	char r = 0;
	int16_t a = 0;
	if (MAG3110_Initialized == 1) {
		a = MAG3110_READ_REGISTER(1);
		a = MAG3110_READ_REGISTER(2);
		MAG3110_WRITE_REGISTER(17, 128);
		MAG3110_WRITE_REGISTER(16, 2);
		do {
			r = MAG3110_READ_REGISTER(0);
		} while (!(r & 1));
		a = MAG3110_READ_REGISTER(1);
		a = a << 8;
		a = a + MAG3110_READ_REGISTER(2);
	}	
	return a;
}

int16_t MAG3110_ReadRawData_y() {
	char r = 0;
	int16_t a = 0;
	if (MAG3110_Initialized == 1) {
		a = MAG3110_READ_REGISTER(3);
		a = MAG3110_READ_REGISTER(4);
		MAG3110_WRITE_REGISTER(17, 128);
		MAG3110_WRITE_REGISTER(16, 2);
		do {
			r = MAG3110_READ_REGISTER(0);
		} while (!(r & 2));
		a = MAG3110_READ_REGISTER(3);
		a = a << 8;
		a = a + MAG3110_READ_REGISTER(4);
	}	
	return a;
}

int16_t MAG3110_ReadRawData_z() {
	char r = 0;
	int16_t a = 0;
	if (MAG3110_Initialized == 1) {
		a = MAG3110_READ_REGISTER(5);
		a = MAG3110_READ_REGISTER(6);
		MAG3110_WRITE_REGISTER(17, 128);
		MAG3110_WRITE_REGISTER(16, 2);
		do {
			r = MAG3110_READ_REGISTER(0);
		} while (!(r & 4));
		a = MAG3110_READ_REGISTER(5);
		a = a << 8;
		a = a + MAG3110_READ_REGISTER(6);
	}	
	return a;
}
