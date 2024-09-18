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

int n, m, a[N], b[N], ans;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    while (m--) {
        char op[3];
        scanf("%s", op);
        if (op[0] == 'Q') {
            ans = 0;
            int l, r;
            io >> l >> r;
            For (i, l, r) if (!b[a[i]]++) ans++;
            printf("%d\n", ans);
            For (i, l, r) b[a[i]] = 0;
        } else if (op[0] == 'R') {
            int x, v;
            io >> x >> v;
            a[x] = v;
        }
    }

    return 0;
}
