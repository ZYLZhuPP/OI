#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    IO& operator >> (int &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
} io; 

struct P {
    int id, b, w;
    bool operator < (const P &a) const { return 1ll * w * a.b < 1ll * a.w * b; }
    bool operator != (const P &a) const { return (b + w) ^ (a.b + a.w); }
} b[N];
priority_queue<P > q;

int n, x, f[N];
long long ans;

int fa[N];
inline int find(int k) { return fa[k]^k? fa[k] = find(fa[k]): k; }

int main() {
    io >> n;
    For (i, 2, n) io >> f[i];
    For (i, 1, n) io >> x, b[i] = (P){i, x, 1 - x}, fa[i] = i;
    For (i, 2, n) q.push(b[i]);
    For (i, 1, n - 1) {
        while (b[q.top().id] != q.top()) q.pop();
        int u = q.top().id, v = find(f[u]); q.pop();
        ans += 1ll * b[v].b * b[u].w;
        fa[u] = v; b[v].b += b[u].b; b[v].w += b[u].w;
        if (v ^ 1) q.push(b[v]);
    }
    printf("%lld", ans);

    return 0;
}
