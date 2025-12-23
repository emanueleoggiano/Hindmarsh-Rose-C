/******************************************************************************
MIT License

Copyright (c) 2025 Emanuele Oggiano

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/


#ifndef DYNAMICS_H_INCLUDED
#define DYNAMICS_H_INCLUDED

// System parameters
#define SYS_DIM 3
#define FXD_PARAM 7

// Error Codes
#define SYS_NULL_ERR -1
#define SYS_BAD_ALLOC -2

struct model {
    double state[SYS_DIM];
    double params[FXD_PARAMS];
    double neuron_current;
};


void InitializeSystem(struct model *hr);



#endif // DYNAMICS_H_INCLUDED
