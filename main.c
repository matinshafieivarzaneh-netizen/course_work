
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "waveform.h"

int main(void) {
    FILE *pql = fopen("power_quality_log.csv", "r");

    if (pql == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    pql_data data[1000];
    int read = 0;
    int line = 0;
    char buffer[106];


    fgets(buffer, sizeof(buffer), pql);
    do
    {
        read = fscanf(pql,"%f,%f,%f,%f,%f,%f,%f,%f\n",
            &data[line].timestamp,
            &data[line].phaseA,
            &data[line].phaseB,
            &data[line].phaseC,
            &data[line].line_current,
            &data[line].frequency,
            &data[line].power_factor,
            &data[line].thd_percent);
        printf(" number: %d, voltage: %f \n",line,data[line].phaseA);
        if (read == 8 )++line;
        if (read != 8 && feof(pql)) {
            break;
        }
        if ( ferror( pql) )
        {
            printf("Error reading from file\n");
            return 1;
        }
    }while (line <= 1000);
fclose(pql);




    double sum_squaredA = 0.0;
    double sum_squaredB = 0.0;
    double sum_squaredC = 0.0;


    for (int i = 0; i <= 999; ++i) {
        sum_squaredA += data[i].phaseA * data[i].phaseA;
        sum_squaredB += data[i].phaseB * data[i].phaseB;
        sum_squaredC += data[i].phaseC * data[i].phaseC;
    }
    double rmsA = rms(1000, sum_squaredA);
    double rmsB = rms(1000, sum_squaredB);
    double rmsC = rms(1000, sum_squaredC);
    printf("RMS volt A; %f \nRMS volt B; %f \nRMS volt C; %f \n", rmsA, rmsB, rmsC);
    rmsA = 200;
    rmsB = 200;
    rmsC = 300;
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




    return 0;
    }







