#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int T, n, ans, val[256];
short c[2187][2187];
char s[N], mp[3];

inline void init() {
    c[0][0] = 1;
    For (i, 1, 2186) c[i][0] = 1;
    For (i, 1, 2186) For (j, 1, i) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % 3;
    val[mp[0] = 'R'] = 0; val[mp[1] = 'Y'] = 1; val[mp[2] = 'B'] = 2;
}

inline short C(int n, int m) {
    if (n < 2187) return c[n][m];
    return c[n % 2187][m % 2187] * C(n / 2187, m / 2187) % 3;
}

int main() {
    init();
    io >> T;
    while (T--) {
        ans = 0;
        io >> n; n--;
        scanf("%s", s);
        For (i, 0, n) ans += val[s[i]] * C(n, i);
        if (n & 1) ans *= 2;
        ans %= 3;
        putchar(mp[ans]); putchar('\n');
    }

    return 0;
}