#include <math.h>
#include "waveform.h"

//
// Created by matin on 23/04/2026.
//
double my_rms( int n, double sum) {
    double result;
   result = sqrt((sum * sum))/n;
    return result;
}