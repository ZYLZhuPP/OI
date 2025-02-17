#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e6 + 5;

template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

ll n, ans, res, s, a[N], cnt[N];

int main() {
    io >> n;
    for (int i = 1; i <= n; i++) {
        io >> a[i];
        cnt[(i - a[i] + n) % n]++;
        if (i - a[i] < 0) s++;
        ans += abs(a[i] - i);
    }

    res = ans;
    s += cnt[0] - 1;
    for (int i = 1; i < n; i++) {
        res = res - (a[i] - 1) + (n - a[i]) + 2 * s - n + 1;
        s += cnt[i] - 1;
        chkmin(ans, res);
    }

    printf("%lld", ans);

    return 0;
}
