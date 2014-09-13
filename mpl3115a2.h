/* mpl3115a2.c */
void MPL3115A2_WRITE_REGISTER(uint8_t reg, uint8_t value);
uint8_t MPL3115A2_READ_REGISTER(uint8_t reg);
void MPL3115A2_Active(void);
void MPL3115A2_Standby(void);
void MPL3115A2_Init_Alt(void);
int MPL3115A2_Read_Alt(void);
void MPL3115A2_Init_Bar(void);
int MPL3115A2_Read_Temp(void);
