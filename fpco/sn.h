//
//  sn.h
//  ProbabilisticOps

#ifndef sn_h
#define sn_h

#include <stdio.h>
#include "../deps/include_relic/relic.h"

/*
 A small number is a number in the form:
 mantissa*10^{-expoent},
 where -1<mantissa<1 and y is represented as a big number.
 The purpose of sn_st is to create the possibility of tracking a number that is rapidly approaching zero. It is not the purpose of sn_st to be a double with more precision or decimal places.
*/
typedef struct {
    double mantissa;
    bn_t expoent;
} sn_st;

typedef sn_st sn_t[1];

#define LIMIT_FOR_DOUBLE_GENERATION 100000

extern int sn_core_initialized;
extern bn_t zero;
extern bn_t one;
extern bn_t fifteen;
extern sn_t half;
extern sn_t mhalf;
extern sn_t snone;
extern sn_t snminusone;

/**
 * Initialize the use of the sn operations.
 */
int sn_core_init(void);

/**
 * Finalize the use of the sn operations.
 */
int sn_core_finalize(void);

/**
 * Prints a small number.
 *
 * @param[in] sn            - the small number to print.
 */
void sn_print(sn_t sn);

/**
 * Prints a small number array.
 *
 * @param[in] sn            - the small number array to print.
 * @param[in] size           - the size of the vector
 */
void sn_print_array(sn_t *sn, int size);


/**
 * Creates a new small number.
 *
 * @param[out] a            - the small number to be initialized.
 */
void sn_new(sn_t a);


/**
 * Creates a new small number array.
 *
 * @param[out] a            - the small number array to be initialized.
 * @param[in] size         - the size of the array.
 */
void sn_new_array(sn_t *a, int size);

/**
 * Frees a small number.
 *
 * @param[out] a            - the small number to be finalized.
 */
void sn_free(sn_t a);

/**
 * Frees a small number array.
 *
 * @param[out] a            - the small number array to be freed.
 * @param[in] size         - the size of the array.
 */
void sn_free_array(sn_t *a, int size);


/**
 * Copy small number.
 *
 * @param[in] src            - the small number to be copied.
 * @param[out] dst           - the result
 */
void sn_cpy(sn_t dst, sn_t src);

/**
 * Copy small number array.
 *
 * @param[in] src            - the small number to be copied.
 * @param[out] dst           - the result
 */
void sn_cpy_array(sn_t *dst, sn_t *src, int size);

/**
 * Returns the result of a signed comparison between two small numbers.
 *
 * @param[in] a                - the first small number.
 * @param[in] b                - the second small number.
 * @param[in] acceptable_error - if the diference in the mantissa is less than the acceptable_error the function returns 0, as it was equal.
 * @return -1 if a < b, 0 if a == b and 1 if a > b.
 */
int sn_cmp(sn_t a, sn_t b, double acceptable_error);

/**
 * Returns the result of a comparison between the magnitude or scale of two small number.
 *
 * @param[in] a                - the first small number.
 * @param[in] b                - the second small number.
 * @param[in] acceptable_error - if the diference in the expoent is less than the acceptable_error the function returns 0, as it was equal.
 * @return -1 if a->expoent < b->expoent, 0 if a->expoent == b->expoent and 1 if a->expoent > b->expoent.
 */
int sn_cmp_magnitude(sn_t a, sn_t b, uint64_t acceptable_error);

/**
 * Compares two small number arrays.
 *
 * @param[in] a                - the first small number array.
 * @param[in] b                - the second small number array.
 * @param[in] size             - the size of the small number array.
 * @param[in] acceptable_error - if the diference in the mantissa is less than the acceptable_error the function returns 0, as it was equal.
 * @return 0 if a[i] == b[i] for all i, returns 1 otherwise.
 */
int sn_cmp_array(sn_t *a, sn_t *b, int size, double acceptable_error);

/**
 * Returns the result of a comparison between the magnitude or scale of two small number arrays.
 *
 * @param[in] a                - the first small number array.
 * @param[in] b                - the second small number array.
 * @param[in] acceptable_error - if the diference in the expoent is less than the acceptable_error the function returns 0, as it was equal.
 * @return 0 if a[i]->expoent == b[i]->expoent for all i, returns 1 otherwise.
 */
int sn_cmp_magnitude(sn_t a, sn_t b, uint64_t acceptable_error);


/**
 * Updates the range of the small number in such a way that sets -1<mantissa<1.
 *
 * @param[in,out] sn            - the small number to update.
 */
void sn_update_range(sn_t sn);

/**
 * Generates a random small number.
 * WARNING: this function is not secure, used only for tests
 *
 * @param[out] sn            - the random small number.
 * @param[in] max_bits        - maximum number of bits for the big number 'expoent'.
 */
void sn_rand(sn_t sn, int max_bits);


/**
 * Generates a random small number array.
 * WARNING: this function is not secure, used only for tests
 *
 * @param[out] a            - the random small number.
 * @param[in] size            - the size of the array.
 * @param[in] max_bits        - maximum number of bits for the big number 'expoent'.
 */
void sn_rand_array(sn_t *a, int size, int max_bits);

/**
 * Converts a small number to a double.
 *
 * @param[in] sn            - the small number to convert.
 * @param[out] d             - the converted double.
 *
 * @return - 0 for success, 1 if the conversion is impossible given the small number
 */
int sn_to_double(double *d, sn_t sn);

/**
 * Converts a small number array to a double array.
 *
 * @param[in] sn            - the small number array to convert.
 * @param[out] d             - a pointer to return the converted double array
 * @param[in] size           - the size of the array
 */
void sn_to_double_array(double *d, sn_t *sn, int size);

/**
 * Converts a double to a small number.
 *
 * @param[in] d           - the double to convert.
 * @param[out] sn         - pointer to receive the converted small number.
 */
void double_to_sn(sn_t sn, double d);

/**
 * Converts a double array to a small number array.
 *
 * @param[out] sn            - a pointer to return the converted small number array
 * @param[in] d             - the double array
 * @param[in] size           - the size of the array
 */
void double_to_sn_array(sn_t *sn, double *d, int size);

/**
 * Multiplies two small numbers.
 *
 * @param[out] c   -  the result
 * @param[in] a    -  the first small number to multiply
 * @param[in] b    -  the second small number to multiply
 */
void sn_mul(sn_t c, sn_t a, sn_t b);

/**
 * Adds two small numbers.
 *
 * @param[out] c   -  the result
 * @param[in] a    -  the first small number to add
 * @param[in] b    -  the second small number to add
 */
void sn_add(sn_t c, sn_t a, sn_t b);


/**
 * Absolute value of small number.
 *
 * @param[out] c   -  the result
 * @param[in] a    -  the small number.
 */
void sn_abs(sn_t c, sn_t a);

/**
 * Absolute value of small number array.
 *
 * @param[out] c   -  the result
 * @param[in] a    -  the small number.
 * @param[in] size           - the size of the array
 */
void sn_abs_array(sn_t *c, sn_t *a, int size);

#endif /* precise_double_h */
