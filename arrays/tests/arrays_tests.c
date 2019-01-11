#include <arrays.h>
#include "../utils/minunit.h"

char *basic_state_machine_test()
{
    StateMachine *sm = create_state_machine(3, 3);

    sm_add_state(sm, "STATE_1");
    sm_add_state(sm, "STATE_2");
    sm_add_state(sm, "STATE_3");

    sm_add_transition(sm, "MOVE", "STATE_1", "STATE_2");
    sm_add_transition(sm, "MOVE", "STATE_2", "STATE_1");
    sm_add_transition(sm, "FLY", "STATE_2", "STATE_3");

    mu_assert(strcmp(sm->current_state->name, "STATE_1") == 0, "State not initialized");
    sm_do_transition(sm, "MOVE");
    mu_assert(strcmp(sm->current_state->name, "STATE_2") == 0, "State transition failed");
    sm_do_transition(sm, "MOVE");
    mu_assert(strcmp(sm->current_state->name, "STATE_1") == 0, "State transition failed");

    destroy_state_machine(sm);

    return NULL;
}


char *all_tests()
{
    mu_suite_start();

    mu_run_test(basic_state_machine_test);

    return NULL;
}

RUN_TESTS(all_tests);