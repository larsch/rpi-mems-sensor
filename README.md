# MEMS Sensor Evaluation Board C Library

This is a Raspberry Pi C library for the MEMS Sensor Board with the 3 Xtrinsic
sensors:

  * High-Precision Pressure Sensor (MPL3115A2)
  * Low-power 3D Magnetometer (MAG3110)
  * 3-Axis, Digital Accelerometer (MMA8491Q)

## Links

  * [Element 14 Community Page for the MEMS Sensor Board](http://www.element14.com/community/community/designcenter/mems-sensor-board)
  * [Git Repo with script and binary-only sensor.so](http://git.oschina.net/embest/rpi_sensor_board.git)

## How to use from C

  1. Run make to build `libmemssensor.a`
  2. Link and use this library

## How to re-build sensor.so for use with Python scripts

  1. Download and extract the [bcm2835 library](http://www.airspayce.com/mikem/bcm2835/).
  2. Copy the bcm2835.c source file into the directory with this library
  3. Run `make sensor.so`.

## Using with Raspberry Pi Version 1.0

  * `bcm2835.c` needs to be compiled with `-DI2C_V1`.
  * Either edit `bcm2835.c` or add the flags in `Makefile`.

## Background

This is a reverse engineed binary-compatible version of `sensor.so` originally
found on the Raspbian image for the sensor board.

The download link to the Raspbian Image on element14.com has gone missing, but
the `sensor.so` library can be found in [this
git repository](http://git.oschina.net/embest/rpi_sensor_board.git).

The sensor.so file is a binary blob, based on the
[bcm2835](http://www.airspayce.com/mikem/bcm2835/), which is GPL licensed. So
the binary blob is in full GPL violation.

The original `sensor.so` is compiled for Raspberry V2.0 and does not work with
V1.0 boards due to a number change on the GPIO pins for I2C. To use with a V1.0
board, a define (`-DI2C_V1`) need to be set when compiling the bcm2835 library.
This can done in `bcm2835.c` or in my Makefile.

I disassembled `sensor.so` and reimplemented the functions in C, with
practically exact result at the assembly level when compiled. I compare the
disassembly output of the `sensor.so` with the output of my compiled C code for
an exact match. I tested using the original Python scripts and everything seems
to be working.

I kept everything minimal and as accurate to the original binary `sensor.so` as
possible, even with bugs and compiler warnings.

## License

Copyright (c) 2014 Lars Christensen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
