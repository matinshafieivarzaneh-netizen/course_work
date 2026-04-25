#include "io.h"
#include "waveform.h"
#include <stdio.h>

//
// Created by matin on 24/04/2026.
//




//reading file .csv
void read_io(const float *file_name)
{
    FILE *pql = fopen("power_quality_log.csv", "r");
    if (pql == NULL) {
        printf("Error opening file\n");
        return ;
    }
    int num_samples = 1000;
    pql_data *data = malloc(sizeof(pql_data)*num_samples);
    int read = 0;
    int line = 0;
    char buffer[200];
    free(data);



    fclose(pql);
}