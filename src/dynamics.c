#include "dynamics.h"
#include <stdio.h>
#include <stdlib.h>

/*
*    Allocate the memory needed.
*    Return 0 if successful
*    Return -1 if dim or num_param is negative
*    Return -2 if allocation failed
*/
short InitializeSystem(struct system *sys, const short dim,
                       const short num_param)
{
    // Check for negative dimensions
    if(dim < 0 || num_param < 0)
        return -1;

    sys->dimension = dim;
    sys->time = 0.0;

    // Allocate the memory
    sys->state = (double*) malloc(dim*sizeof(double));
    sys->params = (double*) malloc(num_param*sizeof(double));

    // Check for allocation errors
    if(sys->state == NULL || sys->params == NULL)
    {
        // Security checks in order to avoid memory leaks
        if(sys->state != NULL)
        {
            free(sys->state);
            sys->state = NULL;
        }
        if(sys->params != NUll)
        {
            free(sys->params);
            sys->params = NULL;
        }
        return -2;
    }
    return 0; // No errors found
}

/*
*    Free the allocated memory
*/
void FreeSystem(struct system *sys)
{
    if(sys == NULL) return;
    
    if(sys->state != NULL)
    {
        free(sys->state);
        sys->state = NULL;
    }
    if(sys->params != NULL)
    {
        free(sys->params);
        sys->params = NULL;
    }
}
