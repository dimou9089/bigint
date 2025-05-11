#ifndef BIGINT_H
#define BIGINT_H
#include <stdint.h>

#define BIGINT_SIZE 512/8


void mod(uint8_t * const a,uint8_t * const b,uint8_t * const c);
int8_t cmp(const uint8_t * const a, const uint8_t * const b);
void sub(uint8_t * const a,uint8_t * const b,uint8_t * const c);
void mul(uint8_t * const a,uint8_t * const b,uint8_t * const c);
void add(uint8_t * const a,uint8_t * const b,uint8_t * const c);
#endif
