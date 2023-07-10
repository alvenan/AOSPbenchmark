#ifndef __RSASEC_H__
#define __RSASEC_H__

#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <type_traits>

using namespace std;

void primefiller();
int pickrandomprime();
void setkeys();
long long int encrypt(double message);
long long int decrypt(int encrpyted_text);
vector<int> encoder(string message);
string decoder(vector<int> encoded);

#endif