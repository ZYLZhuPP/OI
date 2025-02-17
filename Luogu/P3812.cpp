#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 1e5 + 5;
template<class C> inline void cmax(C &x, const C &y) { x = y>x? y: x; }

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

int n;

struct Basis {
    static const int B = 60;
    ll o[B]; bool zero;
    Basis() { memset(o, 0, sizeof o); zero = 0; }
    void ins(ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return void(o[i] = x);
            else x ^= o[i];
        }
        zero = 1;
    }
    bool in(ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return 0;
            else x ^= o[i];
        }
        return 1;
    }
    ll mx() {
        ll res = 0;
        rFor (i, B - 1, 0) cmax(res, res ^ o[i]);
        return res;
    }
    ll mn() {
        if (zero) return 0;
        For (i, 0, B - 1) if (o[i]) return o[i];
        return 1ll << B;
    }
    ll kth(ll k) {
        k -= zero; if (!k) return 0;
        rFor (i, B - 1, 0) if (o[i]) For (j, i + 1, B - 1) if (o[j] >> i & 1) o[j] ^= o[i];
        ll res = 0;
        For (i, 0, B - 1) if (o[i]) {
            if (k & 1) res ^= o[i];
            k >>= 1;
        }
        return res;
    }
};

int main() {
    Basis b;
    io >> n;
    ll x;
    For (i, 1, n) io >> x, b.ins(x);
    cout << b.mx();

    return 0;
}
