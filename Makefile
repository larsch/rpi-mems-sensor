CFLAGS = -Wall -ggdb
test: test.o sensor.o
	gcc -o test test.o sensor.o -lbcm2835

sensor.so:
	gcc -fpic -shared -o sensor.so sensor.c

clean:
	rm *.o test
