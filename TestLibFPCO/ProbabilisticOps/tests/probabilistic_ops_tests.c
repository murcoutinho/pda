//
//  probabilistic_ops_tests.c
//  ProbabilisticOps

#include "probabilistic_ops_tests.h"
#include "fpco.h"
#include "test_configuration.h"

int test_bias_max(int n)
{
    int rv = 0;
    double a,b,c,d;
    sn_t x,y,z;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);sn_new(z);
    
    //test with zero
    bias_rand(x, 4);
    bias_rand(y, 4);
    x->mantissa = 0;
    bias_max(z, x, y);
    if(sn_cmp(z, y, 0) != 0)
    {
        rv = 1;
        goto _err;
    }
    
    bias_rand(x, 4);
    bias_rand(y, 4);
    y->mantissa = 0;
    bias_max(z, x, y);
    if(sn_cmp(z, x, 0) != 0)
    {
        rv = 1;
        goto _err;
    }
    
    for(int i=0; i<n; i++)
    {
        bias_rand(x, 4);
        bias_rand(y, 4);
        
        sn_to_double(&a, x);
        sn_to_double(&b, y);
        
        bias_max(z, x, y);
        
        sn_to_double(&c, z);
        
        d = fmax(fabs(a), fabs(b));
        
        if(fabs(fabs(d) - fabs(c))>ACCEPTABLE_ERROR)
        {
            sn_print(x);
            sn_print(y);
            sn_print(z);
            printf("%f\n%f\n%f\n%f\n",a,b,c,d);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);sn_free(z);
    END_TEST(rv, __func__)
    return rv;
}



int test_prob_to_bias(int n)
{
    int rv = 0;
    double a;
    sn_t x,y;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);
    
    for(int i=0; i<n; i++)
    {
        bias_rand(x, 4);
        bias_to_prob(&a, x);
        prob_to_bias(y, a);
        if(sn_cmp(x, y, ACCEPTABLE_ERROR)!=0)
        {
            sn_print(x);
            sn_print(y);
            printf("%f\n",a);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);
    END_TEST(rv, __func__)
    return rv;
}



int test_prob_mult_through_bias(int n)
{
    int rv = 0;
    double a,b,c,d;
    sn_t x,y,z;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);sn_new(z);
    
    for(int i=0; i<n; i++)
    {
        bias_rand(x, 4);
        bias_rand(y, 4);
 
        bias_to_prob(&a, x);
        bias_to_prob(&b, y);
        
        sn_update_range(x);
        sn_update_range(y);
        
        prob_mult_through_bias(z, x, y);
        
        bias_to_prob(&c, z);
        
        d = a*b;
        
        if(fabs(d - c)>ACCEPTABLE_ERROR)
        {
            sn_print(x);
            sn_print(y);
            sn_print(z);
            printf("it:%d ;\n%f\n%f\n%f\n%f\n",i,a,b,c,d);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);sn_free(z);
    END_TEST(rv, __func__)
    return rv;
}

int test_prob_sum_through_bias(int n)
{
    int rv = 0;
    double a,b,c,d;
    sn_t x,y,z;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);sn_new(z);
    
    for(int i=0; i<n; i++)
    {
        bias_rand(x, 4);
        bias_rand(y, 4);
        
        bias_to_prob(&a, x);
        bias_to_prob(&b, y);
        
        sn_update_range(x);
        sn_update_range(y);
        
        prob_sum_through_bias(z, x, y);
        
        bias_to_prob(&c, z);
        
        d = a+b;
        if(d>1)
            d = 1;
        if(d< -1)
            d = -1;
        
        if(fabs(d - c)>ACCEPTABLE_ERROR)
        {
            sn_print(x);
            sn_print(y);
            sn_print(z);
            printf("it:%d ;\n%f\n%f\n%f\n%f\n",i,a,b,c,d);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);sn_free(z);
    END_TEST(rv, __func__)
    return rv;
}


int test_prob_complement_through_bias(int n)
{
    int rv = 0;
    double a,b,c;
    sn_t x,y;
    
    INIT_TEST(__func__)
    sn_new(x);sn_new(y);
    
    for(int i=0; i<n; i++)
    {
        bias_rand(x, 4);
        bias_to_prob(&a, x);
        sn_update_range(x);
        
        prob_complement_through_bias(y, x);
        
        bias_to_prob(&b, y);
        
        c = 1-a;
        
        if(fabs(c - b)>ACCEPTABLE_ERROR)
        {
            sn_print(x);
            sn_print(y);
            printf("it:%d ;\n%f\n%f\n%f\n",i,a,b,c);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free(x);sn_free(y);
    END_TEST(rv, __func__)
    return rv;
}
