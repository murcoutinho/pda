//
//  probabilistic_ops_tests.h
//  ProbabilisticOps

#ifndef probabilistic_ops_tests_h
#define probabilistic_ops_tests_h

#include <stdio.h>

/**
 * Tests the bias_max function.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_bias_max(int n);


/**
 * Tests the probability to bias conversion.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_prob_to_bias(int n);


/**
 * Tests the probability multiplication through bias.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_prob_mult_through_bias(int n);


/**
 * Tests the probability addition through bias.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_prob_sum_through_bias(int n);


/**
 * Tests the probability complement through bias.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_prob_complement_through_bias(int n);

#endif /* probabilistic_ops_tests_h */
