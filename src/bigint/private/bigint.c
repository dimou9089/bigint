#include <string.h>

#include "bigint.h"
#include "bigint_private.h"


void mod(uint8_t * const a,uint8_t * const b,uint8_t * const c)
{
  uint32_t size,i;
  memcpy(c,a,sizeof(uint8_t)*BIGINT_SIZE);
  size=bigint_size(b);
  for (i=0;i<BIGINT_SIZE-size;i++)
  {
    while (cmp_inplace(c,b,BIGINT_SIZE-size-i)>=0)
    {
      sub_inplace(c,b,BIGINT_SIZE-size-i);
    }
  }
}

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
  int32_t i;
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

void sub_inplace(uint8_t * const a,uint8_t * const b,const uint32_t shift)
{
  uint32_t i;
  uint8_t carry;
  carry=0;
  for (i=0;i<BIGINT_SIZE-shift;i++)
  {
    uint16_t sum;
    if (a[i+shift]>=b[i])
    {
      sum=a[i+shift]-(b[i]+carry);
      carry=0;
    }
    else
    {
      sum=a[i+shift]+0x100-(b[i]+carry);
      carry=1;
    }
    a[i+shift]=sum&0xFF;
  }
}

int8_t cmp_inplace(const uint8_t * const a, const uint8_t * const b, const uint32_t shift)
{
  int32_t i;
  for (i=BIGINT_SIZE-1-shift;i>=0;i--)
  {
    if (a[i+shift]>b[i])
    {
      return 1;
    }
    else if (a[i+shift]<b[i])
    {
      return -1;
    }
  }
  return 0;
}

uint32_t bigint_size(const uint8_t * const bigint)
{
  uint32_t i;
  i=0;
  while (i<BIGINT_SIZE && 0!=bigint[i])
  {
    i++;
  }
  return i;
}
