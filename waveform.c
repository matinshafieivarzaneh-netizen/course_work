#include <math.h>
#include "io.h"
#include "waveform.h"

double calculate_rmsA(pql_data data[]) {
    double sum_squaredA;
    for (int i = 0; i <= 999; ++i) {
        sum_squaredA += data[i].phaseA * data[i].phaseA;

}
    double root_mean_squard_A = sum_squaredA / 1000;
    return root_mean_squard_A;
}



double calculate_rmsB(pql_data data[]) {
    double sum_squaredB;
    for (int i = 0; i <= 999; ++i) {
        sum_squaredB += data[i].phaseB * data[i].phaseB;
    }
    double root_mean_squared_B = sum_squaredB / 1000;
    return root_mean_squared_B;
}
double calculate_rmsC(pql_data data[]) {
    double sum_squaredC;
    for (int i = 0; i <= 999; ++i) {
        sum_squaredC += data[i].phaseC * data[i].phaseC;
    }
    double root_mean_squared_C = sum_squaredC / 1000;
    return root_mean_squared_C;
}

//
// Created by matin on 23/04/2026.
//

