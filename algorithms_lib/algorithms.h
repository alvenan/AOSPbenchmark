#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "qsort/qsort.h"
#include "dijkstra/dijkstra.h"
#include "pffft/test_pffft.h"

void qsortExec(char* input_path, int arr_size);
void dijkstraExec(char* input_path, int graph_size);
void fftExec(int N, int cplx);

extern "C" {
    void pffft_validate_N(int N, int cplx);
}

#endif