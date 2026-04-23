//
// Created by matin on 23/04/2026.
//

#ifndef COURSE_WORK_WAVEFORM_H
#define COURSE_WORK_WAVEFORM_H
#endif //COURSE_WORK_WAVEFORM_H


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

double rms( int n, double sum);





