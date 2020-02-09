//
//  probabilistic_ops.h

#ifndef probabilistic_ops_h
#define probabilistic_ops_h

#include <stdio.h>
#include "sn.h"

/**
 * Generates a random probability bias.
 * WARNING: this function is not secure, used only for tests
 *
 * @param[out] bias            - the result.
 * @param[in] max_bits        - maximum number of bits for the big number 'expoent'.
 */
void bias_rand(sn_t bias, int max_bits);

/**
 * Generates a random probability bias.
 * WARNING: this function is not secure, used only for tests
 *
 * @param[out] bias           - the result array.
 * @param[in]                 - the size of the array.
 * @param[in] max_bits        - maximum number of bits for the big number 'expoent'.
 */
void bias_rand_array(sn_t *bias, int size, int max_bits);

/**
 * Generates a random maximum probability bias (1 or -1).
 * WARNING: this function is not secure, used only for tests
 *
 * @param[out] bias            - the result.
 */
void bias_rand_max(sn_t bias);

/**
 * Generates a random maximum probability bias array (1 or -1).
 * WARNING: this function is not secure, used only for tests
 *
 * @param[out] bias           - the result array.
 * @param[in]  size              - the size of the array.
 */
void bias_rand_max_array(sn_t *bias, int size);

/**
 * Corrects the bias probability to be between -1 and 1.
 *
 * @param[in,out] sn  -  the bias to be checked
 */
void bias_correct_boundaries(sn_t sn);

/**
 * Computes the max, in absolute terms, of two probability biases.
 *
 * @param[out] max  -  the result
 * @param[in] x1    -  the first bias
 * @param[in] x2    -  the second bias
 */
void bias_max(sn_t max, sn_t x1, sn_t x2);

/**
 * Computes converts a probability (double) to a bias (sn).
 *
 * @param[out] bias  -  the result
 * @param[in] prob    -  the probability
 */
void prob_to_bias(sn_t bias, double prob);

/**
 * Computes converts a probability array (double) to a bias array (sn).
 *
 * @param[out] bias  -  the result
 * @param[in] prob    -  the probability
 * @param[in] size  - the size of the array
 */
void prob_to_bias_array(sn_t *bias, double *prob, int size);


/**
 * Computes converts a bias (sn) a probability (double).
 *
 * @param[out] prob  -  the result
 * @param[in] bias    -  the bias
 */
void bias_to_prob(double *prob, sn_t bias);

/**
 * Computes converts a bias array (sn) a probability array (double).
 *
 * @param[out] prob  -  the result
 * @param[in] bias    -  the bias
 * @param[in] size  - the size of the array
 */
void bias_to_prob_array(double *prob, sn_t *bias, int size);

/**
 * Multiply two probabilities represented as bias.
 *
 * @param[out] c  -  the result
 * @param[in] a    -  the bias to be multiplied
 * @param[in] b  - the bias to be multiplied
 */
void prob_mult_through_bias(sn_t c, sn_t a, sn_t b);


/**
 * Adds two probabilities represented as bias.
 *
 * @param[out] c  -  the result
 * @param[in] a    -  the bias to be added
 * @param[in] b  - the bias to be added
 */
void prob_sum_through_bias(sn_t c, sn_t a, sn_t b);


/**
 * Complement a probability represented as bias.
 *
 * @param[out] c  -  the result
 * @param[in] a    -  the bias
 */
void prob_complement_through_bias(sn_t c, sn_t a);


/**
 * Converts a integer (u8, u16, u32 or u64) to a bias array.
 *
 * @param[out] v  -  the result array, it must be previously allocated.
 * @param[in]  x  -  the integer
 */
void u8_to_bias_array(sn_t *v, uint8_t x);
void u16_to_bias_array(sn_t *v, uint16_t x);
void u32_to_bias_array(sn_t *v, uint32_t x);
void u64_to_bias_array(sn_t *v ,uint64_t x);


/**
 * Converts bias array to a integer (u8, u16, u32 or u64).
 *
 * @param[out] x  -  the result.
 * @param[in]  v  -  the input array, it is assumed to have the correct number of elements.
 */
void bias_array_to_u8(uint8_t *x, sn_t *v);
void bias_array_to_u16(uint16_t *x, sn_t *v);
void bias_array_to_u32(uint32_t *x, sn_t *v);
void bias_array_to_u64(uint64_t *x, sn_t *v);

#endif /* precise_probabilistic_ops_h */
