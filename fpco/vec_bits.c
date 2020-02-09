#include "vec_bits.h"
#include <stdint.h>

void print_vec(double *vec, int len)
{
	for (int i = 0; i<len; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("%f ", vec[i]);
	}
}

void u8_to_vec(uint8_t c, double *vec)
{
	for (int i = 0; i<8; i++)
		vec[i] = (double)((c >> i) & 0x01);
}

uint8_t vec_to_u8(double *vec)
{
	uint8_t c = 0, um = 0x01;

	for (int i = 0; i<8; i++)
	{
		if (vec[i]>0.5)
			c |= um << i;
	}

	return c;
}

void u32_to_vec(uint32_t c, double *vec)
{
	for (int i = 0; i<32; i++)
		vec[i] = (double)((c >> i) & 0x01);
}

uint32_t vec_to_u32(double *vec)
{
	uint32_t c = 0, um = 0x01;

	for (int i = 0; i<32; i++)
	{
		if (vec[i]>0.5)
			c |= um << i;
	}

	return c;
}
