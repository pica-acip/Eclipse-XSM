
/*
 ============================================================================
 Name        : sm.c
 Author      : Carsten Pitz @ private
 Version     :
 Copyright   : This code is released under the Eclipse license
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <assert.h>

 #include "sm.h"

StateData getStateData(const StateDataStack *sds) {

    const int idx = sds->stackIdx;
   
    assert(idx >= 0); // make access to invalid data fail
    assert(idx <= HISTORY_DEPTH); // make access to invalid data fail

    return sds->data[idx];
}

StateData popStateData(StateDataStack *sds) {

    const int idx = --(sds->stackIdx); 
   
    assert(idx >= 0); // make access to invalid data fail
    assert(idx <= HISTORY_DEPTH);  // make access to invalid data fail

    return sds->data[idx];
}

void copyStateData(const int destIdx, const int srcIdx, StateDataStack *sds) {

    sds->data[destIdx].internalStateData.name = sds->data[srcIdx].internalStateData.name;
    sds->data[destIdx].internalStateData.state = sds->data[srcIdx].internalStateData.state;

    sds->data[destIdx].serviceProvided = sds->data[srcIdx].serviceProvided;
}

StateData pushStateData(StateDataStack *sds) {

    const int idx = ++(sds->stackIdx);

    copyStateData(idx, idx-1, sds);

    assert(idx >= 0); // make access to invalid data fail
    assert(idx <= HISTORY_DEPTH); // make access to invalid data fail

    return sds->data[idx];
}
