#include "io.h"

#include <stdio.h>

//
// Created by matin on 24/04/2026.
//
pql_data *processing_csv(char file_name[256]) {

    //reading file .csv
    FILE *pql = fopen(file_name, "r");
    if (pql == NULL) {
        printf("Error opening file\n");
        return NULL;
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
            return NULL;
        }

    }while (line < num_samples);
    fclose(pql);
    
    return data;


    }




