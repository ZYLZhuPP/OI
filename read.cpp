#include<bits/stdc++.h>
using namespace std;
const int Mo = 998244353;

inline void add(int &x, const int &y) { x -= (x+=y)>=Mo? Mo: 0; }
inline void dec(int &x, const int &y) { x += ((x-=y)>>31) & Mo; }

int main() {
    int x = 10, y = Mo - 5;
    add(x, y);
    cerr << x;

    return 0;
}