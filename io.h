//
// Created by matin on 24/04/2026.
//



#include <stdio.h>
#include <stdlib.h>
#ifndef COURSE_WORK_IO_H
#define COURSE_WORK_IO_H
#ifndef io_h
#define io_h
typedef struct{
    double timestamp;
    double phaseA;
    double phaseB;
    double phaseC;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} pql_data;

pql_data *processing_csv(char file_name[256]);

#endif






#endif //COURSE_WORK_IO_H
