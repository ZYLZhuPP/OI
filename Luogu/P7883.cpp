#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef pair<int, int > P;
const int N = 4e5 + 5;
const ll INF = 1e18;

struct IO {
    static const int BufS = 1 << 20;
    char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n;
P a[N], b[N];

inline ll dist(const P &a, const P &b) { return 1ll * (a.st - b.st) * (a.st - b.st) + 1ll * (a.nd - b.nd) * (a.nd - b.nd); }

inline ll solve(int l, int r) {
    if (l == r) return INF;
    int m = (l + r) >> 1;
    ll d1 = solve(l, m), d2 = solve(m + 1, r), D = min(d1, d2);
    int d = sqrt(D);
    int t = 0;
    For (i, l, r) if (abs(a[i].st - a[m].st) <= d) b[++t] = a[i];
    sort(b + 1, b + t + 1, [](P a, P b) { return a.nd < b.nd; });
    For (i, 1, t - 1) For (j, i + 1, t)
        if (b[j].nd - b[i].nd <= d) D = min(D, dist(b[i], b[j])); else break;
    return D;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i].st >> a[i].nd;
    sort(a + 1, a + n + 1);
    printf("%lld", solve(1, n));

    return 0;
}