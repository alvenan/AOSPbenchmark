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

void fftExec(int N) {
    pffft_validate_N(N, 0);
}

void rsaExec(char* input_path) {
    ifstream input_file(input_path);
    string message((istreambuf_iterator<char>(input_file)),istreambuf_iterator<char>());

    primefiller();
    setkeys();
    // cout<<"enter the message\n";getline(cin,message);
    // calling the encoding function
    vector<int> coded = encoder(message);
    // cout << "Initial message:\n" << message;
    // cout << "\n\nThe encoded message(encrypted by public "
            // "key)\n";
    // for (auto& p : coded)
    // cout << p;
    // cout << "\n\nThe decoded message(decrypted by private "
            // "key)\n";
    // cout << decoder(coded) << endl;
    decoder(coded);
}