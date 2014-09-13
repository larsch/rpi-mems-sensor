/* mag3110.c */
int MAG3110_WRITE_REGISTER(char reg, char val);
char MAG3110_READ_REGISTER(char reg);
int MAG3110_BULK_READ(char reg, char count, char *data);
int MAG3110_Init(void);
char MAG3110_ReadRawData(char *data);
int MAG3110_ReadAsInt(void);
int16_t MAG3110_ReadRawData_x(void);
int16_t MAG3110_ReadRawData_y(void);
int16_t MAG3110_ReadRawData_z(void);
