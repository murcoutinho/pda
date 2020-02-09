//
//  fpco_tests.h
//  ProbabilisticOps

#ifndef fpco_tests_h
#define fpco_tests_h

#include <stdio.h>

/**
 * Tests the rotating to the left and right.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_rotation(int n);


/**
 * Tests the XOR.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_xor(int n);
int test_xor_2(int n);

/**
 * Tests the shift operation.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_shift(int n);


/**
 * Tests the AND.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_and(int n);


/**
 * Tests the OR.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_or(int n);


/**
 * Tests the NOT.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_not(int n);


/**
 * Tests the ADD.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_add(int n);


/**
 * Tests the SUB.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_sub(int n);

/**
 * Tests the functions XOR, AND, OR, SUM.
 *
 * @param[in] n    - the number of test to be executed.
 */
int test_integer_operations_fuzzer(int n);


#endif /* fpco_tests_h */
