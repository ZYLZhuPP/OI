#include<bits/stdc++.h>
using namespace std;

int main() {
    float f = 2;
    int i = * (int *) &f;
    i = 0x5F3759DF - (i >> 1);
    float a = * (float *) &i;
    cout << a * a;
    return 0;
}
