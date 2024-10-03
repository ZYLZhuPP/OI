#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int n, a[N], c[N], s[N];
ll ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], c[a[i]]++;
    rFor (i, n - 1, 1) s[i] = s[i + 1] + c[i + 1];
    For (i, 1, n) {
        int x = query(n - a[i]);
        ans += min(x, s[a[i]] - x);
        upd(n - a[i] + 1, 1);
    }
    printf("%lld", ans);

    return 0;
}
