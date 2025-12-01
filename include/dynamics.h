#ifndef DYNAMICS_H_INCLUDED
#define DYNAMICS_H_INCLUDED


struct system {
    double *state; // State of the system (x, y, z, ...)
    double *params; // Parameters of the system
    unsigned short dimension; // Dimension of the system
    double time;
};





#endif // DYNAMICS_H_INCLUDED
