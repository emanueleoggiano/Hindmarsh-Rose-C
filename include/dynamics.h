#ifndef DYNAMICS_H_INCLUDED
#define DYNAMICS_H_INCLUDED

#define SYS_DIM 3
#define FXD_PARAM 7

struct model {
    double state[SYS_DIM];
    double params[FXD_PARAMS];
    double neuron_current;
};



#endif // DYNAMICS_H_INCLUDED
