#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e6 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n;
ll ans, res;
vector<int > pos[N];

struct Node {
    int p, x;
    bool operator < (const Node &a) const { return p > a.p; }
};
set<Node > se;

inline void upd(int p, int x) {
    auto it = se.lower_bound({p, 0});
    int y = it!=se.end()? it->p: 0;
    while (it != se.end() && it->x >= x) {
        auto nxt = next(it);
        res -= 1ll * (it->p - (nxt!=se.end()? nxt->p: 0)) * it->x;
        se.erase(it), it = nxt;
    }
    if (it != se.end() && it->p >= p && it->x <= x) return;
    if (it != se.begin()) {
        auto pre = prev(it);
        if (pre->x <= x) return;
        res -= 1ll * (p - y) * pre->x;
    }
    se.insert({p, x});
    res += 1ll * (p - (it!=se.end()? it->p: 0)) * x;
}

int main() {
    io >> n;
    int x;
    For (i, 1, n) io >> x, pos[x].pb(i);
    For (i, 0, n) {
        int p = 0;
        for (auto &x : pos[i]) upd(x - 1, p), p = x;
        upd(n, p);
        ll x = 1ll * n * (n + 1) / 2 - res;
        printf("%lld ", x - ans); ans = x;
    }

    return 0;
}
