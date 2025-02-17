#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, m, P, x, y;
ll d[N], a[N], s[N], f0[N], f1[N];
int q[N];

inline ll dx(int i, int j) { return i - j; }
inline ll dy(int i, int j) { return f0[i] + s[i] - (f0[j] + s[j]); }
inline ll F(int i, int j) { return f0[j] + a[i] * (i - j) - (s[i] - s[j]); }

int main() {
    io >> n >> m >> P;
    For (i, 2, n) io >> x, d[i] = d[i - 1] + x;
    For (i, 1, m) io >> x >> y, a[i] = y - d[x];
    sort(a + 1, a + m + 1);
    For (i, 1, m) s[i] = s[i - 1] + a[i];

    memset(f1, 31, sizeof f1); f1[0] = 0;
    For (k, 1, P) {
        swap(f0, f1);
        int h = 1, t = 0; q[++t] = 0;
        For (i, 1, m) {
            ll k = a[i];
            while (h < t && dy(q[h + 1], q[h]) <= dx(q[h + 1], q[h]) * k) h++;
            f1[i] = F(i, q[h]);
            while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) <= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
            q[++t] = i;
        }
    }
    printf("%lld", f1[m]);

    return 0;
}
