#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

struct IO {
    static const int BufS = 1 << 20;
    char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, A, B;
vector<pair<int, ll > > qx, qy;
mt19937_64 rnd(1145141);

inline int solve(vector<pair<int, ll > > q) {
    unordered_map<ll, int > mp;
    sort(q.begin(), q.end());
    int n = q.size(); ll s = 0;
    For (i, 0, n - 2) {
        s ^= q[i].second;
        mp[s] += q[i + 1].first - q[i].first;
    }
    int res = 0;
    for (auto &p : mp) cmax(res, p.second);
    return res;
}

int main() {
    freopen("donuts.in", "r", stdin);
    freopen("donuts.out", "w", stdout);
    io >> n >> A >> B;
    qx.pb({0, 0}), qx.pb({A, 0});
    qy.pb({0, 0}), qy.pb({B, 0});
    int x, y, X, Y;
    For (i, 1, n) {
        io >> x >> y >> X >> Y;
        if (x > X) swap(x, X);
        if (y > Y) swap(y, Y);
        ll v = rnd();
        qx.pb({x, v}), qx.pb({X, v});
        qy.pb({y, v}), qy.pb({Y, v});
    }
    printf("%lld", 1ll * solve(qx) * solve(qy));

    fclose(stdin); fclose(stdout);
    return 0;
}
