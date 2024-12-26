#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

struct Node {
    ll s, t;
    bool operator < (const Node &a) const { return s + t < a.s + a.t; }
} a[N];

int T, ans, n;

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n;
        For (i, 1, n) io >> a[i].s >> a[i].t;
        sort(a + 1, a + n + 1);
        priority_queue<ll > q;
        ll t0 = 0;
        For (i, 1, n) {
            if (t0 <= a[i].s) t0 += a[i].t, ans++, q.push(a[i].t);
            else if (a[i].t < q.top()) {
                t0 -= q.top() - a[i].t;
                q.pop(); q.push(a[i].t);
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}