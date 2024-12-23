#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, ans;
vector<array<int, 4 > > ops;
map<int, int > mp;

int main() {
    io >> n;
    int op, t, x, k;
    while (n--) io >> op >> t >> x >> k, ops.pb({-t - x, -t + x, 2 - op, k});
    sort(ops.begin(), ops.end());
    for (auto &[x, y, op, k] : ops) {
        if (op) {
            while (k && !mp.empty()) {
                auto it = mp.upper_bound(y);
                if (it != mp.begin()) {
                    it = prev(it);
                    auto [a, b] = *it;
                    cmin(b, k); ans += b; k -= b;
                    if (!(mp[a] -= b)) mp.erase(a);
                } else break;
            }
        } else mp[y] += k;
    }
    printf("%d", ans);

    return 0;
}
