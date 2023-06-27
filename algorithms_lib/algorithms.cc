#include "algorithms.h"
#include <fstream>
#include <math.h>
#include <iostream>

using namespace std;

void qsortExec(char* input_path, int arr_size){
    ifstream input_file;
    int arr[arr_size];

    input_file.open(input_path);
    if(input_file.is_open()) {
        for (int i=0; i<arr_size; i++)
            input_file >> arr[i];
        input_file.close();
    }
    quickSort(arr, 0, arr_size-1);
}

void dijkstraExec(char* input_path, int graph_size){
    ifstream input_file;
    int** graph = new int*[graph_size];

    for(int i=0; i<graph_size; i++)
        graph[i] = new int[graph_size];

    input_file.open(input_path);
    if(input_file.is_open()) {
        for (int i=0; i<graph_size; i++)
            for (int j=0; j<graph_size; j++)
                input_file >> graph[i][j];
        input_file.close();
    }
    dijkstra(graph, 0, graph_size);
}

