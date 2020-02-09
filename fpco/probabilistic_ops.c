#include "probabilistic_ops.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sn.h"

void bias_rand(sn_t bias, int max_bits)
{
    sn_rand(bias, max_bits);
    if(bn_is_zero(bias->expoent))
        bias->expoent->sign = 0;
    else
        bias->expoent->sign = 1;
}

void bias_rand_max(sn_t bias)
{
    bn_zero(bias->expoent);
    bias->mantissa = ((double)(rand()%2))*2 - 1;
}

void bias_rand_array(sn_t *bias, int size, int max_bits)
{
    for(int i=0; i<size; i++)
        bias_rand(bias[i], max_bits);
}

void bias_rand_max_array(sn_t *bias, int size)
{
    for(int i=0; i<size; i++)
        bias_rand_max(bias[i]);
}

void bias_correct_boundaries(sn_t sn)
{
    sn_update_range(sn);
    if (bn_sign(sn->expoent)==BN_POS)
    {
        if(!bn_is_zero(sn->expoent))
        {
            bn_zero(sn->expoent);
            if (sn->mantissa>0)
                sn->mantissa = 1;
            else
                sn->mantissa = -1;
        }
    }
}

void bias_max(sn_t max, sn_t x1, sn_t x2)
{
    int cmp;
	sn_update_range(x1);
	sn_update_range(x2);

	if (x1->mantissa == 0)
    {
        sn_cpy(max, x2);
        return;
    }
	if (x2->mantissa == 0)
    {
        sn_cpy(max, x1);
        return;
    }

    cmp = bn_cmp(x1->expoent, x2->expoent);
	if (cmp == CMP_LT)
        sn_cpy(max, x2);
    else if (cmp == CMP_GT)
        sn_cpy(max, x1);
	else
	{
		if (fabs(x1->mantissa) < fabs(x2->mantissa))
            sn_cpy(max, x2);
		else
            sn_cpy(max, x1);
	}
}

void prob_to_bias(sn_t bias, double prob)
{
    bn_zero(bias->expoent);
    bias->mantissa = 2 * prob - 1;
    
    sn_update_range(bias);
}

void prob_to_bias_array(sn_t *bias, double *prob, int size)
{
    for (int i = 0; i<size; i++)
        prob_to_bias(bias[i], prob[i]);
}

void bias_to_prob(double *prob, sn_t bias)
{
    sn_to_double(prob, bias);
    *prob = (1 + *prob) / 2;
}

void bias_to_prob_array(double *prob, sn_t *bias, int size)
{
    for (int i = 0; i<size; i++)
        bias_to_prob(&(prob[i]), bias[i]);
}

void prob_mult_through_bias(sn_t c, sn_t a, sn_t b)
{
    sn_t aux;
    
    sn_new(aux);
    
    sn_mul(aux, a, b);
    sn_add(aux, aux, a);
    sn_add(aux, aux, b);
    sn_mul(aux, aux, half);
    sn_add(aux, aux, mhalf);
    
    sn_cpy(c, aux);
    bias_correct_boundaries(c);
    
    sn_free(aux);
}


void prob_sum_through_bias(sn_t c, sn_t a, sn_t b)
{
    sn_add(c, a, b);
    sn_add(c, c, snone);
    bias_correct_boundaries(c);
}


void prob_complement_through_bias(sn_t c, sn_t a)
{
    sn_cpy(c, a);
    c->mantissa = -c->mantissa;
}

void u8_to_bias_array(sn_t *v, uint8_t x)
{
    for (int i = 0; i<8; i++)
    {
        if((x >> i) & 0x01)
            sn_cpy(v[i], snone);
        else
            sn_cpy(v[i], snminusone);
    }
}

void u16_to_bias_array(sn_t *v, uint16_t x)
{
    for (int i = 0; i<16; i++)
    {
        if((x >> i) & 0x01)
            sn_cpy(v[i], snone);
        else
            sn_cpy(v[i], snminusone);
    }
}

void u32_to_bias_array(sn_t *v, uint32_t x)
{
    for (int i = 0; i<32; i++)
    {
        if((x >> i) & 0x01)
            sn_cpy(v[i], snone);
        else
            sn_cpy(v[i], snminusone);
    }
}

void u64_to_bias_array(sn_t *v, uint64_t x)
{
    for (int i = 0; i<64; i++)
    {
        if((x >> i) & 0x01)
            sn_cpy(v[i], snone);
        else
            sn_cpy(v[i], snminusone);
    }
}

void bias_array_to_u8(uint8_t *x, sn_t *v)
{
    uint8_t um = 1;
    
    *x = 0;
    for (int i = 0; i<8; i++)
    {
        if (v[i]->mantissa > 0)
            *x |= um << i;
    }
}


void bias_array_to_u16(uint16_t *x, sn_t *v)
{
    uint16_t um = 1;
    
    *x = 0;
    for (int i = 0; i<16; i++)
    {
        if (v[i]->mantissa > 0)
            *x |= um << i;
    }
}


void bias_array_to_u32(uint32_t *x, sn_t *v)
{
    uint32_t um = 1;
    
    *x = 0;
    for (int i = 0; i<32; i++)
    {
        if (v[i]->mantissa > 0)
            *x |= um << i;
    }
}


void bias_array_to_u64(uint64_t *x, sn_t *v)
{
    uint64_t um = 1;
    
    *x = 0;
    for (int i = 0; i<64; i++)
    {
        if (v[i]->mantissa > 0)
            *x |= um << i;
    }
}
