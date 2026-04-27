
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "waveform.h"
#include "io.h"


int main(void) {
    char file_name[256];
    printf("please enter file name: ");
    scanf(" %s",&file_name);

    pql_data *data = processing_csv(file_name);


//reading file
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
    int num_samples = 1000;
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
    fprintf(output," peak voltage A: %.3lf \n peak voltage B: %.3lf \n peak voltage C: %.3lf \n", voltage_pA, voltage_pB, voltage_pC);
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
    fprintf(output," peak to peak value A: %.3lf \n peak to peak value B: %.3lf \n peak to peak value C: %.3lf \n", pp_valueA, pp_valueB, pp_valueC);

    fprintf(output,"DC offsetA: %.3lf \nDC offsetB: %.3lf \nDC offsetC: %.3lf \n", DC_offsetA, DC_offsetB, DC_offsetC);
    // detecting clipping in phase A
    for (int i = 0; i <= 999; ++i) {
        if (fabs(data[i].phaseA) >= 324.9) {
            fprintf(output,"detected clipping at t = %.3lf s in phase A \n", data[i].timestamp);
        }
    }
    fprintf(output,"\n\n\n");
    //detecting clipping in phase B
    for (int i = 0; i <= 999; ++i) {
        if (fabs(data[i].phaseB) >= 324.9) {
            fprintf(output,"detected clipping at t = %.3lf ms in phase B \n", data[i].timestamp);
        }
    }
    fprintf(output,"\n\n\n");
    //detecting clipping in phase C
    for (int i = 0; i <= 999; ++i) {
        if (fabs(data[i].phaseC) >= 324.9) {
            fprintf(output,"detected clipping at t = %.3lf ms in phase C \n", data[i].timestamp);
        }
    }






free(data);
    return 0;
    }









