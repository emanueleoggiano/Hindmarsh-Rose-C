#ifndef DYNAMICS_H_INCLUDED
#define DYNAMICS_H_INCLUDED


struct system {
    double *state; // State of the system (x, y, z, ...)
    double *params; // Parameters of the system
    unsigned short dimension; // Dimension of the system
    double time;
};

/**********************************************************/
/*                    MEMORY MANAGMENT                    */
/**********************************************************/

/*
*    Allocate the memory needed.
*    Return 0 if successful
*    Return -1 if dim or num_param is negative
*    Return -2 if allocation failed
*/
short InitializeSystem(struct system *sys, const short dim,
                       const short num_param);

/*
*    Free the allocated memory
*/
void FreeSystem(struct system *sys);




#endif // DYNAMICS_H_INCLUDED
