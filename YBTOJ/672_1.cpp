#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

struct IO {
    int c, f;
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

int n;
double l1[N], l2[N], ans, p;

int main() {
    io >> n;
    For (i, 1, n) {
        scanf("%lf", &p);
        l1[i] = p * (l1[i - 1] + 1.l);
        l2[i] = p * (l2[i - 1] + 2.l * l1[i - 1] + 1.l);
        ans = ans + p * (3.l * l2[i - 1] + 3.l * l1[i - 1] + 1.l);
    }
    printf("%.1lf", ans);

    return 0;
}
