#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;
inline bool cmax(ll &x, const ll &y) { return x<y? x=y, 1: 0; }

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

int n, m, p, x;
ll a[N], s[N], f[N], f0[N], f1[N], f_[N];
int q[N];

namespace solve1 {
    inline ll dx(int i, int j) { return i - j; }
    inline ll Y(int i) { return f[max(0, i - 1)] + 1ll * i * (i - 1) / 2 + s[i]; }
    inline ll dy(int i, int j) { return Y(i) - Y(j); }
    inline ll F(int i, int j) { return f[max(0, j - 1)] + 1ll * (i - j) * (i - j + 1) / 2 - (s[i] - s[j]); }
    
    void slope() {
        memset(f, -31, sizeof f); f[0] = 0;
        int h = 1, t = 0; q[++t] = 0;
        For (i, 1, n) {
            ll k = i;
            while (h < t && dy(q[t], q[t - 1]) <= dx(q[t], q[t - 1]) * k) t--;
            f[i] = max(f[i - 1], F(i, q[t]));
            while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) >= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
            q[++t] = i;
        }
    }
    
    void main() {
        For (i, 1, n) s[i] = s[i - 1] + a[i];
        slope(); For (i, 1, n) f0[i] = f[i];
    
        For (i, 1, n) s[i] = s[i - 1] + a[n - i + 1];
        slope(); For (i, 1, n) f1[n - i + 1] = f[i];
    }
}

namespace solve2 {
    inline ll dx(int i, int j) { return i - j; }
    inline ll dy(int i, int j) { return f[i] - f[j]; }
    inline ll F1(int i, int j) { return f0[j - 1] + f1[i + 1] + 1ll * (i - j + 1) * (i - j + 2) / 2 - (s[i] - s[j - 1]); }
    inline ll F2(int i, int j) { return f0[i - 1] + f1[j + 1] + 1ll * (j - i + 1) * (j - i + 2) / 2 - (s[j] - s[i - 1]); }

    void solve(int l, int r) {
        if (l == r) return void(cmax(f_[l], 1 - a[l]));

        int m = (l + r) >> 1;
        
        ll ma = LLONG_MIN;
        int h = 1, t = 0;
        For (i, l, m) {
            f[i] = f0[i - 1] + 1ll * (i - 1) * (i - 2) / 2 + s[i - 1];
            while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) >= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
            q[++t] = i;
        }
        rFor (i, r, m + 1) {
            ll k = i;
            while (h < t && dy(q[h + 1], q[h]) >= dx(q[h + 1], q[h]) * k) h++;
            cmax(ma, F1(i, q[h]));
            cmax(f_[i], ma);
        }

        ma = LLONG_MIN;
        h = 1, t = 0;
        For (i, m + 1, r) {
            f[i] = f1[i + 1] + 1ll * (i + 1) * (i + 2) / 2 - s[i];
            while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) >= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
            q[++t] = i;
        }
        For (i, l, m) {
            ll k = i;
            while (h < t && dy(q[t], q[t - 1]) <= dx(q[t], q[t - 1]) * k) t--;
            cmax(ma, F2(i, q[t]));
            cmax(f_[i], ma);
        }

        solve(l, m); solve(m + 1, r);
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    
    solve1::main();
    For (i, 1, n) s[i] = s[i - 1] + a[i];
    memset(f_, -31, sizeof f_);
    solve2::solve(1, n);

    io >> m;
    while (m--) {
        io >> p >> x; //cout << f_[p] << endl;
        printf("%lld\n", max(f0[p - 1] + f1[p + 1], f_[p] - (x - a[p])));
    }

    return 0;
}
