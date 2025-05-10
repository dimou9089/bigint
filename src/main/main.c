#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"

int main(){
  uint8_t bigintA[BIGINT_SIZE];
  uint8_t bigintB[BIGINT_SIZE];
  memset(bigintA,0,sizeof(uint8_t)*BIGINT_SIZE);
  memset(bigintB,0,sizeof(uint8_t)*BIGINT_SIZE);
  return 0;
}
