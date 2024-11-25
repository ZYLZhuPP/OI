#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, a[N], b[N], c[N], cnt[N], s[N], k[N];
ll ans0, ans1;
array<int, 2 > op[N];
multiset<int > se[N];

inline ll calc(int o, int p, int b[]) {
    ll res = 0;
    For (i, 1, n) cnt[i] = cnt[i - 1] + ((i & 1) ^ p), s[i] = s[i - 1] + ((a[i] & 1) ^ o);
    For (i, 1, n) {
        if (i > 1 && s[i - 1] < cnt[i - 1]) k[i] = -1;
        else if (i < n && s[n] - s[i] < cnt[n] - cnt[i]) k[i] = 1;
        else k[i] = 2;
        op[i] = {k[i], i * k[i]};
    }
    sort(op + 1, op + n + 1);
    For (i, 1, n) {
        int k = op[i][0], x = op[i][1] / k;
        if ((a[x] & 1) ^ o) se[x].insert(a[x]);
        if ((x & 1) ^ p) {
            if (k == -1) b[x] = *se[x].rbegin(), se[x].erase(se[x].find(b[x]));
            else b[x] = *se[x].begin(), se[x].erase(se[x].find(b[x]));
        }
        if (k != 2) res += se[x].size(), swap(se[x], se[x + k]);
    }
    return res;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    ans0 = calc(0, 0, b) + calc(1, 1, b);
    ans1 = n&1? 1e9: (calc(0, 1, c) + calc(1, 0, c));
    For (i, 1, n) printf("%d ", ans0<ans1? b[i]: c[i]);

    return 0;
}
