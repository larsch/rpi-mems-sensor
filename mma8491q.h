struct p { int16_t x, y, z; };
/* mma8491q.c */
int MMA8491Q_Enable(void);
int MMA8491Q_DisEnable(void);
void MMA8491Q_WRITE_REGISTER(void);
void MMA8491Q_READ_REGISTER(void);
int MMA8491Q_BULK_READ(char a, char b, char *c);
int MMA8491Q_Init(void);
int MMA8491_ReadRaw(char *data);
int MMA8491_Read(struct p *xyz);
