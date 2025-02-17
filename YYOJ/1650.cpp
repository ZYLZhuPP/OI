#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, V = N * (__lg(N) + 1) + 5;

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
    inline bool operator ~() {return ~c;}
} io;

int n, a[N], pos[N];
ll ans;

namespace tr {
    struct Node { int l, r, s; };
    Node v[V]; int rt[N], tot;
    void upd(int &p, int l, int r, int x) {
        v[++tot] = v[p], ++v[p = tot].s;
        if (l == r) return;
        int m = (l + r) >> 1;
        x <= m? upd(v[p].l, l, m, x): upd(v[p].r, m + 1, r, x);
    }
    int kth(int p, int q, int l, int r, int k) {
        if (l == r) return l;
        int s = v[v[q].l].s - v[v[p].l].s, m = (l + r) >> 1;
        return k <= s? kth(v[p].l, v[q].l, l, m, k): kth(v[p].r, v[q].r, m + 1, r, k - s);
    }
    void add(int k, int x) { upd(rt[k] = rt[k - 1], 1, n, x); }
    int kth(int L, int R, int k) { return kth(rt[L - 1], rt[R], 1, n, k); }
}

void solve(int L, int R) {
    if (L >= R) return;
    ans += R - L + 1;
    int x = a[tr::kth(L, R, (R - L + 2) / 2)];
    solve(L, x - 1); solve(x + 1, R);
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], pos[a[i]] = i;
    For (i, 1, n) tr::add(i, pos[i]);
    solve(1, n);
    
    printf("%lld", ans);
    
    return 0;
} 
