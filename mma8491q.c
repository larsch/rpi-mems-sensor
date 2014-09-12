#include <stdint.h>
#include "mma8491q.h"
#include <bcm2835.h>
#include <stdio.h>

int MMA8491Q_Enable() {
	if (bcm2835_init() == 0)  {
		return 1;
	} else {
		bcm2835_gpio_fsel(25, 1);
		bcm2835_gpio_write(25, 1);
		return 0;
	}
}

int MMA8491Q_DisEnable() {
	if (bcm2835_init() == 0) {
		return 1;
	} else {
		bcm2835_gpio_fsel(25, 1);
		bcm2835_gpio_write(25, 0);
		return 0;
	}
}

void MMA8491Q_WRITE_REGISTER() {
	/* tbd */	
}

void MMA8491Q_READ_REGISTER() {
	/* tbd */
}

int MMA8491Q_BULK_READ(char a, char b, char* c) {
	if (!bcm2835_init()) {
		return 1;
	} else {
		bcm2835_i2c_begin();
		bcm2835_i2c_setClockDivider(0x9c4);
		bcm2835_i2c_setSlaveAddress(0x55);
		bcm2835_i2c_read_register_rs(&a, c, b);
		return *c;
	}
}

int MMA8491Q_Init() {
	return 1;
}

int MMA8491_ReadRaw(char* data) {
	char r = 0;
	MMA8491Q_Enable();
	MMA8491Q_BULK_READ(1, 6, data);
	MMA8491Q_DisEnable();
	return 1;
}

int MMA8491_Read(struct p* xyz) {
	char a[8] = { 0 };
	if (MMA8491_ReadRaw((char*)a) == 1) {
		xyz->x = a[0];
		xyz->x <<= 8;
		xyz->x += a[1];
		xyz->x >>= 2;

		xyz->y = a[2];
		xyz->y <<= 8;
		xyz->y += a[3];
		xyz->y >>= 2;

		xyz->z = a[4];
		xyz->z <<= 8;
		xyz->z += a[5];
		xyz->z >>= 2;
	}
	return 1;
}
