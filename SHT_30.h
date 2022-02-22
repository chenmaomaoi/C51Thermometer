#ifndef __SHT_30
#define __SHT_30

void SHT_30_Init();
bit SHT_30_DataProcess();

extern unsigned int SHT_30_raw_data[2];
extern float SHT_30_T;
extern float SHT_30_RH;

#endif // !__SHT_30
