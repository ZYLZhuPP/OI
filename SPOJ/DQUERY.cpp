#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, S, a[N], s[N], ans[N];

struct Node {
    int l, r, bl, id;
    bool operator < (const Node &a) const { return bl^a.bl? bl<a.bl: r<a.r; }
} q[N];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    S = sqrt(n);
    io >> m;
    For (i, 1, m) {
        int l, r;
        io >> l >> r;
        q[i] = Node{l, r, l / S, i};
    }
    sort(q + 1, q + m + 1);
    int l = 1, r = 0, res = 0;
    For (i, 1, m) {
        int L = q[i].l, R = q[i].r;
        while (l > L) if (!s[a[--l]]++) ++res;
        while (r < R) if (!s[a[++r]]++) ++res;
        while (l < L) if (!--s[a[l++]]) --res;
        while (r > R) if (!--s[a[r--]]) --res;
        ans[q[i].id] = res;
    }
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
//Luogu SP3267
