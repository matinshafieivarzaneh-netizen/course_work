#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
typedef struct{
    float timestamp;
    float phaseA;
    float phaseB;
    float phaseC;
    float line_current;
    float frequency;
    float power_factor;
    float thd_percent;
} pql_data;
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
double meanA = sum_squaredA / 1000.0;
    double meanB = sum_squaredB / 1000.0;
    double meanC = sum_squaredC / 1000.0;
    double rmsA = sqrt(meanA);
    double rmsB = sqrt(meanB);
    double rmsC = sqrt(meanC);
        printf("RMS volt A; %f \nRMS volt B; %f \nRMS volt C; %f \n", rmsA, rmsB, rmsC);




        return 0;

}