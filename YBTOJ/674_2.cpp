#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define st first
#define nd second
typedef long long ll;
const int N = 5e4 + 5;

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

int n, q[N], m;
ll x[N], y[N], f[N];
pair<int, int > a[N];

ll dx(int i, int j) { return -y[i + 1] + y[j + 1]; }
ll dy(int i, int j) { return f[i] - f[j]; }
ll F(int i, int j) { return f[j] + x[i] * y[j + 1]; }

int main() {
    io >> n;
    For (i, 1, n) io >> a[i].st >> a[i].nd;
    sort(a + 1, a + n + 1);
    For (i, 1, n) {
        while (m && y[m] <= a[i].nd) m--;
        m++; x[m] = a[i].st; y[m] = a[i].nd;
    }

    int l = 1, r = 0;
    q[++r] = 0;
    For (i, 1, m) {
        ll k = x[i];
        while (l < r && dy(q[l + 1], q[l]) < dx(q[l + 1], q[l]) * k) l++;
        f[i] = F(i, q[l]);
        while (l < r && dy(i, q[r]) * dx(q[r], q[r - 1]) < dy(q[r], q[r - 1]) * dx(i, q[r])) r--;
        q[++r] = i;
    }
    printf("%lld", f[m]);

    return 0;
}
