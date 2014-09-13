CFLAGS = -Wall
CC = gcc

# Uncomment this for Raspberry V1
# CFLAGS += -DI2C_V1

SENSOR_SRC = mpl3115a2.c mma8491q.c mag3110.c
SENSOR_OBJ = $(SENSOR_SRC:.c=.o)
SENSOR_HDR = $(SENSOR_SRC:.c=.h)

all: libmemssensor.a

headers: $(SENSOR_HDR)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.h: %.c
	cproto $< > $@

libmemssensor.a: $(SENSOR_OBJ)
	ar r $@ $(SENSOR_OBJ)

sensor.so: bcm2835.c $(SENSOR_SRC) Makefile
	$(CC) $(CFLAGS) -fpic -shared -o sensor.so $(SENSOR_SRC) bcm2835.c

clean:
	rm -f $(SENSOR_OBJ) sensor.so libmemssensor.a test
