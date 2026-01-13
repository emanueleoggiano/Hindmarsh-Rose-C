

/*
The equations of the system are:

dx/dt = y - ax^3 + bx^2 - z + I

dy/dt = c - d*x^2 - y

dz/dt = r * (s * (x - x_R) - z)

*/


#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------------------------*/
/* Structs */

/* The model has 3 dynamical variables that are stored in state */
struct state {
    double x;
    double y;
    double z;
}

/* The model has X parameters */
struct params {
    double a, b, c, d;
    double r, s, x_R;
    double I;
}

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Fixed points analysis */

/* To find the fixed points of a dynamical system, we must check
   when all these conditions are satisfied: 
                             
                                   dx/dt = 0 
                                   dy/dt = 0
                                   dz/dt = 0

   Mathematically this means that we must study the zeros of the equation:
                         
                  -a*x^3 + (b - d)*x^2 - s*x + c + s*x_R + I = 0
*/

double polynomial_value(double x, struct params par) {
    double c_3 = - par.a;
    double c_2 = par.b - par.d;
    double c_1 = - par.s;
    double c_0 = par.c + (par.s*par.x_R) + par.I;

    return (c_3*x*x*x + c_2*x*x + c_1*x + c_0);
}

double polynomial_deriv(double x, struct params par) {
    double c_3 = - par.a;
    double c_2 = par.b - par.d;
    double c_1 = - par.s;

    return (3*c_3*x*x + 2*c_2*x + c_1);
}

#define NEWTON_MAX_ITER 1000
#define NEWTON_TOLERANCE 1e-8
double newton_method(struct params par, double guess) {
    double x = guess;

    double f = polynomial_value(x, par);
    double f_dot = polynomial_deriv(x, par);

    for(unsigned i = 0; i < NEWTON_MAX_ITER; i++) {

        if(fabs(f_dot) < 1e-9) return NAN;
        
        double x_new = x - (f/f_dot);
        if(fabs(x - x_new) < NEWTON_TOLERANCE) return x_new;
        
        x = x_new;
        f = polynomial_value(x, par);
        f_dot = polynomial_deriv(x, par);
    }

    return NAN;
}
/*---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------*/
/* Main */

int main(void) {
}
/*---------------------------------------------------------------------------*/
