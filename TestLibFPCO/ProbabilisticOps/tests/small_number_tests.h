//
//  small_number_tests.h
//  ProbabilisticOps

#ifndef small_number_tests_h
#define small_number_tests_h

#include <stdio.h>

/**
 * Generate a random small number and prints it.
 *
 * @param[in] n    - the number of test to be executed.
 */
void test_init_and_print_precise_double(int n);

/**
 * Generate a random small number array and prints it.
 *
 * @param[in] n    - the number of test to be executed.
 */
void test_init_and_print_precise_double_array(int n);

/**
 * Tests the update range function.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_sn_update_range(int n);

/**
 * Tests the conversion from double to pd, and from pd to double.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_double_to_sn_conversions(int n);

/**
 * Tests the multiplication of small numbers.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_sn_mul(int n);

/**
 * Tests the sum of small numbers.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_sn_add(int n);

#endif /* precise_double_tests_h */
