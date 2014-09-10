#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "mpl3115a2.h"
#include <bcm2835.h>

double getAlt() {
	int v = MPL3115A2_Read_Alt();
	printf("raw alt = %u\n", v);
	int alt_m = v >> 8;
	int alt_l = v & 0xff;
	if (alt_m & 0x8000) alt_m = alt_m - 65536;
	double frac = alt_l / 256.0;
	return alt_m + frac;	
}

double getBar() {
	int v = MPL3115A2_Read_Alt();
	int alt_m = v >> 6;
	int alt_l = v & 0x30;
	return alt_m + alt_l / 64.0;
}

double getTemp() {
	int t = MPL3115A2_Read_Temp();
	int t_m = (t >> 8) & 0xFF;
	int t_l = t & 0xFF;
	if (t_m > 0x7f) t_m = t_m - 256;
	return t_m + t_l / 256.0;
}

int main() {
	bcm2835_init();
	MPL3115A2_Init_Alt();
//	MPL3115A2_Init_Bar();
	MPL3115A2_Active();	
	sleep(1);
	for (;;) {
		printf("alt: %f, temp: %f\n", getAlt(), getTemp());
		//printf("bar: %f Pa, temp: %f\n", getBar(), getTemp());
		usleep(100000);
	}
	return 0;
}
