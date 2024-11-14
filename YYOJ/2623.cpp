#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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
    inline bool operator ~ () const { return ~c; }
} io;

int P, K, n;

int main() {
    io >> P >> K; n = pow(P, K);
    printf("%d\n", n * (n - 1) / P / (P - 1));
    int x = 1, y = P;
    For (i, 1, K) {
        For (j, 0, n / y - 1) {
            For (d, 0, x - 1) {
                For (k, 0, x - 1) {
                    int p = k;
                    For (l, 0, P - 1) {
                        printf("%d ", j * y + l * x + p);
                        p = (p + d) % x;
                    }
                    puts("");
                }
            }
        }
        x *= P; y *= P;
    }

    return 0;
}
