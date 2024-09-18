#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, K, q[N], t;

int main() {
    io >> n >> K;
    For (i, 1, n) {
        char c;
        while (!isdigit(c = gc()));
        int x = c ^ 48;
        q[++t] = x;
        while (t > 1 && K && q[t] > q[t - 1]) q[t - 1] = q[t], t--, K--;
    }
    For (i, 1, t) putchar(q[i] ^ 48);

    return 0;
}