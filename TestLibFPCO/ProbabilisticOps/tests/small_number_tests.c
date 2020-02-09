//
//  small_number_tests.c
//  ProbabilisticOps


#include "small_number_tests.h"
#include "fpco.h"
#include <math.h>
#include "test_configuration.h"

void test_init_and_print_precise_double(int n)
{
    INIT_TEST(__func__)
    sn_t a;
    sn_new(a);
    for(int i=0; i<n; i++)
    {
        sn_rand(a, 32);
        sn_print(a);
    }
    sn_free(a);
    END_TEST(0, __func__)
}


void test_init_and_print_precise_double_array(int n)
{
    INIT_TEST(__func__)
    sn_t a[8];
    sn_new_array(a, 8);
    
    for(int i=0; i<n; i++)
    {
        sn_rand_array(a, 8, 32);
        sn_print_array(a, 8);
    }
    
    sn_free_array(a, 8);
    END_TEST(0, __func__)
}


int test_sn_update_range(int n)
{
    INIT_TEST(__func__)
    int fac, sign, rv = 0;
    sn_t a,a_copy;
    bn_t bn_fac;
    sn_new(a); sn_new(a_copy);
    bn_null(bn_fac); bn_new(bn_fac);
   
    for(int i=0; i<n; i++)
    {
        sn_rand(a,32);
        sn_cpy(a_copy, a);
        fac = rand()%5;
        sign = rand()%2;
        bn_set_dig(bn_fac, fac);
        
        if(fac)
        {
            a->mantissa *= pow(10,fac);
            bn_sub(a->expoent, a->expoent, bn_fac);
        }
        else
        {
            a->mantissa /= pow(10,fac);
            bn_add(a->expoent, a->expoent, bn_fac);
        }
        
        sn_update_range(a);
        if(sn_cmp(a, a_copy, 0.0000001))
        {
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(a); sn_free(a); bn_free(bn_fac);
    END_TEST(rv, __func__)
    return rv;
}

int test_double_to_sn_conversions(int n)
{
    int rv = 0;
    double d;
    sn_t sn, sn_old;
    
    INIT_TEST(__func__)
    sn_new(sn); sn_new(sn_old);
    
    for(int i =0; i<n; i++)
    {
        d=0;
        sn->mantissa=0; sn_old->mantissa = 0;
        
        sn_rand(sn, 5); sn_cpy(sn_old, sn);
        if(sn_to_double(&d, sn))
            continue;
        
        sn->mantissa = 0;
        bn_zero(sn->expoent);
        
        double_to_sn(sn, d);
        
        if(sn_cmp(sn, sn_old, 0.001))
        {
            rv = 1;
            goto _err;
        }
    }
_err:
    sn_free(sn); sn_free(sn_old);
    END_TEST(rv , __func__)
    return rv;
}



int test_sn_mul(int n)
{
    int rv = 0;
    double a,b,c;
    sn_t x,y,z;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);sn_new(z);
    
    for(int i=0; i<n; i++)
    {
        sn_rand(x, 4);
        sn_rand(y, 4);
        
        sn_to_double(&a, x);
        sn_to_double(&b, y);
        
        sn_mul(z, x, y);
        
        sn_to_double(&c, z);
        
        
        if(fabs(a*b - c)>ACCEPTABLE_ERROR)
        {
            sn_print(x);
            sn_print(y);
            sn_print(z);
            printf("%f\n%f\n",a,b);
            printf("a*b = %f, c = %f",a*b,c);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);sn_free(z);
    END_TEST(rv, __func__)
    return rv;
}


int test_sn_add(int n)
{
    int rv = 0;
    double a,b,c;
    sn_t x,y,z;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);sn_new(z);
    
    for(int i=0; i<n; i++)
    {
        sn_rand(x, 4);
        sn_rand(y, 4);
        
        sn_to_double(&a, x);
        sn_to_double(&b, y);
        
        sn_add(z, x, y);
        
        sn_to_double(&c, z);
        
        //sn_print(x);
        //sn_print(y);
        //sn_print(z);
        //printf("%f\n%f\n",a,b);
        //printf("a*b = %f, c = %f",a*b,c);
        
        if(fabs(a+b - c)>ACCEPTABLE_ERROR)
        {
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);sn_free(z);
    END_TEST(rv, __func__)
    return rv;
}


