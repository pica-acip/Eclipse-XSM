/*
 ============================================================================
 Name        : xsm.c
 Author      : Carsten Pitz @ private
 Version     :
 Copyright   : This code is released under the Eclipse license
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <stdio.h>

 #include "sm.h"
 #include "behavior.h"

int main(int argc, const char * argv[]) {

    printf("================================================================================\n");  
    printf("Ptr fun!\n");
    printf("================================================================================\n"); 

    // declare services
    static StateBehaviors mySampleStateBehaviors;

    // configure services
    configureStateBehaviors(&mySampleStateBehaviors);

    // declare state data
    static StateDataStack mySampleStateDataStack;
    initStateData(&mySampleStateDataStack);

    // configure state data
    {
        printf("================================================================================\n"); 
        printf("configure\n");
        StateData sd = getStateData(&mySampleStateDataStack);
        printf("%lu\n", (unsigned long) &sd);
        sd.serviceProvided = 0;
        sd.internalStateData.name = "SAMPLE";

        printf("State name is %s\n", sd.internalStateData.name);

    // run services

        printf("================================================================================\n"); 
        printf("run\n");

        printf("State name is %s\n", sd.internalStateData.name);

        const int retVal = runStateBehavior(&mySampleStateBehaviors, &sd);
        printf("State returned with return value %i\n", retVal);
    }

    {
        printf("================================================================================\n"); 
        printf("push\n");printf("run\n");
        StateData sd = pushStateData(&mySampleStateDataStack);
        
        printf("%lu\n", (unsigned long) &sd);

        printf("State name is %s\n", sd.internalStateData.name);

        sd.serviceProvided = 1;
        const int retVal = runStateBehavior(&mySampleStateBehaviors, &sd);
        printf("State returned with return value %i\n", retVal);
    }

    {
          printf("================================================================================\n"); 
        printf("pop\n");
        StateData sd = popStateData(&mySampleStateDataStack);
        printf("%lu\n", (unsigned long) &sd);

        printf("State name is %s\n", sd.internalStateData.name);

        printf("Stack pointer is %i\n", mySampleStateDataStack.stackIdx );
        sd.serviceProvided = 1;
        const int retVal = runStateBehavior(&mySampleStateBehaviors, &sd);
        printf("State returned with return value %i\n", retVal);
    }

    return 0;
}
