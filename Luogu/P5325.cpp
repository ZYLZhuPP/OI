#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline int qPow(ll a, ll b) { ll r=1; for(;b;b>>=1,a=ml(a,a))if(b&1)r=ml(r,a); return r; }

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

namespace min25 {
    const int N = 1e5 + 5;
    int m, id1[N], id2[N], P, p[N], mip[N];
    int inv2 = qPow(2, Mo - 2), inv6 = qPow(6, Mo - 2);
    ll n, w[N << 1];
    int g[N << 1], h[N << 1], f[N << 1], preg[N], preh[N];

    int F(ll x) { x %= Mo; return mo(ml(x, x) - x); }
    int sg(ll x) { x %= Mo; return ml(ml(x, x + 1), inv2); }
    int sh(ll x) { x %= Mo; return ml(ml(x, x + 1), ml(mo(2 * x + 1), inv6)); }

    void init() {
        p[0] = 0;
        For (i, 2, P) {
            if (!mip[i]) {
                p[mip[i] = ++p[0]] = i;
                preg[p[0]] = mo(preg[p[0] - 1] + i);
                preh[p[0]] = mo(preh[p[0] - 1] + ml(i, i));
            }    
            for (int j = 1; j <= mip[i] && i * p[j] <= P; ++j)
                mip[i * p[j]] = j; 
        }
    }

#define getid(x) ((x)<=P? id1[x]: id2[n / (x)])

    int ask(ll x, int i) {
        if (x <= 1 || x < p[i]) return 0;
        int res = mo(f[getid(x)] - mo(preh[i - 1] - preg[i - 1]));

        For (j, i, p[0]) {
            if (x / p[j] < p[j]) break;
            ll t = p[j];
            for (int e = 1; t * p[j] <= x; e++, t *= p[j])
                add(res, mo(ml(F(t), ask(x / t, j + 1)) + F(t * p[j])));
        }

        return res;
    }

    int calc(ll x) {
        n = x;
        P = sqrt(n);
        init();
        
        m = 0;
        for (ll l = 1; l <= n; ) {
            ll v = n / l, r = n / v;
            if (v <= P) id1[v] = ++m; else id2[r] = ++m;
            w[m] = v;
            g[m] = sg(v) - 1;
            h[m] = sh(v) - 1;
            l = r + 1;
        }

        For (j, 1, p[0]) {
            For (i, 1, m) {
                if (w[i] / p[j] < p[j]) break;
                add(g[i], -ml(p[j], mo(g[getid(w[i] / p[j])] - preg[j - 1])));
                add(h[i], -ml(ml(p[j], p[j]), mo(h[getid(w[i] / p[j])] - preh[j - 1])));
            }
        }
        
        For (i, 1, m) f[i] = mo(h[i] - g[i]);
        return mo(ask(n, 1) + 1);
        rFor (j, p[0], 1) {
            For (i, 1, m) {
                if (w[i] / p[j] < p[j]) break;
                ll t = p[j];
                for (int e = 1; t * p[j] <= w[i]; e++, t *= p[j])
                    add(f[i], mo(ml(F(t), mo(f[getid(w[i] / t)] - mo(preh[j] - preg[j]))) + F(t * p[j])));
            }
        }

        return mo(f[getid(n)] + 1);
    }
}

int main() {
    ll n;
    io >> n;

    cout << min25::calc(n);

    return 0;
}
