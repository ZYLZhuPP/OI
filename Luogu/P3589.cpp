#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;
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

int n, a, b, p, m, ans;
char s[N];
vector<array<int, 2 > > no;

int main() {
    io >> n >> a >> b >> p >> m;
    scanf("%s", s);
    For (i, 0, m - 1) {
        int x = 1ll * i * a % n, l, r;
        if (s[i] & 1) l = n - x, r = (n + p - x - 1) % n;
        else l = (n + p - x) % n, r = n - x - 1;
        if (l <= r) no.pb({l, r});
        else no.pb({0, r}), no.pb({l, n - 1});
    }
    For (i, n - m + 1, n - 1) {
        int x = (1ll * i * a + b) % n;
        no.pb({x, x});
    }
    sort(no.begin(), no.end());
    int l = 0, r = -1; ans = n;
    for (auto &[x, y] : no) if (x > r) ans -= r - l + 1, l = x, r = y; else cmax(r, y);
    ans -= r - l + 1;
    printf("%d", ans);

    return 0;
}
