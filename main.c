
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io.h"
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

FILE *output = fopen("result.txt", "w");
if (output == NULL) {
    printf("Error writing file\n");
    free(data);
    return 1;
}
// calculating rms
    double sum_squaredA = 0.0;
    double sum_squaredB = 0.0;
    double sum_squaredC = 0.0;


    for (int i = 0; i <= 999; ++i) {
        sum_squaredA += data[i].phaseA * data[i].phaseA;
        sum_squaredB += data[i].phaseB * data[i].phaseB;
        sum_squaredC += data[i].phaseC * data[i].phaseC;
    }
    double rmsA = sqrt(sum_squaredA/num_samples);
    double rmsB = sqrt(sum_squaredB/num_samples);
    double rmsC = sqrt(sum_squaredC/num_samples);
    fprintf(output,"RMS volt A; %f \nRMS volt B; %f \nRMS volt C; %f \n", rmsA, rmsB, rmsC);
    //checking for tolerance
    if (rmsA <= 207) {
        fprintf(output,"rmsA is too small\n");
    }
    if (rmsB <= 207) {
        fprintf(output,"rmsB is too small\n");
    }
    if (rmsC <= 207) {
        fprintf(output,"rmsC is too small\n");
    }
    if (253 <= rmsA) {
        fprintf(output,"rmsA is too too big\n");
    }
    if (253 <= rmsB) {
        fprintf(output,"rmsB is too big\n");
    }
    if (253 <= rmsC) {
        fprintf(output,"rmsC is too big\n");
    }
    //calculating peak voltage
    double voltage_pA = rmsA * 1.4142;
    double voltage_pB = rmsB * 1.4142;
    double voltage_pC = rmsC * 1.4142;
    fprintf(output," peak voltage A: %lf \n peak voltage B: %lf \n peak voltage C: %lf \n", voltage_pA, voltage_pB, voltage_pC);
     //calculating dc offset
    double sumA = 0.0;
    double sumB = 0.0;
    double sumC = 0.0;


    for (int i = 0; i <= 999; ++i) {
        sumA += data[i].phaseA ;
        sumB += data[i].phaseB ;
        sumC += data[i].phaseC ;
    }
    double DC_offsetA = sumA / num_samples;
    double DC_offsetB = sumB / num_samples;
    double DC_offsetC = sumC / num_samples;
    //calculating peak to peak values
    double pp_valueA = (voltage_pA - DC_offsetA)*2;
    double pp_valueB = (voltage_pB - DC_offsetB)*2;
    double pp_valueC = (voltage_pC - DC_offsetC) *2;
    fprintf(output," peak to peak value A: %lf \n peak to peak value B: %lf \n peak to peak value C: %lf \n", pp_valueA, pp_valueB, pp_valueC);

    fprintf(output,"DC offsetA: %lf \nDC offsetB: %lf \nDC offsetC: %lf \n", DC_offsetA, DC_offsetB, DC_offsetC);
    // detecting clipping in phase A
    for (int i = 0; i <= 999; ++i) {
        if (sqrt(data[i].phaseA *data[i].phaseA) >= 324.9) {
            fprintf(output,"detected clipping at t = %lf ms in phase A \n", data[i].timestamp);
        }
    }
    fprintf(output,"\n\n\n");
    //detecting clipping in phase B
    for (int i = 0; i <= 999; ++i) {
        if (sqrt(data[i].phaseB *data[i].phaseB) >= 324.9) {
            fprintf(output,"detected clipping at t = %lf ms in phase B \n", data[i].timestamp);
        }
    }
    fprintf(output,"\n\n\n");
    //detecting clipping in phase C
    for (int i = 0; i <= 999; ++i) {
        if (sqrt(data[i].phaseC *data[i].phaseC) >= 324.9) {
            fprintf(output,"detected clipping at t = %lf ms in phase C \n", data[i].timestamp);
        }
    }






free(data);
    return 0;
    }







