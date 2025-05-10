#include "bigint.h"
#include <string.h>



void mul(uint8_t * a,uint8_t * b,uint8_t * c)
{
  uint32_t i,j;
  uint8_t carry;
  carry=0;
  for (i=0;i<BIGINT_SIZE;i++)
  {
    uint8_t tmp[BIGINT_SIZE];
    memset(tmp,0,i);
    for (j=0;j<BIGINT_SIZE-i;j++)
    {
      uint16_t prod;
      prod=a[j]*b[i]+carry;
      tmp[j+i]=prod&0xFF;
      carry=(prod>>8)&0xFF;
    }
    add(c,tmp,c);
  }
}

void add(uint8_t * a,uint8_t * b,uint8_t * c)
{
  uint32_t i;
  uint8_t carry;
  carry=0;
  for (i=0;i<BIGINT_SIZE;i++)
  {
    uint16_t sum;
    sum=a[i]+b[i]+carry;
    c[i]=sum&0xFF;
    carry=(sum>>8)&0xFF;
  }
}
