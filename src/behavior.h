/*
 ============================================================================
 Name        : behavior.c
 Author      : Carsten Pitz @ private
 Version     :
 Copyright   : This code is released under the Eclipse license
 Description : C, Ansi-style, planned MISRA C compliant:
 
 header of runtime to run state behaviors
 ============================================================================
 */

#include "sm.h"

#ifndef BEHAVIOR_H

#define BEHAVIOR_H 1

typedef int (*Service)(StateData*);

typedef struct  {

    /*
     Each BehaviorServices behavior provides a standard behavior. (standardBehavior)
     This standard behavior can be modified by preceeding behavior (preBehavior) and trailing behavior (postBehavior)
     without touching the standard behavior code.
     */

    Service standardBehavior;

    Service preBehavior;
    Service postBehavior;
} BehaviorServices;

typedef struct  {

    /*
     UML /onEntry and /onExit behaviors are straight forward.

    But /do behaviors need some interpretation, so /do is implemented as
      configureDo - set StateData data accordingly (i.e. set serviceProvided to false), no further action
      establishDo - set device into state according to StateData data (i.e. signal serviceProvided state on LIN bus and lock that state)
      unestablishDo - perform cleanup if required (i.e. unlock serviceProvided state)
     */

    BehaviorServices configureDo;
    BehaviorServices establishDo;
    BehaviorServices onEntry;
    BehaviorServices onExit;
    BehaviorServices unestablishDo;
} StateBehaviors;

void initStateData(StateDataStack *sds);
int runStateBehavior(StateBehaviors *sb, StateData *sd);

void configureStateBehaviors(StateBehaviors *sb); // externalize

#endif
