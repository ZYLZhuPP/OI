#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e7 + 5;

struct IO {
    char c; int f;
#define gc() (getchar())
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~() {return ~c;}
} io;

int toc[N], tod[N];
int M, T, C, D, rC, rD, G, m, c, d, p;
ll A, B, n, dx, ans, L, R, r[N];

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> A >> B >> C >> D; A %= C; B %= D;
        if (!A && !B) { printf("%lld\n", n); continue; }
        if (!A || !B) { puts("0"); continue; }
        M = 1;
        For (i, 1, C - 1) {
            M = 1ll * M * A % C, toc[M] = i;
            if (M == 1) {rC = i; break;}
        }
        M = 1;
        For (i, 1, D - 1) {
            M = 1ll * M * B % D, tod[M] = i;
            if (M == 1) {rD = i; break;}
        }
        G = __gcd(rC, rD);
        L = 1ll * rC * rD / G;
        R = n % L;
        for (register ll i = 0; i < L; i += rD) r[i % rC] = i;
        m = max(C, D);
        For (i, 1, m - 1) {
            c = toc[i], d = tod[i]; toc[i] = tod[i] = 0;
            if (!c || !d) continue;
            if ((c - d) % G) continue;
            p = (c - d) % rC;
            if (p < 0) p += rC;
            ans += n / L + (d + r[p] <= R);
        }
        printf("%lld\n", ans);
    }

    return 0;
}
