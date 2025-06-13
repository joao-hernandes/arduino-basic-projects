#ifndef ELTRIC_OVEN_HEADER
#define ELETRIC_OVEN_HEADER

//Máquina de estados
enum State {
    STATE_MENU,
    STATE_TIMER,
    STATE_TEMPERATURE,
    STATE_FAN,
    STATE_SERIAL,
    STATE_RUN,
    STATE_END};
extern State currentState;                              //Estado inicial

#endif