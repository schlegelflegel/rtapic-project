/**
 * @file granular.h
 * @author Amon Benson (amonkbenson@gmail.com)
 * @brief Granular Synthesizer
 * @version 0.1
 * @date 2021-07-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "circbuf.h"


/**
 * @struct granular
 * @brief granular delay based around a circular buffer
 * 
 * This class contains all information and provides functions regarding the core granular delay.
 * It does also contain functions to manipulate the delay (grain size, etc.)
 */
typedef struct {
    circbuf *buffer; /**< circular buffer used to sample the grains */
} granular;

/**
 * @memberof granular
 * @brief create a new granular object
 * 
 * @return granular* a reference to the allocated granular object or `NULL` if the allocation failed
 */
granular *granular_new(void);

/**
 * @memberof granular
 * @brief frees an existing granular object
 * 
 * @param g the granular instance to be freed. Must not be `NULL`.
 */
void granular_free(granular *g);

/**
 * @memberof granular
 * @brief main signal processing function of the granular delay
 * 
 * @param g the granular object
 * @param in the input buffer where data is read from
 * @param out the output buffer where data is written to
 * @param n the number of samples to be processed. This is also the size of the input and output buffers
 */
void granular_perform(granular *g, float *in, float *out, int n);
