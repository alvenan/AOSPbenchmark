#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

int minDistance(int dist[], bool sptSet[], int graph_size);
void printSolution(int dist[], int graph_size);
void dijkstra(int** graph, int src, int graph_size);

#endif