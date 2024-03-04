#ifndef _RC_H
#define _RC_H

																
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "uartidle.h"

/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_W               RC_Ctl.key.bit.W		
#define KEY_S               RC_Ctl.key.bit.S		
#define KEY_A               RC_Ctl.key.bit.A		
#define KEY_D               RC_Ctl.key.bit.D	
#define KEY_SHIFT           RC_Ctl.key.bit.SHIFT	
#define KEY_CTRL            RC_Ctl.key.bit.CTRL		
#define KEY_Q               RC_Ctl.key.bit.Q		
#define KEY_E               RC_Ctl.key.bit.E		
#define KEY_R               RC_Ctl.key.bit.R		
#define KEY_F               RC_Ctl.key.bit.F		
#define KEY_G               RC_Ctl.key.bit.G		
#define KEY_Z               RC_Ctl.key.bit.Z		
#define KEY_X               RC_Ctl.key.bit.X		
#define KEY_C               RC_Ctl.key.bit.C		
#define KEY_V               RC_Ctl.key.bit.V		
#define KEY_B               RC_Ctl.key.bit.B	



void RemoteDataProcess(uint8_t *pData);

typedef struct
{
		struct
	 {
		 int16_t x;
		 int16_t y;
		 int16_t z;
		 int16_t x_filter;
		 int16_t y_filter;
		 uint8_t press_l;
		 uint8_t press_r;
	 }mouse;
	  struct
   {
		 int16_t ch0;
		 int16_t ch1;
		 int16_t ch2;
		 int16_t ch3;
		 int16_t ch4;
		 int8_t s1;
		 int8_t s2;
   }rc;
		union
	{
    uint16_t key_code;
    struct
    {
      uint16_t W : 1;
      uint16_t S : 1;
      uint16_t A : 1;
      uint16_t D : 1;
      uint16_t SHIFT : 1;
      uint16_t CTRL : 1;
      uint16_t Q : 1;
      uint16_t E : 1;
      uint16_t R : 1;
      uint16_t F : 1;
      uint16_t G : 1;
      uint16_t Z : 1;
      uint16_t X : 1;
      uint16_t C : 1;
      uint16_t V : 1;
      uint16_t B : 1;
    } bit;
  }key;
	struct
	{
	 uint8_t w;
	 uint8_t s;
	 uint8_t a;
	 uint8_t d;
	 uint8_t z;
	 uint8_t b;
	 uint8_t e;
	 uint8_t v;
	 uint8_t c;
	}last;
}rc_crl_t;

 

#endif //_BSP_RC_1_H

