#include "rc.h"


rc_crl_t RC_Ctl;


void rc_abs(int16_t *res)
{
    if (*res < 10 && *res > -10)
    {
        *res = 0;
    }
}

void RemoteDataProcess(uint8_t *pData)
{
 if(pData == NULL)
 {
 return;
 }
 
 RC_Ctl.rc.ch0 = (((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF)-1024; 
 RC_Ctl.rc.ch1 = ((((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF)-1024;
 RC_Ctl.rc.ch2 = ((((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) | ((int16_t)pData[4] << 10)) & 0x07FF)-1024;
 RC_Ctl.rc.ch3 = ((((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF)-1024;

 RC_Ctl.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
 RC_Ctl.rc.s2 = ((pData[5] >> 4) & 0x0003);
 
 RC_Ctl.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
 RC_Ctl.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
 RC_Ctl.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8); 
 RC_Ctl.mouse.press_l = pData[12];
 RC_Ctl.mouse.press_r = pData[13];
 
 RC_Ctl.key.key_code = (((int16_t)pData[14])| ((int16_t)pData[15] << 8));
 
 rc_abs(&RC_Ctl.rc.ch0);
 rc_abs(&RC_Ctl.rc.ch1);
 rc_abs(&RC_Ctl.rc.ch2);
 rc_abs(&RC_Ctl.rc.ch3);

}





