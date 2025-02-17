#pragma GCC optimize("Ofast,inline,unroll-loops")
#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

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

int T, n, ans;
char s[N];
bitset<N > b, s0, s1, S0[N], S1[N];

inline void solve() {
    scanf("%s", s); n = strlen(s);
    s0 = 0, s1 = 0, ans = 0;
    For (i, 0, n - 1) s0[i] = s[i] != '0', s1[i] = s[i] == '1';
    S0[0] = s0, S1[0] = s1;
    For (i, 1, n - 1)
        s0 <<= 1, s0[0] = s0[n], s0[n] = 0, S0[i] = s0,
        s1 <<= 1, s1[0] = s1[n], s1[n] = 0, S1[i] = s1;
    For (i, 0, n) {
        int x = n / __gcd(n, i);
        b = 0; For (j, 0, i - 1) b[j * n / i] = 1;
        For (j, 0, x - 1) ans += (b | S0[j]) == S0[j] && (b & S1[j]) == S1[j];
    }
    printf("%d\n", ans);
}

int main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    io >> T;
    while (T--) solve();

    fclose(stdin); fclose(stdout);
    return 0;
}