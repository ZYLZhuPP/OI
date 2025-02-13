#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e4 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int T, n, Q, B, a[N];
ll s, ans[N];
vector<pair<int, int > > L[N], R[N];

struct Node {
    int l, r, id;
    bool operator < (const Node &a) { return l/B^a.l/B? l<a.l: r<a.r; }
};
vector<Node > qs;

inline int gcd(int a, int b) { return !b? a: gcd(b, a % b); }

inline ll queryL(int l, int r) {
    int j = l, x = a[l]; ll res = 0;
    for (auto &[i, y] : L[l])
        if (i > r) { res += 1ll * x * (r - j + 1); break; }
        else res += 1ll * x * (i - j), x = y, j = i;
    return res;
}

inline ll queryR(int l, int r) {
    int j = r, x = a[r]; ll res = 0;
    for (auto &[i, y] : R[r])
        if (i < l) { res += 1ll * x * (j - l + 1); break; }
        else res += 1ll * x * (j - i), x = y, j = i;
    return res;
}

int main() {
    io >> T;
    while (T--) {
        io >> n;
        B = sqrt(n);
        For (i, 1, n) io >> a[i];

        R[1].pb({1, a[1]});
        For (i, 2, n) {
            int x = a[i];
            R[i].pb({i, x});
            for (auto &[j, y] : R[i - 1]) if (a[j] % x) R[i].pb({j, x = gcd(x, a[j])});
        }
        L[n].pb({n, a[n]});
        rFor (i, n - 1, 1) {
            int x = a[i];
            L[i].pb({i, x});
            for (auto &[j, y] : L[i + 1]) if (a[j] % x) L[i].pb({j, x = gcd(x, a[j])});
        }
        For (i, 1, n) L[i].pb({n + 1, 0}), R[i].pb({0, 0});

        io >> Q;
        int l, r;
        For (i, 1, Q) io >> l >> r, qs.pb({l, r, i});
        sort(qs.begin(), qs.end());
        l = 1, r = 0, s = 0;
        for (auto &[x, y, id] : qs) {
            while (l > x) s += queryL(--l, r);
            while (r < y) s += queryR(l, ++r);
            while (l < x) s -= queryL(l++, r);
            while (r > y) s -= queryR(l, r--);
            ans[id] = s;
        }

        For (i, 1, Q) printf("%lld\n", ans[i]);
        For (i, 1, n) L[i].resize(0), R[i].resize(0);
        qs.resize(0);
    }

    return 0;
}
