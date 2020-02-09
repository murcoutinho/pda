//
//  fpco.c (Fundamental Probabilistic Cryptographic Operations)
//
//  Created by Murilo Coutinho on 22/08/19.
//  Copyright © 2019 Murilo Coutinho. All rights reserved.
//

#include "fpco.h"
#include "sn.h"
#include "probabilistic_ops.h"

int fpco_core_initialized = 0;
int global_max_size_of_bias_arrays = 0;
sn_t *aux = NULL;

int fpco_core_init(int max_size_of_bias_arrays)
{
    int rv = 0;
    
    if(fpco_core_initialized == 0)
    {
        rv = sn_core_init();
        if(rv)
            return rv;
        
        global_max_size_of_bias_arrays = max_size_of_bias_arrays;
        aux = (sn_t *) malloc(sizeof(sn_t)*global_max_size_of_bias_arrays);
        if(aux == NULL)
        {
            sn_core_finalize();
            return 1;
        }
        
        for(int i=0; i<global_max_size_of_bias_arrays; i++)
            sn_new(aux[i]);
        
        fpco_core_initialized = 1;
    }
    
    return 0;
}


int fpco_core_finalize(void)
{
    if(fpco_core_initialized == 1)
    {
        for(int i=0; i<global_max_size_of_bias_arrays; i++)
            sn_free(aux[i]);
        
        free(aux);
        aux = NULL;
        
        sn_core_finalize();
        
        global_max_size_of_bias_arrays = 0;
        fpco_core_initialized = 0;
    }
    
    return 0;
}

int fpco_rot_right(sn_t *out, sn_t *in, int shift, int size)
{
    if(size>global_max_size_of_bias_arrays)
        return 1;
    
    sn_cpy_array(aux, in, size);
    for (int i = 0; i<size; i++)
        sn_cpy(out[i], aux[(i + shift) % size]);
    
    return 0;
}


int fpco_rot_left(sn_t *out, sn_t *in, int shift, int size)
{
    if(size>global_max_size_of_bias_arrays)
        return 1;
    
    sn_cpy_array(aux, in, size);
    for (int i = 0; i<size; i++)
        sn_cpy(out[i], aux[(size + i - shift) % size]);
    
    return 0;
}

int fpco_permutation(sn_t *out, sn_t *in,  int *permutation, int size)
{
    if(size>global_max_size_of_bias_arrays)
        return 1;
    
    sn_cpy_array(aux, in, size);
    
    for (int i = 0; i < size; i++)
        sn_cpy(out[i], aux[permutation[i]]);
    
    return 0;
}


int fpco_shift_left(sn_t *out, sn_t *in, int shift, int size)
{
    if(fpco_rot_left(out, in, shift, size))
        return 1;
    
    for (int i = 0; i<shift; i++)
        sn_cpy(out[i], snminusone);
    
    return 0;
}


int fpco_shift_right(sn_t *out, sn_t *in, int shift, int size)
{
    if(fpco_rot_right(out, in, shift, size))
        return 1;
    
    for (int i = size - 1; i >= (size - shift); i--)
        sn_cpy(out[i], snminusone);
    
    return 0;
}

int fpco_xor(sn_t *c, sn_t *a, sn_t *b, int size)
{
    if(global_max_size_of_bias_arrays<2)
        return -1;
    for (int i = 0; i<size; i++)
    {
        //-------------------------------------------------------------
        /*
         this code is to prevent errors when bias are equal to 1 or -1.
         */
        sn_abs(aux[0], a[i]);
        sn_abs(aux[1], b[i]);
        if( (sn_cmp(aux[0], snone, 0)==0) && (sn_cmp(aux[1], snone, 0)==0) )
        {
            if(a[i]->mantissa * b[i]->mantissa < 0)
                sn_cpy(c[i], snminusone);
            else
                sn_cpy(c[i], snone);
        }
        else
            sn_mul(c[i], a[i], b[i]);
        //-------------------------------------------------------------
        prob_complement_through_bias(c[i], c[i]);
        bias_correct_boundaries(c[i]);
    }
    
    return 0;
}


int fpco_and(sn_t *c, sn_t *a, sn_t *b, int size)
{
    if(global_max_size_of_bias_arrays<2)
        return -1;
    for (int i = 0; i<size; i++)
    {
        /*
         this code is to prevent errors when bias are equal to 1 or -1.
         */
        sn_abs(aux[0], a[i]);
        sn_abs(aux[1], b[i]);
        if( (sn_cmp(aux[0], snone, 0)==0) && (sn_cmp(aux[1], snone, 0)==0) )
        {
            if(a[i]->mantissa + b[i]->mantissa != 2)
                sn_cpy(c[i], snminusone);
            else
                sn_cpy(c[i], snone);
        }
        else
            prob_mult_through_bias(c[i], a[i], b[i]);
    }
    
    
    return 0;
}


int fpco_or(sn_t *c, sn_t *a, sn_t *b, int size)
{
    if(size>global_max_size_of_bias_arrays)
        return 1;
    
    for (int i = 0; i<size; i++)
    {
        /*
      this code is to prevent errors when bias are equal to 1 or -1.
      */
        sn_abs(aux[0], a[i]);
        sn_abs(aux[1], b[i]);
        if( (sn_cmp(aux[0], snone, 0)==0) && (sn_cmp(aux[1], snone, 0)==0) )
        {
            if(a[i]->mantissa + b[i]->mantissa == -2)
                sn_cpy(c[i], snminusone);
            else
                sn_cpy(c[i], snone);
        }
        else
        {
            prob_complement_through_bias(aux[i], a[i]);
            prob_complement_through_bias(c[i], b[i]);
            prob_mult_through_bias(c[i], c[i], aux[i]);
            prob_complement_through_bias(c[i], c[i]);
        }
    }
    
    return 0;
}

int fpco_not(sn_t *out, sn_t *in, int size)
{
    for (int i = 0; i<size; i++)
        prob_complement_through_bias(out[i], in[i]);
    
    return 0;
}

/*
 If we add a+b when a is much bigger than b, sn_add will return a because a lack of precision. In fpco_add this problem can lead to the creation of 0 biases (which is something we dont want because everything will become zero). The solution is to add the bigger number first, then if their sum is zero, it will not affect the sum of the rest. This function sort_for_secure_sum, is used to force the sum to occur in the intended order.
 */
void sort_for_secure_sum()
{
    int count = -1;
    
    while(count!=0)
    {
        count = 0;
        for(int i=2;i<4;i++)
        {
            if(bn_cmp(aux[i]->expoent, aux[i+1]->expoent)==CMP_LT)
            {
                count++;
                sn_cpy(aux[6], aux[i]);
                sn_cpy(aux[i], aux[i+1]);
                sn_cpy(aux[i+1], aux[6]);
            }
        }
    }
}

int fpco_add(sn_t *c, sn_t *a, sn_t *b, int size)
{
    
    if(size>global_max_size_of_bias_arrays)
        return 1;
    if(global_max_size_of_bias_arrays<7)
        return -1;
    
    //aux[0] - used for the carry bit
    //aux[1] - retains the resulting bit
    //aux[2] - used for intermediary values
    sn_cpy(aux[0], snminusone);
    
    for (int i = 0; i<size; i++)
    {
        sn_mul(aux[1], a[i], b[i]);
        sn_mul(aux[1], aux[1], aux[0]);
    
        prob_complement_through_bias(aux[5], aux[1]);
        sn_cpy(aux[4], aux[0]);
        sn_cpy(aux[3], a[i]);
        sn_cpy(aux[2], b[i]);
        sort_for_secure_sum();
        
        sn_add(aux[2], aux[2], aux[3]);
        sn_add(aux[2], aux[2], aux[4]);
        sn_add(aux[2], aux[2], aux[5]);
        
        sn_mul(aux[2], aux[2], half);
        
        bias_correct_boundaries(aux[2]);
        bias_correct_boundaries(aux[1]);
        
        sn_cpy(c[i], aux[1]); //to allow c as the same pointer of a or b
        sn_cpy(aux[0], aux[2]);
    }
    return 0;
}


int fpco_sub(sn_t *c, sn_t *a, sn_t *b, int size)
{
    if(size>global_max_size_of_bias_arrays)
        return 1;
    if(global_max_size_of_bias_arrays<3)
        return -1;
    
    //aux[0] - used for the carry bit
    //aux[1] - retains the resulting bit
    //aux[2] - used for intermediary values
    sn_cpy(aux[0], snminusone);
    
    for (int i = 0; i<size; i++)
    {
        sn_mul(aux[1], a[i], b[i]);
        sn_mul(aux[1], aux[1], aux[0]);
        
        sn_add(aux[2], aux[1], aux[0]);
        prob_complement_through_bias(aux[0], a[i]);
        sn_add(aux[2], aux[2], aux[0]);
        sn_add(aux[2], aux[2], b[i]);
        
        sn_mul(aux[2], aux[2], half);
        
        bias_correct_boundaries(aux[2]);
        bias_correct_boundaries(aux[1]);
        
        sn_cpy(c[i], aux[1]); //to allow c as the same pointer of a or b
        sn_cpy(aux[0], aux[2]);
    }
    return 0;
}

