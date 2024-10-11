#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;

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

const int pri[32] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127};
ll n, m;
priority_queue<array<ll, 4 > > q;

int main() {
    io >> n >> m;
    For (i, 1, 31) for (ll j = 1, x = 1; x <= n / pri[i]; j++, x *= pri[i]) q.push({x * pri[i], i, j, i - 1});
    while (m--) {
        auto [x, p, c, l] = q.top(); q.pop();
        if (!m) printf("%lld", x);
        else if (c > 1) For (i, 1, l) q.push({x / pri[p] * pri[i], p, c - 1, i});
    }

    return 0;
}
