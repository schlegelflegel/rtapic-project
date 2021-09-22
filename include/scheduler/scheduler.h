/**
 * @file scheduler.h
 * @author zeyu yang (zeyuuyang42@gmail.com)
 * @brief scheduler is a instance that store all user adjustable configs
 *        like the size of grains, inter onset between grains. 
 *        granular polls the statue in scheduler to get configs for grain arragment.
 *        At version 0.1 all configs are temporarily constant
 *        but little randomness will be involved for justifying the correctness of current granular structre
 *        functions for adjusting all configs with a human-friendly method will be added at upcoming version 
 * @version 0.2
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <stdio.h>
#include <stdlib.h> // for the rand function
#include <time.h>   // for seed

#include "util/mem.h"
#include "util/util.h"

#include "m_pd.h" // add for post function, remove this after debuging

#include "params.h"
#include "control/manager.h"


/**
 * @struct scheduler
 * @brief scheduler class
 * 
 * The scheduler class contains all user adjustable configs
 */
typedef struct {
    // basic user adjustable configs
    control_parameter *gransize;  /**< the size of sampled grains also for corresponding evelope*/
    int interonset;     /**< the onset difference between two grains that been sampled */
    int maxinteronset;  /**< the maximun onset difference between two grains to be synthesized */
    int mininteronset;  /**< the minimun onset difference between two grains to be synthesized */
    int eveloptype;     /**< type of evelop used for grain generation procedure */


    // configs that changed at each dsp routine
    int fetchgrain;     /**< the number of grains sampled */
    int synthgrain;     /**< the number of grains synthesized */

    // advance user adjustable configs 
    int getpitch;       /**< enable the pitch detection or not, 0 for disable */
    int getenergy;      /**< enable the energy detection or not, 0 for disable */
    float pitch;        /**< wished pitch of transformed grain, e.g. 440Hz for all upcoming grains*/
    float energy;       /**< wished energy of transformed grain, e.g. 0.5 for all upcoming grains */
    float pitchratio;   /**< wished energy of transformed grain, e.g. 2*higher(octave) for all upcoming grains*/
    float energyratio;  /**< wished energy of transformed grain, e.g. 2*louder for all upcoming grains */

}scheduler, *p_scheduler; /**< pointer to a scheduler */


/**
 * @memberof scheduler
 * @brief creates a scheduler object
 * 
 * This method creates a scheduler object contains all the adjustable configs that needed for grain arragment
 * 
 * @return scheduler* a reference to the scheduler object or `NULL` if failed
 */
scheduler *scheduler_new(control_manager *mgr);

/**
 * @memberof scheduler
 * @brief frees a scheduler object
 * 
 * This method frees a scheduler object
 * 
 * @param sd the scheduler object to be freed
 */
void scheduler_free(scheduler *sd);

/**
 * @memberof scheduler
 * @brief get the next interonset 
 * 
 * This method choses a random number between maxinteronset and mininteronset as the interonset of next grain
 * 
 * @param max the maximum interonset
 * @param min the minimum interonset
 * @param slot the allowed slot interonset (must sample as interger of new samples of dsp routine)
 * 
 * @return int the length of next interonset 
 */
int scheduler_get_next_interonset(int max, int min, int slot); 

/**
 * @memberof scheduler
 * @brief update configs at each dsp routin
 * 
 * This method updates the configs at each dsp routine
 * Configs could change automaticly or under user's adjustion
 * 
 * @param sd the scheduler object to be processed
 */
void scheduler_perform(scheduler *sd, int n);

/**
 * @memberof scheduler
 * @brief update configs for controlling the fetch and synth process
 * 
 * This method updates the counter(fetchgrain/synthgrain) at each dsp routine
 * 
 * @param sd the scheduler object to be processed
 */
void scheduler_update_counter(scheduler *sd, int n);