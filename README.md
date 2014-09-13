# MEMS Sensor Evaluation Board C Library

This is a Raspberry Pi C library for the MEMS Sensor Board with the 3 Xtrinsic
sensors:

  * High-Precision Pressure Sensor (MPL3115A2)
  * Low-power 3D Magnetometer (MAG3110)
  * 3-Axis, Digital Accelerometer (MMA8491Q)

# Links

  * [Element 14 Community Page for the MEMS Sensor Board](http://www.element14.com/community/community/designcenter/mems-sensor-board)
  * [Git Repo with script and binary-only sensor.so](http://git.oschina.net/embest/rpi_sensor_board.git)

# How to use from C

  1. Run make to build `libmemssensor.a`
  2. Link and use this library

# How to re-build sensor.so for use with Python scripts

  1. Download and extract the [bcm2835 library](http://www.airspayce.com/mikem/bcm2835/).
  2. Copy the bcm2835.c source file into the directory with this library
  3. Run `make sensor.so`.

# Background

This is a reverse engineed binary-compatible version of `sensor.so` originally
found on the Raspbian image for the sensor board.

The download link to the Raspbian Image on element14.com has gone missing, but
the `sensor.so` library can be found on [this
page](http://git.oschina.net/embest/rpi_sensor_board.git).

The sensor.so file is a binary blob, based on the
[bcm2835](http://www.airspayce.com/mikem/bcm2835/), which is GPL licensed. So
the binary blob is in full GPL violation.

I disassembled the `sensor.so` and reimplemented the function in C, with
practially exact result at the assembly level when compiled. I compare the
disassembly output of the `sensor.so` with the output of my compiled C code for
an exact match. I tested using the original Python scripts and everything seems
to be working.

I kept everything minimal
