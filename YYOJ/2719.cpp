#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, a[N], ans;
char s[N];

namespace BIT {
    int o1[N], o2[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int o[], int x, int v) { for (; x <= n; x += lowbit(x)) cmax(o[x], v); }
    inline int query(int o[], int x) { int r = 0; for (; x; x -= lowbit(x)) cmax(r, o[x]); return r; }
}
using namespace BIT;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    scanf("%s", s + 1);
    For (i, 1, n) {
        int x = max(query(o1, a[i] - 1), query(o2, n - a[i]));
        cmax(ans, x);
        if (s[x + 1] == 'U') upd(o1, a[i], x + 1); else upd(o2, n - a[i] + 1, x + 1);
    }
    printf("%d", ans);
    
    return 0;
}
