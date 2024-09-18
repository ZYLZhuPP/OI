#include<bits/stdc++.h>
using namespace std;

#define pb push_back
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

int n, m, a[N], lst[N], sum, ans[N];
vector<pair<int, int > > qs[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x <= n; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int main()  {
    io >> n;
    For (i, 1, n) io >> a[i];
    io >> m;
    int l, r;
    For (i, 1, m) io >> l >> r, qs[r].pb({l, i});
    For (i, 1, n) {
        int x = a[i];
        if (lst[x]) upd(lst[x], -1);
        else sum++;
        upd(lst[x] = i, 1);
        for (auto &[l, id] : qs[i]) ans[id] = sum - query(l - 1);
    }
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
