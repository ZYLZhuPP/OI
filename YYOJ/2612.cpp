#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 505, M = 1.2e7 + 5;

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

int n, m, s[N], b[N * N], cnt[M << 1], Cnt[M << 1];
ll ans;

int main() {
    io >> n;
    int x;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;
    For (i, 1, n) For (j, i, n) b[++m] = s[j] - s[i - 1];
    For (i, 1, n) {
        int x = M - s[i - 1];
        For (j, 1, m) cnt[b[j] + x]++;
        x = M - s[i];
        For (j, 1, m) ans += cnt[x - b[j]];
    }
    For (i, 1, m) Cnt[M + 2 * b[i]]++;
    For (i, 1, m) ans -= 3 * Cnt[M - b[i]];
    For (i, 1, m) if (!b[i]) ans += 2;
    printf("%lld", ans / 6);

    return 0;
}
