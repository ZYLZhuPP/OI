#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double Lf;
typedef map<int, ll >::iterator it;
const int N = 2e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, ll b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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
vector<int > del;
map<int, ll > mp;

inline Lf K(const it &l, const it &r) { return 1.L * (r->second - l->second) / (r->first - l->first); }
inline int calc(const it &l, const it &r) {
    int x = r->first - l->first; ll y = r->second - l->second;
    ll a = y / x; int b = y % x;
    return mo(ml(b, qPow(3, a)) + ml(x - b, a? qPow(3, a - 1): 0));
}
inline void delL(int x, ll y, it a) {
    while (a != mp.begin()) {
        it b = prev(a);
        if (1.L * (y - b->second) / (x - b->first) > K(a, b)) add(ans, -calc(b, a)), del.pb(a->first); else return;
        a = b;
    }
}
inline void delR(int x, ll y, it a) {
    while (a != mp.end()) {
        it b = next(a);
        if (a->second <= y) {
            if (b != mp.end()) add(ans, -calc(a, b));
            del.pb(a->first);
        } else break;
        a = b;
    }
    while (a != mp.end()) {
        it b = next(a);
        if (b != mp.end() && 1.L * (y - b->second) / (x - b->first) < K(a, b)) add(ans, -calc(a, b)), del.pb(a->first); else return;
        a = b;
    }
}

int main() {
    io >> n;
    mp[0] = 0;
    int x; ll y;
    For (i, 1, n) {
        io >> x >> y;
        if (mp.count(x)) {
            it p = mp.find(x);
            if (p->second < y) {
                it l = prev(p), r = next(p);
                add(ans, -calc(l, p)), delL(x, y, l);
                if (r != mp.end()) add(ans, -calc(p, r)), delR(x, y, r);
                for (int &x : del) mp.erase(x);
                del.resize(0);
                mp[x] = y;
                p = mp.find(x), l = prev(p), r = next(p);
                add(ans, calc(l, p));
                if (r != mp.end()) add(ans, calc(p, r));
            }
        } else {
            it r = mp.upper_bound(x), l = prev(r);
            if (r == mp.end()) {
                if (y > l->second) {
                    delL(x, y, l);
                    for (int &x : del) mp.erase(x);
                    del.resize(0);
                    mp[x] = y;
                    it p = mp.find(x); l = prev(p);
                    add(ans, calc(l, p));
                }
            } else if (1.L * (y - l->second) / (x - l->first) > K(l, r)) {
                add(ans, -calc(l, r));
                delL(x, y, l); delR(x, y, r);
                for (int &x : del) mp.erase(x);
                del.resize(0);
                mp[x] = y;
                it p = mp.find(x); l = prev(p), r = next(p);
                add(ans, calc(l, p));
                if (r != mp.end()) add(ans, calc(p, r));
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
