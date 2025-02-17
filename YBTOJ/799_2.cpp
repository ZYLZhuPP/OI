#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 1005;

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
pair<int, ll> a[N];

struct Basis {
    static const int B = 63;
    ll o[B]; bool zero;
    Basis() { memset(o, 0, sizeof o); zero = 0; }
    bool ins(ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            x ^= o[i];
        }
        return zero = 1, 0;
    }
} B;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i].nd >> a[i].st;
    sort(a + 1, a + n + 1);
    rFor (i, n, 1) if (B.ins(a[i].nd)) ans += a[i].st;
    printf("%d", ans);

    return 0;
}
