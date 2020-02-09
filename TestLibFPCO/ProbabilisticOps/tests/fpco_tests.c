//
//  fpco_tests.c
//  ProbabilisticOps

#include "fpco_tests.h"
#include "probabilistic_ops_tests.h"
#include "test_configuration.h"
#include "fpco.h"

int test_rotation(int n)
{
    int rv = 0;
    int t, shift;
    sn_t x[SIZE_OF_TEST_ARRAY], y[SIZE_OF_TEST_ARRAY];
    
    INIT_TEST(__func__)
    
    sn_new_array(x, SIZE_OF_TEST_ARRAY);
    sn_new_array(y, SIZE_OF_TEST_ARRAY);
    
    for(int i=0; i<n; i++)
    {
        
        bias_rand_array(x, SIZE_OF_TEST_ARRAY, 8);
        sn_cpy_array(y, x, SIZE_OF_TEST_ARRAY);
        t = rand()%4;
        shift = rand()%SIZE_OF_TEST_ARRAY;
        
        switch (t) {
            case 0:
                fpco_rot_right(x, x, shift, SIZE_OF_TEST_ARRAY);
                fpco_rot_left(x, x, shift, SIZE_OF_TEST_ARRAY);
                break;
            case 1:
                fpco_rot_left(x, x, shift, SIZE_OF_TEST_ARRAY);
                fpco_rot_right(x, x, shift, SIZE_OF_TEST_ARRAY);
                break;
            case 2:
                fpco_rot_right(x, x, shift, SIZE_OF_TEST_ARRAY);
                fpco_rot_right(x, x, SIZE_OF_TEST_ARRAY - shift, SIZE_OF_TEST_ARRAY);
                break;
            default:
                fpco_rot_left(x, x, shift, SIZE_OF_TEST_ARRAY);
                fpco_rot_left(x, x, SIZE_OF_TEST_ARRAY - shift, SIZE_OF_TEST_ARRAY);
                break;
        }
        
        if(sn_cmp_array(x, y, SIZE_OF_TEST_ARRAY, 0))
        {
            printf("ERROR!\n");
            rv = 1;
            goto _err;
        }
    }
    
    sn_free_array(x, SIZE_OF_TEST_ARRAY);
    sn_free_array(y, SIZE_OF_TEST_ARRAY);
    
_err:
    END_TEST(rv, __func__)
    return rv;
}



int test_xor(int n)
{
    int rv = 0;
    sn_t x[SIZE_OF_TEST_ARRAY], y[SIZE_OF_TEST_ARRAY], z[SIZE_OF_TEST_ARRAY];
    
    INIT_TEST(__func__)
    
    sn_new_array(x, SIZE_OF_TEST_ARRAY);
    sn_new_array(y, SIZE_OF_TEST_ARRAY);
    sn_new_array(z, SIZE_OF_TEST_ARRAY);
    
    for(int i=0; i<n; i++)
    {
        bias_rand_max_array(x, SIZE_OF_TEST_ARRAY);
        bias_rand_max_array(y, SIZE_OF_TEST_ARRAY);
        
        fpco_xor(z, x, y, SIZE_OF_TEST_ARRAY);
        fpco_xor(z, z, y, SIZE_OF_TEST_ARRAY);
        
        if(sn_cmp_array(x, z, SIZE_OF_TEST_ARRAY, ACCEPTABLE_ERROR))
        {
            printf("ERROR!\n");
            rv = 1;
            goto _err;
        }
    }
    
    sn_free_array(x, SIZE_OF_TEST_ARRAY);
    sn_free_array(y, SIZE_OF_TEST_ARRAY);
    
_err:
    END_TEST(rv, __func__)
    return rv;
}



int test_shift(int n)
{
    int rv = 0;
    int shift;
    sn_t x[SIZE_OF_TEST_ARRAY], xl[SIZE_OF_TEST_ARRAY], xr[SIZE_OF_TEST_ARRAY];
    
    INIT_TEST(__func__)
    
    sn_new_array(x, SIZE_OF_TEST_ARRAY);
    sn_new_array(xl, SIZE_OF_TEST_ARRAY);
    sn_new_array(xr, SIZE_OF_TEST_ARRAY);
    
    for(int i=0; i<n; i++)
    {
        bias_rand_max_array(x, SIZE_OF_TEST_ARRAY);
        sn_cpy_array(xl, x, SIZE_OF_TEST_ARRAY);
        sn_cpy_array(xr, x, SIZE_OF_TEST_ARRAY);
        
        shift = rand()%SIZE_OF_TEST_ARRAY;
        
        fpco_shift_left(xl, x, shift, SIZE_OF_TEST_ARRAY);
        fpco_shift_right(xr, x, SIZE_OF_TEST_ARRAY - shift, SIZE_OF_TEST_ARRAY);
        
        fpco_rot_left(x, x, shift, SIZE_OF_TEST_ARRAY);
        fpco_xor(xl, xl, xr, SIZE_OF_TEST_ARRAY);
        
        if(sn_cmp_array(x, xl, SIZE_OF_TEST_ARRAY, 0))
        {
            printf("ERROR!\n");
            rv = 1;
            goto _err;
        }
    }
    
    sn_free_array(x, SIZE_OF_TEST_ARRAY);
    sn_free_array(xl, SIZE_OF_TEST_ARRAY);
    sn_free_array(xr, SIZE_OF_TEST_ARRAY);
    
_err:
    END_TEST(rv, __func__)
    return rv;
}



int test_xor_2(int n)
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
        
        fpco_xor(&x, &y, &x, 1);
        
        bias_to_prob(&c, x);
        
        d = (1-a)*b + a*(1-b);
        
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



int test_and(int n)
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
        
        fpco_and(&x, &y, &x, 1);
        
        bias_to_prob(&c, x);
        
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



int test_or(int n)
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
        
        fpco_or(&x, &y, &x, 1);
        
        bias_to_prob(&c, x);
        
        d = 1-(1-a)*(1-b);
        
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



int test_not(int n)
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
        
        fpco_not(&y, &x, 1);
        
        bias_to_prob(&b, y);
        
        c = 1-a;
        
        if(fabs(b - c)>ACCEPTABLE_ERROR)
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


int test_add(int n)
{
    int rv = 0;
    sn_t x[SIZE_OF_TEST_ARRAY], y[SIZE_OF_TEST_ARRAY], z[SIZE_OF_TEST_ARRAY], z2[SIZE_OF_TEST_ARRAY];
    double dx[SIZE_OF_TEST_ARRAY], dy[SIZE_OF_TEST_ARRAY], dz[SIZE_OF_TEST_ARRAY];
    double carry = 0;
    
    INIT_TEST(__func__)
    
    sn_new_array(x, SIZE_OF_TEST_ARRAY);
    sn_new_array(y, SIZE_OF_TEST_ARRAY);
    sn_new_array(z, SIZE_OF_TEST_ARRAY);
    sn_new_array(z2, SIZE_OF_TEST_ARRAY);
    
    for(int j=0; j<n; j++)
    {
        bias_rand_array(x, SIZE_OF_TEST_ARRAY, 2);
        bias_rand_array(y, SIZE_OF_TEST_ARRAY, 2);
        bias_to_prob_array(dx, x, SIZE_OF_TEST_ARRAY);
        bias_to_prob_array(dy, y, SIZE_OF_TEST_ARRAY);
        
        fpco_add(z, x, y, SIZE_OF_TEST_ARRAY);
        
        carry = 0;
        for(int i=0; i<SIZE_OF_TEST_ARRAY;i++)
        {
            dz[i] = carry*dx[i]*dy[i] + carry*(1-dx[i])*(1-dy[i]) + (1-carry)*dx[i]*(1-dy[i]) + (1-carry)*(1-dx[i])*dy[i];
            
            carry = carry*dx[i]*dy[i] + carry*dx[i]*(1-dy[i]) + (1-carry)*dx[i]*dy[i] + carry*(1-dx[i])*dy[i];
        }
        
        prob_to_bias_array(z2, dz, SIZE_OF_TEST_ARRAY);
        
        if(sn_cmp_array(z2, z, SIZE_OF_TEST_ARRAY, 0.01))
        {
            sn_print_array(x, SIZE_OF_TEST_ARRAY);
            sn_print_array(y, SIZE_OF_TEST_ARRAY);
            sn_print_array(z, SIZE_OF_TEST_ARRAY);
            sn_print_array(z2, SIZE_OF_TEST_ARRAY);
            printf("ERROR!\n");
            rv = 1;
            goto _err;
        }
    }
    
    sn_free_array(x, SIZE_OF_TEST_ARRAY);
    sn_free_array(y, SIZE_OF_TEST_ARRAY);
    sn_free_array(z, SIZE_OF_TEST_ARRAY);
    sn_free_array(z2, SIZE_OF_TEST_ARRAY);
    
_err:
    END_TEST(rv, __func__)
    return rv;
}


int test_sub(int n)
{
    int rv = 0;
    sn_t x[SIZE_OF_TEST_ARRAY], y[SIZE_OF_TEST_ARRAY], z[SIZE_OF_TEST_ARRAY], z2[SIZE_OF_TEST_ARRAY];
    double dx[SIZE_OF_TEST_ARRAY], dy[SIZE_OF_TEST_ARRAY], dz[SIZE_OF_TEST_ARRAY];
    double carry = 0;
    
    INIT_TEST(__func__)
    
    sn_new_array(x, SIZE_OF_TEST_ARRAY);
    sn_new_array(y, SIZE_OF_TEST_ARRAY);
    sn_new_array(z, SIZE_OF_TEST_ARRAY);
    sn_new_array(z2, SIZE_OF_TEST_ARRAY);
    
    for(int j=0; j<n; j++)
    {
        bias_rand_array(x, SIZE_OF_TEST_ARRAY, 2);
        bias_rand_array(y, SIZE_OF_TEST_ARRAY, 2);
        bias_to_prob_array(dx, x, SIZE_OF_TEST_ARRAY);
        bias_to_prob_array(dy, y, SIZE_OF_TEST_ARRAY);
        
        fpco_sub(z, x, y, SIZE_OF_TEST_ARRAY);
        
        carry = 0;
        for(int i=0; i<SIZE_OF_TEST_ARRAY;i++)
        {
            dz[i] = carry*dx[i]*dy[i] + carry*(1-dx[i])*(1-dy[i]) + (1-carry)*dx[i]*(1-dy[i]) + (1-carry)*(1-dx[i])*dy[i];
            
            carry = carry*dx[i]*dy[i] + carry*(1-dx[i])*dy[i] + carry*(1-dx[i])*(1-dy[i]) + (1-carry)*(1-dx[i])*dy[i];
        }
        
        prob_to_bias_array(z2, dz, SIZE_OF_TEST_ARRAY);
        
        if(sn_cmp_array(z2, z, SIZE_OF_TEST_ARRAY, 0.01))
        {
            sn_print_array(x, SIZE_OF_TEST_ARRAY);
            sn_print_array(y, SIZE_OF_TEST_ARRAY);
            sn_print_array(z, SIZE_OF_TEST_ARRAY);
            sn_print_array(z2, SIZE_OF_TEST_ARRAY);
            printf("ERROR!\n");
            rv = 1;
            goto _err;
        }
    }
    
    sn_free_array(x, SIZE_OF_TEST_ARRAY);
    sn_free_array(y, SIZE_OF_TEST_ARRAY);
    sn_free_array(z, SIZE_OF_TEST_ARRAY);
    sn_free_array(z2, SIZE_OF_TEST_ARRAY);
    
_err:
    END_TEST(rv, __func__)
    return rv;
}

void test_integer_operations(uint64_t *zu, uint64_t xu, uint64_t yu,
                                sn_t *x, sn_t *y, sn_t *z, int size)
{
    int r = rand()%5;
    
    switch (r) {
        case 0:
            *zu = xu ^ yu;
            fpco_xor(z, x, y, size);
            break;
        case 1:
            *zu = xu & yu;
            fpco_and(z, x, y, size);
            break;
        case 2:
            *zu = xu | yu;
            fpco_or(z, x, y, size);
            break;
        case 3:
            *zu = xu + yu;
            fpco_add(z, x, y, size);
            break;
        case 4:
            *zu = xu - yu;
            fpco_sub(z, x, y, size);
            break;
            
        default:
            break;
    }
}

int test_integer_operations_fuzzer(int n)
{
    int rv = 0, size;
    uint64_t xu,yu,zu;
    sn_t x[64],y[64],z[64];
    
    INIT_TEST(__func__)
    sn_new_array(x, 64);
    sn_new_array(y, 64);
    sn_new_array(z, 64);
    
    for(int i=0; i<n; i++)
    {
        bias_rand_max_array(x, 64);
        bias_rand_max_array(y, 64);
        
        size = rand()%4;
        
        xu=0;yu=0;zu=0;
        switch (size) {
            case 0: //u8
                bias_array_to_u8((uint8_t *)&xu, x);
                bias_array_to_u8((uint8_t *)&yu, y);
                test_integer_operations(&zu, xu, yu, x, y, z, 8);
                u8_to_bias_array(x, (uint32_t) zu);
                rv = sn_cmp_array(x, z, 8, ACCEPTABLE_ERROR);
                break;
            case 1: //u16
                bias_array_to_u16((uint16_t *)&xu, x);
                bias_array_to_u16((uint16_t *)&yu, y);
                test_integer_operations(&zu, xu, yu, x, y, z, 16);
                u16_to_bias_array(x, (uint32_t) zu);
                rv = sn_cmp_array(x, z, 16, ACCEPTABLE_ERROR);
                break;
            case 2: //u32
                bias_array_to_u32((uint32_t *)&xu, x);
                bias_array_to_u32((uint32_t *)&yu, y);
                test_integer_operations(&zu, xu, yu, x, y, z, 32);
                u32_to_bias_array(x, (uint32_t) zu);
                rv = sn_cmp_array(x, z, 32, ACCEPTABLE_ERROR);
                break;
            default:
                bias_array_to_u64((uint64_t *)&xu, x);
                bias_array_to_u64((uint64_t *)&yu, y);
                test_integer_operations(&zu, xu, yu, x, y, z, 64);
                u64_to_bias_array(x, (uint64_t) zu);
                rv = sn_cmp_array(x, z, 64, ACCEPTABLE_ERROR);
                break;
        }
        
        if(rv)
        {
            sn_print_array(x, 64);
            sn_print_array(z, 64);
            printf("it:%d ;\n%d\n%d\n%d\n",i,xu,yu,zu);
            rv = 1;
            goto _err;
        }
    }
    
_err:
    sn_free_array(x,SIZE_OF_TEST_ARRAY);
    sn_free_array(y, SIZE_OF_TEST_ARRAY);
    sn_free_array(z, SIZE_OF_TEST_ARRAY);
    END_TEST(rv, __func__)
    return rv;
}
