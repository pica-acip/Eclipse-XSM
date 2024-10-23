/*
 ============================================================================
 Name        : behavior.c
 Author      : Carsten Pitz @ private
 Version     :
 Copyright   : This code is released under the Eclipse license
 Description : C, Ansi-style, planned MISRA C compliant:
 
 Runtime to run state behaviors
 ============================================================================
 */


#include <stdio.h>

#include "sm.h"
#include "behavior.h"


void initStateData(StateDataStack *sds) {

    sds->stackIdx = 0;
}


int runService(Service *s, StateData *sd) {

    int retVal = 0;

    // run service, if service is configured
    if (*s != NULL) {
        retVal = (*s)(sd);
    }

    return retVal;
}

int runBehavior(BehaviorServices *bs, StateData *sd) {

    int retVal = 0;

    // run preceeding Behavior (preBehavior)
    {
        int serviceRetVal = runService(&(bs->preBehavior), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;
    }

    // run standard Behavior (standardBehavior)
    {
        int serviceRetVal = runService(&(bs->standardBehavior), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;
    }

    // run trailing behavior (postBehavior)
    {
        int serviceRetVal = runService(&(bs->postBehavior), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;
    }

    // return highest return value
    return retVal;
}

int runStateBehavior(StateBehaviors *sb, StateData *sd) {

    int retVal = 0;

    sd->internalStateData.state = __UNDEFINED__;

    /*
     configureDo and establishDo are run before onEntry to establish the state
     */

    // run configureDo - set the state data (StateData) accordingly
    {
        int serviceRetVal = runBehavior(&(sb->configureDo), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;

        sd->internalStateData.state = CONFIGURED;
    }

    // run establishDo - manifest the state and if required, allocate resources
    {
        int serviceRetVal = runBehavior(&(sb->establishDo), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;

        sd->internalStateData.state = ESTABLISHED;
    }

    /*
     As soon as state is established, on Entry is run
     */

    // run onEntry - entry behavior, shall be the intended behavior
    {
        int serviceRetVal = runBehavior(&(sb->onEntry), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;

        sd->internalStateData.state = ENTERED;
    }

    /*
     onExit is run within the established state
     */

    // run onExit - cleanup if required, update state
    {
        int serviceRetVal = runBehavior(&(sb->onExit), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;

        sd->internalStateData.state = EXITED;
    }

    /*
     unestablishDo is run after onExit to unestablish the state again
     */

    // run unestablishDo - perform some cleanup and free resource allocations if required
    {
        int serviceRetVal = runBehavior(&(sb->unestablishDo), sd);
        retVal = serviceRetVal > retVal ? serviceRetVal : retVal;

        sd->internalStateData.state = UNESTABLISHED;
    }

    // return highest return value
    return retVal;
}

/*
 ================================================================================
 to be externalized
 ================================================================================
 */

int sampleSuccededService(StateData *sd) {
    printf("State %s in state %i : %i\n", sd->internalStateData.name, sd->internalStateData.state, sd->serviceProvided);
    return 0;
}

int sampleFailedService(StateData *sd) {
    printf("State %s in state %i : %i\n", sd->internalStateData.name, sd->internalStateData.state, sd->serviceProvided);
    printf("%i\n", sd->serviceProvided);
    return 1;
}


void configureStateBehaviors(StateBehaviors *sb) {

    // configure configureDo behaviors
    sb->configureDo.standardBehavior = &sampleSuccededService;
    sb->configureDo.preBehavior = NULL;
    sb->configureDo.postBehavior = NULL;

    // configure establishDo behaviors
    sb->establishDo.standardBehavior = NULL;
    sb->establishDo.preBehavior = NULL;
    sb->establishDo.postBehavior = NULL;

    // configure onEntry behaviors
    sb->onEntry.standardBehavior = NULL;
    sb->onEntry.preBehavior = NULL;
    sb->onEntry.postBehavior = NULL;

    // configure onExit behavior
    sb->onExit.standardBehavior = NULL;
    sb->onExit.preBehavior = NULL;
    sb->onExit.postBehavior = NULL;

    // configure unestablishDo behavior
    sb->unestablishDo.standardBehavior = NULL;
    sb->unestablishDo.preBehavior = NULL;
    sb->unestablishDo.postBehavior = &sampleFailedService;
}

/*
 ================================================================================
 */

