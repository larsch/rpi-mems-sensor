CFLAGS = -Wall -ggdb
CC = gcc

SENSOR_SRC = mpl3115a2.c
SENSOR_OBJ = $(SENSOR_SRC:.c=.o)

test: test.o $(SENSOR_OBJ)
	$(CC) -o test test.o $(SENSOR_OBJ) -lbcm2835

sensor.so: ../bcm2835-1.36/src/bcm2835.c $(SENSOR_SRC)
	$(CC) -fpic -shared -o sensor.so $(SENSOR_SRC) ../bcm2835-1.36/src/bcm2835.c

clean:
	rm *.o test
