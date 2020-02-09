//
//  fpco.h (Fundamental Probabilistic Cryptographic Operations)
//  ProbabilisticOps

#ifndef fpco_h
#define fpco_h

#include <stdio.h>
#include "sn.h"

extern int fpco_core_initialized;
extern int global_max_size_of_bias_arrays;
extern sn_t *aux;

/**
 * Initialize the use of the fpco operations.
 */
int fpco_core_init(int max_size_of_bias_arrays);

/**
 * Finalize the use of the fpco operations.
 */
int fpco_core_finalize(void);

/**
 * Rotate right.
 *
 * @param[in] in            - the small number to be copied.
 * @param[out] out          - the result
 * @param[in] shift         - defines the rotation.
 * @param[in] size          - the size of the array.
 */
int fpco_rot_right(sn_t *out, sn_t *in, int shift, int size);

/**
 * Rotate left.
 *
 * @param[in] in            - the small number to be copied.
 * @param[out] out          - the result
 * @param[in] shift         - defines the rotation.
 * @param[in] size          - the size of the array.
 */
int fpco_rot_left(sn_t *out, sn_t *in, int shift, int size);

/**
 * Shift right.
 *
 * @param[in] in            - the small number to be copied.
 * @param[out] out          - the result
 * @param[in] shift         - defines the shift.
 * @param[in] size          - the size of the array.
 */
int fpco_shift_right(sn_t *out, sn_t *in, int shift, int size);

/**
 * Shift left.
 *
 * @param[in] in            - the small number to be copied.
 * @param[out] out          - the result
 * @param[in] shift         - defines the shift.
 * @param[in] size          - the size of the array.
 */
int fpco_shift_left(sn_t *out, sn_t *in, int shift, int size);

/**
 * XOR. (c = b^a)
 *
 * @param[out] a            - the result
 * @param[in] b             - the first bias array
 * @param[in] c             - the second bias array
 * @param[in] size          - the size of the array.
 */
int fpco_xor(sn_t *c, sn_t *a, sn_t *b, int size);


/**
 * AND. (c = b&a)
 *
 * @param[out] a            - the result
 * @param[in] b             - the first bias array
 * @param[in] c             - the second bias array
 * @param[in] size          - the size of the array.
 */
int fpco_and(sn_t *c, sn_t *a, sn_t *b, int size);


/**
 * OR. (c = b|a)
 *
 * @param[out] a            - the result
 * @param[in] b             - the first bias array
 * @param[in] c             - the second bias array
 * @param[in] size          - the size of the array.
 */
int fpco_or(sn_t *c, sn_t *a, sn_t *b, int size);


/**
 * NOT. (out = !in)
 *
 * @param[out] out            - the result
 * @param[in] in             - the bias array
 * @param[in] size          - the size of the array.
 */
int fpco_not(sn_t *out, sn_t *in, int size);


/**
 * ADD. (c = a+b)
 *
 * @param[out] a            - the result
 * @param[in] b             - the first bias array
 * @param[in] c             - the second bias array
 * @param[in] size          - the size of the array.
 */
int fpco_add(sn_t *c, sn_t *a, sn_t *b, int size);


/**
 * SUB. (c = a-b)
 *
 * @param[out] a            - the result
 * @param[in] b             - the first bias array
 * @param[in] c             - the second bias array
 * @param[in] size          - the size of the array.
 */
int fpco_sub(sn_t *c, sn_t *a, sn_t *b, int size);

#endif /* fpco_h */
