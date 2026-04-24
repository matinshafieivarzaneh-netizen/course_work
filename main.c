
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "waveform.h"


int main(void) {
    //reading file .csv
    FILE *pql = fopen("power_quality_log.csv", "r");
    if (pql == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    int num_samples = 1000;
    pql_data *data = malloc(sizeof(pql_data)*num_samples);
    int read = 0;
    int line = 0;
    char buffer[200];


    fgets(buffer, sizeof(buffer), pql);
    do {
        read = fscanf(pql,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
            &data[line].timestamp,
            &data[line].phaseA,
            &data[line].phaseB,
            &data[line].phaseC,
            &data[line].line_current,
            &data[line].frequency,
            &data[line].power_factor,
            &data[line].thd_percent);
        printf(" number: %d, voltage: %lf \n",line,data[line].phaseA);
        if (read == 8 ) {
            line++;
        }
        if (read != 8 && feof(pql)) {
            break;
        }
        if ( ferror( pql) )
        {
            printf("Error reading from file\n");
            free(data);
            return 1;
        }

    }while (line < num_samples);
fclose(pql);



// calculating rms
    double sum_squaredA = 0.0;
    double sum_squaredB = 0.0;
    double sum_squaredC = 0.0;


    for (int i = 0; i <= 999; ++i) {
        sum_squaredA += data[i].phaseA * data[i].phaseA;
        sum_squaredB += data[i].phaseB * data[i].phaseB;
        sum_squaredC += data[i].phaseC * data[i].phaseC;
    }
    double rmsA = sqrt(sum_squaredC/num_samples);
    double rmsB = sqrt(sum_squaredB/num_samples);
    double rmsC = sqrt(sum_squaredC/num_samples);
    printf("RMS volt A; %f \nRMS volt B; %f \nRMS volt C; %f \n", rmsA, rmsB, rmsC);
    //checking for tolerance
    if (rmsA <= 207) {
        printf("rmsA is too small\n");
    }
    if (rmsB <= 207) {
        printf("rmsB is too small\n");
    }
    if (rmsC <= 207) {
        printf("rmsC is too small\n");
    }
    if (253 <= rmsA) {
        printf("rmsA is too too big\n");
    }
    if (253 <= rmsB) {
        printf("rmsB is too big\n");
    }
    if (253 <= rmsC) {
        printf("rmsC is too big\n");
    }
    //calculating peak voltage
    double voltage_pA = rmsA * 1.4142;
    double voltage_pB = rmsB * 1.4142;
    double voltage_pC = rmsC * 1.4142;
    printf(" peak voltage A: %lf \n peak voltage B: %lf \n peak voltage C: %lf \n", voltage_pA, voltage_pB, voltage_pC);
    //calculating peak to peak values
    double pp_valueA = voltage_pA *2;
    double pp_valueB = voltage_pB *2;
    double pp_valueC = voltage_pC *2;
    printf(" peak to peak value A: %lf \n peak to peak value B: %lf \n peak to peak value C: %lf \n", pp_valueA, pp_valueB, pp_valueC);








free(data);
    return 0;
    }







