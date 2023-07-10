#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <cstdio> 
#include "qsort/qsort.h"
#include "dijkstra/dijkstra.h"
#include "pffft/test_pffft.h"
#include "rsasec/rsasec.h"

void qsortExec(char* input_path, int arr_size);
void dijkstraExec(char* input_path, int graph_size);
void fftExec(int N);
void rsaExec(char* input_path);

#endif