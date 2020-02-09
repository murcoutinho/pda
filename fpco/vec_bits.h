#ifndef vec_bits_h
#define vec_bits_h

#include <stdio.h>
#include <stdint.h>

void print_vec(double *vec, int len);
void u8_to_vec(uint8_t c, double *vec);
uint8_t vec_to_u8(double *vec);
void u32_to_vec(uint32_t c, double *vec);
uint32_t vec_to_u32(double *vec);

#endif /* vec_bits_h */

