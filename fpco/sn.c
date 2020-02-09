//
//  sn.c
//  ProbabilisticOps
//
//  Created by Murilo Coutinho on 17/08/19.
//  Copyright © 2019 Murilo Coutinho. All rights reserved.
//

#include "sn.h"
#include <float.h>
#include "math.h"

int sn_core_initialized = 0;
bn_t zero;
bn_t one;
bn_t fifteen;
sn_t half;
sn_t mhalf;
sn_t snone;
sn_t snminusone;

int sn_core_init()
{
    if(sn_core_initialized==0)
    {
        bn_null(one); bn_new(one); bn_set_dig(one, 1);
        bn_null(zero); bn_new(zero); bn_zero(zero);
        bn_null(fifteen); bn_new(fifteen); bn_set_dig(fifteen, 15);
        
        sn_new(half); bn_zero(half->expoent); half->mantissa = 0.5;
        sn_new(mhalf); bn_zero(mhalf->expoent); mhalf->mantissa = -0.5;
        sn_new(snone); bn_zero(snone->expoent); snone->mantissa = 1;
        sn_new(snminusone); bn_zero(snminusone->expoent); snminusone->mantissa = -1;
        
        sn_core_initialized = 1;
    }
    
    return 0;
}

int sn_core_finalize()
{
    if(sn_core_initialized==1)
    {
        bn_free(one);
        bn_free(zero);
        bn_free(fifteen);
        sn_free(half);
        sn_free(mhalf);
        sn_free(snone);
        sn_free(snminusone);
        
        sn_core_initialized = 0;
    }
    
    return 0;
}

void sn_print(sn_t sn)
{
    printf("Double: %f, Exp: ", sn->mantissa);
    bn_print(sn->expoent);
    printf("\n");
}

void sn_print_array(sn_t *sn, int size)
{
    printf("PD array:");
    for (int i = 0; i<size; i++)
    {
        printf("%.2f,", sn[i]->mantissa);
        bn_print(sn[i]->expoent);
    }
    printf(";\n");
}

void sn_new(sn_t a)
{
    a->mantissa = 0;
    bn_null(a->expoent);
    bn_new(a->expoent);
}

void sn_new_array(sn_t *a, int size)
{
    for(int i=0; i<size; i++)
        sn_new(a[i]);
}

void sn_free(sn_t a)
{
    a->mantissa = 0;
    bn_free(a->expoent);
}

void sn_free_array(sn_t *a, int size)
{
    for(int i=0; i<size; i++)
        sn_free(a[i]);
}

void sn_cpy(sn_t dst, sn_t src)
{
    dst->mantissa = src->mantissa;
    bn_copy(dst->expoent, src->expoent);
}

void sn_cpy_array(sn_t *dst, sn_t *src, int size)
{
    for(int i=0; i<size; i++)
        sn_cpy(dst[i], src[i]);
}

int sn_cmp(sn_t a, sn_t b, double acceptable_error)
{
    double da,db;
    sn_update_range(a);
    sn_update_range(b);
    
    sn_to_double(&da, a);
    sn_to_double(&db, b);
    
    if(fabs(da-db)<=acceptable_error)
        return 0;
    else
    {
        if(a<b)
            return -1;
        else
            return 1;
    }
    
}


int sn_cmp_magnitude(sn_t a, sn_t b, uint64_t acceptable_error)
{
    bn_t acc, diff;
    int r;
    
    bn_null(acc);bn_new(acc);
    bn_null(diff);bn_new(diff);
    
    bn_set_dig(acc, acceptable_error);
    bn_sub(diff, a->expoent, b->expoent);
    diff->sign = BN_POS;
    
    r = bn_cmp(diff, acc);
    if(r!=CMP_GT)
        r = CMP_EQ;
    else
        r = bn_cmp(a->expoent, b->expoent);
    
    bn_free(acc);
    bn_free(diff);
    return r;
}

int sn_cmp_array(sn_t *a, sn_t *b, int size, double acceptable_error)
{
    for(int i=0; i<size; i++)
        if(sn_cmp(a[i], b[i], acceptable_error))
            return 1;
    
    return 0;
}

int sn_cmp_magnitude_array(sn_t *a, sn_t *b, int size, int acceptable_error)
{
    for(int i=0; i<size; i++)
        if(sn_cmp_magnitude(a[i], b[i], acceptable_error))
            return 1;
    
    return 0;
}

void sn_update_range(sn_t sn)
{
    if (sn->mantissa == 0)
    {
        bn_zero(sn->expoent);
        return;
    }
    
    while (fabs(sn->mantissa) <= 0.1)
    {
        sn->mantissa *= 10;
        bn_sub(sn->expoent, sn->expoent, one);
    }
    while (fabs(sn->mantissa)>1)
    {
        sn->mantissa /= 10;
        bn_add(sn->expoent, sn->expoent, one);
    }
    
    if(bn_is_zero(sn->expoent))
        sn->expoent->sign = 0;
}

void sn_rand(sn_t sn, int max_bits)
{
    int sign = rand()%2;
    int sign2 = 2*(rand()%2)-1;
    int bits = rand()%max_bits;
    
    bn_rand(sn->expoent, sign, bits);
    sn->mantissa = sign2 * ((double) (rand()%LIMIT_FOR_DOUBLE_GENERATION))/LIMIT_FOR_DOUBLE_GENERATION;
    
    sn_update_range(sn);
}

void sn_rand_array(sn_t *a, int size, int max_bits)
{
    for(int i=0; i<size; i++)
        sn_rand(a[i], max_bits);
}

int sn_to_double(double *d, sn_t sn)
{
    if(bn_cmp(sn->expoent, fifteen)==CMP_GT)
        return 1;
    
    while (bn_is_zero(sn->expoent) != 1)
    {
        if (bn_sign(sn->expoent) == BN_POS)
        {
            sn->mantissa *= 10;
            bn_sub(sn->expoent, sn->expoent, one);
        }
        else
        {
            sn->mantissa /= 10;
            bn_add(sn->expoent, sn->expoent, one);
        }
        
        if(sn->mantissa == 0)
        {
            *d = 0;
            return 1;
        }
    }
    *d = sn->mantissa;
    
    return 0;
}

void sn_to_double_array(double *d, sn_t *sn, int size)
{
    for (int i = 0; i<size; i++)
        sn_to_double(&d[i], sn[i]);
}

void double_to_sn(sn_t sn, double d)
{
    sn->mantissa = d;
    bn_zero(sn->expoent);
    
    sn_update_range(sn);
}

void double_to_sn_array(sn_t *sn, double *d, int size)
{
    for (int i = 0; i<size; i++)
        double_to_sn(sn[i], d[i]);
}

void sn_mul(sn_t c, sn_t a, sn_t b)
{
    c->mantissa = a->mantissa * b->mantissa;
    bn_add(c->expoent, a->expoent, b->expoent);
    
    sn_update_range(c);
}

void sn_add(sn_t c, sn_t a, sn_t b)
{
    sn_st **max, **min;
    sn_t aux;
    
    if(a->mantissa == 0)
    {
        sn_cpy(c, b);
        return;
    }
    
    if(b->mantissa == 0)
    {
        sn_cpy(c, a);
        return;
    }
    
    if (bn_cmp(a->expoent, b->expoent)==CMP_GT)
    {
        max = &a;
        min = &b;
    }
    else
    {
        max = &b;
        min = &a;
    }
    
    sn_new(aux);
    bn_sub(aux->expoent, (*max)->expoent, (*min)->expoent);
    if (bn_cmp(aux->expoent, fifteen)!= CMP_GT)
    {
        sn_cpy(aux, (*min));
        
        while (bn_cmp((*max)->expoent, aux->expoent)==CMP_GT)
        {
            aux->mantissa *= 0.1;
            bn_add(aux->expoent,aux->expoent,one);
        }
        
        aux->mantissa += (*max)->mantissa;
        sn_cpy(c, aux);
    }
    else
    {
        sn_cpy(c, (*max));
    }
    
    sn_free(aux);
}

void sn_abs(sn_t c, sn_t a)
{
    sn_cpy(c, a);
    c->mantissa = fabs(c->mantissa);
}

void sn_abs_array(sn_t *c, sn_t *a, int size)
{
    for(int i=0; i<size; i++)
        sn_abs(c[i],a[i]);
}
