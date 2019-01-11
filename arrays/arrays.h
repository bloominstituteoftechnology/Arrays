#ifndef statemachines_h
#define statemachines_h

typedef struct State {
  char *name;
} State;

typedef struct Transition {
  char *name;
  struct State *origin;
  struct State *destination;
} Transition;

typedef struct StateMachine {
  struct State *current_state;

  int num_states;
  int state_capacity;
  struct State **states;

  int num_transitions;
  int transition_capacity;
  struct Transition **transitions;
} StateMachine;


StateMachine *create_state_machine (int state_capacity, int transition_capacity);

State *sm_add_state(StateMachine *sm, char *state_name);

Transition *sm_add_transition(StateMachine *sm, char *transition_name,
                              char *origin_state_name, char *destination_state_name);

State *sm_do_transition(StateMachine *sm, char *transition_name);

void destroy_state_machine(StateMachine *sm);


#endif