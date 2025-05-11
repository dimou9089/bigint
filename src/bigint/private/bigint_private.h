#ifndef BIGINT_PRIVATE_H
#define BIGINT_PRIVATE_H
#include "bigint.h"

void sub_inplace(uint8_t * const a,uint8_t * const b,const uint32_t shift);
uint32_t bigint_size(const uint8_t * const bigint);
int8_t cmp_inplace(const uint8_t * const a, const uint8_t * const b, const uint32_t shift);
#endif
