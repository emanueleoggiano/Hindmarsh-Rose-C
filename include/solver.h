#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

#include "dynamics.h"

struct RK4Solver
{
    // RK4 parameters
    double *k1;
    double *k2;
    double *k3;
    double *k4;
    
    unsigned short dimension;
    
    // Save the original state during calculation
    double *stateBuffer;
    
};

/**********************************************************/
/*                    MEMORY MANAGMENT                    */
/**********************************************************/

/*
*    Allocate the memory needed to initialize the solver.
*    Return 0 if successful
*    Return -1 if dim is negative
*    Return -2 if allocation failed
*/
struct RK4Solver* InitializeSolver(const short dim);

/*
*    Free the allocated memory
*/
void FreeSolver(struct RK4Solver *solver);

/**********************************************************/
/*                      RK4 ALGORITHM                     */
/**********************************************************/

/*
*    Excecute the Runge-Kutta fourth order algoritm
*    for a single time step
*/
void RK4Step(struct system *sys, struct RK4Solver *solver, double dt,
             double (*SystemFunction)(struct system*, double*));
