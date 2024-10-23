/*
 ============================================================================
 Name        : xsm.c
 Author      : Carsten Pitz @ private
 Version     :
 Copyright   : This code is released under the Eclipse license
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef SM_H

#define SM_H 1

#define HISTORY_DEPTH 3

typedef enum {
    __UNDEFINED__ = 0,
    CONFIGURED = 1,
    ESTABLISHED = 2,
    ENTERED = 3,
    EXITED = 4,
    UNESTABLISHED = 5,
} StateStates;

typedef struct {
    char* name;
    StateStates state;
} InternalStateData;

typedef struct {
    InternalStateData internalStateData;
    int serviceProvided;
} StateData;

typedef struct {
    int stackIdx;
    StateData data[HISTORY_DEPTH + 1];
} StateDataStack;

StateData getStateData(const StateDataStack *sds);
StateData popStateData(StateDataStack *sds);
StateData pushStateData(StateDataStack *sds);

#endif
