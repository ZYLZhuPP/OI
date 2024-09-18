#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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
ll f[N], ans, t[N], a[N], tr[N];
vector<int > ok[N];

inline int lowbit(int x) { return x & -x; }
void upd(int k, ll x) { for (; k <= n; k += lowbit(k)) tr[k] = max(tr[k], x); }
ll query(int k) {
    ll res = 0;
    for (; k; k -= lowbit(k)) res = max(res, tr[k]);
    return res;
}

int main() {
    io >> n;
    For (i, 1, n) io >> t[i];
    For (i, 1, n) io >> a[i];

    For (i, 1, n) {
        for (auto &u : ok[i]) upd(u, f[u]);
        f[i] = a[i] * t[i] + (i - t[i] <= 0? 0: query(i - t[i]));
        if (i + t[i] <= n) ok[i + t[i]].push_back(i);
        ans = max(ans, f[i]);
    }

    printf("%lld", ans);

    return 0;
}
