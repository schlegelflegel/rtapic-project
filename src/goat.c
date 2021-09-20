#include "goat.h"

#include <stdlib.h>
#include "control/manager.h"


goat *goat_new(void) {
    goat *g = malloc(sizeof(goat));
    if (!g) return NULL;

    g->mgr = control_manager_new();
    if (!g->mgr) return NULL;

    g->modbank = modulator_bank_new(g->mgr);
    if (!g->modbank) return NULL;

    g->gran = granular_new();
    if (!g->gran) return NULL;

    g->schdur = scheduler_new(g->mgr);
    if (!g->schdur) return NULL;   

    // TODO: testing
    control_parameter *gransize = control_manager_parameter_by_name(g->mgr, "gransize");

    gransize->offset = 2000.0f;
    control_parameter_add_modulator(gransize, 0, &g->modbank->lfo1->super);
    control_parameter_set_amount(gransize, 0, 2000.0f);    

    return g;
}

void goat_free(goat *g) {
    modulator_bank_free(g->modbank, g->mgr);
    control_manager_free(g->mgr);
    granular_free(g->gran);
    scheduler_free(g->schdur);
    free(g);
}

void goat_perform(goat *g, float *in, float *out, int n) {
    control_manager_perform(g->mgr, in, n);
    scheduler_perform(g->schdur);
    granular_perform(g->gran, g->schdur, in, out, n); // update the buffer and manipulate the DelayLine
}
