/**
 * Author: Lukas Derner Grüdtner
 **/

#include "../include/time.h"

double time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)(tv.tv_sec) + (double)(tv.tv_usec)/ 1000000.00;
}

double elapsed(double t1, double t2)
{
    return (double)(t2-t1)*1000;
}