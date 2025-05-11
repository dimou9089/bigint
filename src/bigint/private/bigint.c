#include "bigint.h"
#include <string.h>



void mul(uint8_t * const a,uint8_t * const b,uint8_t * const c)
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

void add(uint8_t * const a,uint8_t * const b,uint8_t * const c)
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

void sub(uint8_t * const a,uint8_t * const b,uint8_t * const c)
{
  uint32_t i;
  uint8_t carry;
  carry=0;
  for (i=0;i<BIGINT_SIZE;i++)
  {
    uint16_t sum;
    if (a[i]>=b[i])
    {
      sum=a[i]-(b[i]+carry);
      carry=0;
    }
    else
    {
      sum=a[i]+0x100-(b[i]+carry);
      carry=1;
    }
    c[i]=sum&0xFF;
  }
}

int8_t cmp(const uint8_t * const a, const uint8_t * const b)
{
  uint32_t i;
  for (i=BIGINT_SIZE-1;i>=0;i--)
  {
    if (a[i]>b[i])
    {
      return 1;
    }
    else if (a[i]<b[i])
    {
      return -1;
    }
  }
  return 0;
}
