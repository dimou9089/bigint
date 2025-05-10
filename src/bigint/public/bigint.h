#ifndef OPERATION_H
#define OPERATION_H
#include <stdint.h>

#define BIGINT_SIZE 512/8


void mul(uint8_t * a,uint8_t * b,uint8_t * c);
void add(uint8_t * a,uint8_t * b,uint8_t * c);
#endif
