#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "sensor.h"
#include <bcm2835.h>

double getAlt() {
	int v = MPL3115A2_Read_Alt();
	int alt_m = v >> 8;
	int alt_l = v & 0xff;

	return ((v << 8) >> 8)/1000.0;
        
	double res;
	printf("%06x\n", v);
	if (alt_l > 99)
		res = alt_l / 1000.0;
	else
		res = alt_l / 100.0;
	return alt_m + res;
}

double getTemp() {
	int t = MPL3115A2_Read_Temp();
	int t_m = (t >> 8) & 0xFF;
	int t_l = t & 0xFF;
	double res;
	printf("%04x\n", t);
	return t_m + t_l / 256.0;
}

int main() {
	bcm2835_init();
	MPL3115A2_Init_Alt();
	MPL3115A2_Active();	
	sleep(1);
	for (;;) {
		printf("alt: %f, temp: %f\n", getAlt(), getTemp());
		usleep(100000);
	}
	return 0;
}
