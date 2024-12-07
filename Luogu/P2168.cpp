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
    inline bool operator ~ () { return ~c; }
} io;

struct Node {
    ll s; int h;
    bool operator < (const Node &a) const { return a.s^s? a.s<s: a.h<h; }
};

int n, K;
ll ans;
priority_queue<Node > q;

int main() {
    io >> n >> K;
    ll x;
    For (i, 1, n) io >> x, q.push({x, 0});
    while ((q.size() - 1) % (K - 1)) q.push({0, 0});
    while (q.size() > 1) {
        ll s = 0; int h = 0;
        For (i, 1, K) s += q.top().s, h = max(h, q.top().h), q.pop();
        q.push({s, h + 1});
        ans += s;
    }
    printf("%lld\n%d", ans, q.top().h);

    return 0;
}