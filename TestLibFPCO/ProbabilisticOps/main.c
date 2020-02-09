//
//  main.c
//  ProbabilisticOps

/*
 This test suit was develop to check consistency of the probabilistic operations.
 Since some of these tests are dependent on numerical conversions and approximations,
 it is possible to get errors (false positives) on some tests from time to time. Increasing the constant ACCEPTABLE_ERROR, in test_configuration.h, reduces the probability of these false positives.
 */

#include <stdio.h>
#include "small_number_tests.h"
#include <time.h>
#include "probabilistic_ops_tests.h"
#include "fpco_tests.h"
#include "fpco.h"
#include "test_configuration.h"


int test_sn(void)
{
    test_init_and_print_precise_double(GENERAL_NUMBER_OF_TEST_ITERATIONS);
    test_init_and_print_precise_double_array(GENERAL_NUMBER_OF_TEST_ITERATIONS);
    if(test_sn_update_range(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    if(test_double_to_sn_conversions(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    if(test_sn_mul(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    if(test_sn_add(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    return 0;
}

int test_probabilistic_ops(void)
{
    if(test_bias_max(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_prob_to_bias(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_prob_mult_through_bias(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_prob_sum_through_bias(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_prob_complement_through_bias(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    return 0;
}


int test_fpco(void)
{
    if(test_rotation(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_xor(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_xor_2(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_shift(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_and(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_or(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_not(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_add(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_sub(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    if(test_integer_operations_fuzzer(GENERAL_NUMBER_OF_TEST_ITERATIONS))
        return 1;
    
    return 0;
}


int main(int argc, const char * argv[]) {
    if (core_init() != STS_OK) {
        core_clean();
        return 1;
    }
    if (fpco_core_init(64) != 0) {
        return 1;
    }
    srand((unsigned int) time(NULL));
    
    if(test_sn())
        return 1;
    
    if(test_probabilistic_ops())
       return 1;
    
    if(test_fpco())
        return 1;
    
    fpco_core_finalize();
    return 0;
}
