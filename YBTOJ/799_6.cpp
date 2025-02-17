#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5, Mo = 10086;

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

int n, ans = 1;

struct Basis {
    static const int B = 31;
    int o[B]; bool zero;
    Basis() { memset(o, 0, sizeof o); zero = 1; }
    bool ins(int x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            else x ^= o[i];
        }
        return zero = 1, 0;
    }
    int rnk(int x) {
        int res = zero, y = 1;
        For (i, 0, B - 1) if (o[i]) {
            if (x >> i & 1) res += y;
            y <<= 1;
        }
        return res;
    }
} B;

int main() {
    io >> n;
    int x;
    For (i, 1, n) {
        io >> x;
        if (!B.ins(x)) ans = ans * 2 % Mo;
    }
    io >> x;
    printf("%d", ((B.rnk(x) - 1) % Mo * ans + 1) % Mo);

    return 0;
}
