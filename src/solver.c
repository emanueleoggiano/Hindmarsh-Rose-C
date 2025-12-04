#include "solver.h"

/**********************************************************/
/*                    MEMORY MANAGMENT                    */
/**********************************************************/

/*
*    Allocate the memory needed to initialize the solver.
*    Return NULL if the creation of the solver failed
*    Return SOLVER_DIM_ERR if dimension is <= 0
*    Return SOLVER_MEM_ERR if allocation failed
*/
struct RK4Solver* InitializeSolver(const short dim, short *ErrorMsg) {
    
    if(dim <= 0) {
        if(ErrorMsg != NULL) *ErrorMsg = SOLVER_DIM_ERR;
        return NULL;
    }

    struct Rk4Solver *solver = (RK4Solver*) malloc(sizeof(RK4Solver));

    if(solver == NULL) {
        if(ErrorMsg != NULL) *ErrorMsg = SOLVER_MEM_ERR;
        return NULL;
    }

    if(dim <= 0) {
        if(ErrorMsg != NULL) *ErrorMsg = SOLVER_DIM_ERR;
        return NULL;
    }

    solver->dimension = dim;
    
    // Setting everything to NULL before calling malloc
    solver->k1 = NULL; solver->k2 = NULL;
    solver->k3 = NULL; solver->k4 = NULL;
    solver->stateBuffer = NULL;

    // Allocation of the memory
    solver->k1 = (double*) malloc(dim*sizeof(double));
    solver->k2 = (double*) malloc(dim*sizeof(double));
    solver->k3 = (double*) malloc(dim*sizeof(double));
    solver->k4 = (double*) malloc(dim*sizeof(double));
    solver->stateBuffer = (double*) malloc(dim*sizeof(double));

    if(!solver->k1 || !solver->k2 || !solver->k3 || !solver->k4 ||
        !solver->stateBuffer) {
        
        FreeSolver(solver);

        if(ErrorMsg != NULL) *ErrorMsg = SOLVER_MEM_ERR;
        return NULL;
    }

    // Everything is ok
    if(ErrorMsg != NULL) *ErrorMsg = SOLVER_OK;
    return solver;
}

/*
*    Free the allocated memory
*/
void FreeSolver(struct RK4Solver *solver) {

    if(solver == NULL) return;

    if(solver->k1 != NULL) {
        free(solver->k1);
        solver->k1 = NULL;
    }

    if(solver->k2 != NULL) {
        free(solver->k2);
        solver->k2 = NULL;
    }

    if(solver->k3 != NULL) {
        free(solver->k3);
        solver->k3 = NULL;
    }

    if(solver->k4 != NULL) {
        free(solver->k4);
        solver->k4 = NULL;
    }

    if(solver->stateBuffer != NULL) {
        free(solver->stateBuffer);
        solver->stateBuffer = NULL;
    }

    free(solver);
}

/**********************************************************/
/*                      RK4 ALGORITHM                     */
/**********************************************************/

/*
*    Excecute the Runge-Kutta fourth order algoritm
*    for a single time step dt
*/
short RK4Step(struct system *sys, struct RK4Solver *solver, double dt,
              void (*SystemFunction)(struct system*, double*)) {

    if(!sys || !solver || !SystemFunction) {
        return RK4_NULL;
    }

    /*
    * Check if the dimension of the system is equal
    * to the dimension of the solver
    */
    if(sys->dimension != solver->dimension) {
        return RK4_DIM_ERR;
    }

    const short dim = sys->dimension;
    double *state = sys->state;
    double *buffer = solver->stateBuffer;

    // Save the state (y_n) because it has to be modified
    for(unsigned short i = 0; i < dim; i++)
        buffer[i] = state[i];

    // Calculation of k1
    SystemFunction(sys, solver->k1);

    // Calculation of k2
    
    sys->time += 0.5*dt; // Time update (t + dt/2)

    for(unsigned short i = 0; i < dim; i++)
        state[i] = buffer[i] + 0.5 * dt * solver->k1[i];
        
    SystemFunction(sys, solver->k2);

    // Calculation of k3
    for(unsigned short i = 0; i < dim; i++)
        state[i] = buffer[i] + 0.5 * dt * solver->k2[i];

    SystemFunction(sys, solver->k3);
    
    // Calculation of k4
    
    sys->time += 0.5*dt; // Time update (t + dt)
    
    for(unsigned short i = 0; i < dim; i++)
        state[i] = buffer[i] + dt *solver->k3[i];

    SystemFunction(sys, solver->k4);

    // State update
    for(unsigned short i = 0; i < dim; i++) {
        state[i] = buffer[i] + (dt/6)*(solver->k1[i] + 2*solver->k2[i] +
                                       2*solver->k3[i] + solver->k4[i]);
    }

    return RK4_OK;
}
