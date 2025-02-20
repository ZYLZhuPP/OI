#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5, M = N * 80;

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

int n, m, ql[N], qr[N], cnt[N], id[M];
ll a[N], s[N], f[M];
struct Node { int l, r; ll g; } o[M], b[M];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i];
    int t = 0;
    For (i, 1, n) {
        For (j, 1, t) o[j].r = i, o[j].g = __gcd(o[j].g, a[i]);
        o[++t] = {i, i, a[i]};
        int nt = 0;
        For (j, 1, t) if (j == 1 || j == t || o[j].g ^ o[j + 1].g) b[++m] = o[++nt] = o[j];
        t = nt;
    }
    t = 0;
    rFor (i, n, 1) {
        For (j, 1, t) o[j].l = i, o[j].g = __gcd(o[j].g, a[i]);
        o[++t] = {i, i, a[i]};
        int nt = 0;
        For (j, 1, t) if (j == 1 || j == t || o[j].g ^ o[j + 1].g) b[++m] = o[++nt] = o[j];
        t = nt;
    }
    For (i, 1, m) cnt[b[i].r - b[i].l]++;
    For (i, 1, n) cnt[i] += cnt[i - 1];
    For (i, 1, m) id[cnt[b[i].r - b[i].l]--] = i;
    For (_, 1, m) {
        int i = id[_];
        if (b[i].l < b[i].r) {
            int ls = ql[b[i].l], rs = qr[b[i].r];
            f[i] = min(f[ls] + b[ls].g * (b[i].r - b[ls].r) + s[b[i].r] - s[b[ls].r], f[rs] + b[rs].g * (b[rs].l - b[i].l) + s[b[rs].l - 1] - s[b[i].l - 1]);
        }
        ql[b[i].l] = qr[b[i].r] = i;
    }
    printf("%lld", f[id[m]]);

    return 0;
}
