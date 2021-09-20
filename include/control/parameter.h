#pragma once

#include "control/modulator.h"
#include <stddef.h>

#define CONTROL_NUM_SLOTS 3


typedef struct control_parameter_slot {
    control_modulator *mod;
    float amount;
} control_parameter_slot;

typedef struct control_parameter {
    const char *name;

    control_parameter_slot slots[CONTROL_NUM_SLOTS];

    float offset;
    float min;
    float max;
    float value;

    struct control_parameter *next;
} control_parameter;


control_parameter *control_parameter_new(const char *name, float default_value, float min, float max);

void control_parameter_free(control_parameter *p);


void control_parameter_add_modulator(control_parameter *p, size_t slot, control_modulator *mod);

void control_parameter_remove_modulator(control_parameter *p, size_t slot);

void control_parameter_set_amount(control_parameter *p, size_t slot, float amount);


float control_parameter_as_float(control_parameter *p);

int control_parameter_as_int(control_parameter *p);
