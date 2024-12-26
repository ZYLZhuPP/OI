#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
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

struct V {
    int x, y;
    bool operator < (const V &a) const { return x^a.x? x<a.x: y<a.y; }
    V operator + (const V &a) const { return {x + a.x, y + a.y}; }
    V operator - (const V &a) const { return {x - a.x, y - a.y}; }
    ll norm() const { return 1ll * x * x + 1ll * y * y; }
    ll cross(const V &a) const { return 1ll * x * a.y - 1ll * y * a.x; }
    bool dir() const { return x > 0 || (!x && y > 0); }
} b[N], C, start, stk[N];

ll n, cnt, ans, top;
vector<V > c;

bool cmp(const V &x, const V &y) {
    ll res = (x - C).cross(y - C);
    return res? res>0: (x - C).norm()>(y - C).norm();
}

void ConvexHull(vector<V > &v) {
    For (i, 1, (int)v.size() - 1) if (v[i] < v[0]) swap(v[i], v[0]);
    C = stk[top = 1] = v[0];
    sort(v.begin() + 1, v.end(), cmp);
    For (i, 1, (int)v.size() - 1) {
        while (top >= 2 && (stk[top] - stk[top - 1]).cross(v[i] - stk[top]) < 0) top--;
        stk[++top] = v[i];
    }
    v.resize(0);
    For (i, 1, top) v.pb(stk[i]);
}

int main() {
    io >> n;
    int k, x, y;
    For (i, 1, n) {
        c.resize(0);
        io >> k;
        while (k--) io >> x >> y, c.pb({x, y});
        ConvexHull(c), start = start + c[0];
        For (i, 1, (int)c.size()) b[++cnt] = c[i % c.size()] - c[i - 1];
    }
    sort(b + 1, b + cnt + 1, [&](V x, V y) { return x.dir()^y.dir()? x.dir(): x.cross(y)>0; });
    For (i, 1, cnt) cmax(ans, start.norm()), start = start + b[i];
    printf("%lld", ans);

    return 0;
}