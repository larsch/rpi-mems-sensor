#!/bin/bash -e
(echo "struct p { int16_t x, y, z; };"; cproto $1.c) > $1.h
gcc -shared $1.c -o /tmp/$1.so
wdiff \
  -n -w $'\e[31m' -x $'\e[0m' -y $'\e[32m' -z $'\e[0m' \
  <(objdump -d ../rpi_sensor_board/sensor.so | awk "/<$2>/,/^$/" | cut -f2-) \
  <(objdump -d /tmp/$1.so | awk "/<$2>/,/^$/" | cut -f2-)
