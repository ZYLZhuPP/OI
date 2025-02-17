#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, ans, cnt[N];
vector<int > pos[N], b[N];

inline void get(int x, int k) {
    int p = 0, mn = n + 1;
    ans -= cnt[x]; cnt[x] = 0;
    while (p < (int)pos[x].size()) {
        int np = upper_bound(pos[x].begin() + p, pos[x].end(), pos[x][p] + k) - pos[x].begin();
        if (np < (int)pos[x].size()) cmin(mn, pos[x][np] - pos[x][p]);
        cnt[x]++; ans++; p = np;
    }
    if (mn <= n) b[mn].emplace_back(x);
}

int main() {
    io >> n;
    int x;
    For (i, 1, n) io >> x, pos[x].pb(i);
    For (i, 1, n) if (pos[i].size()) {
        if ((int)pos[i].size() == 1) ans++;
        else b[1].pb(i);
    }
    For (i, 1, n) {
        for (auto &x : b[i]) get(x, i);
        printf("%d\n", ans);
    }

    return 0;
}