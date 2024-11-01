#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e7 + 5, Mo = 998244853, inv2 = 499122427, inv3 = 665496569;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r = 1; for (; b; mul(a, a), b >>= 1) if (b & 1) mul(r, a); return r; }

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

int T, P, K, cnt[N], _[N], ans;

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> P >> K;
        if (K == 0) printf("%d\n", ml(P, inv2));
        else if (K == 2) {
            For (i, 0, P - 1) cnt[1ll * i * (i + P - 1) % P]++;
            ans = ml(cnt[0], cnt[0]);
            For (i, 1, P - 1) add(ans, ml(cnt[i], cnt[P - i]));
            printf("%d\n", ml(ml(P, P), qPow(ans, Mo - 2)));
            For (i, 0, P - 1) cnt[i] = 0;
        } else {
            if (P == 2) { printf("%d\n", ml(4, inv3)); continue; }
            For (i, 1, P - 1) _[1ll * i * i % P] = i;
            For (i, 0, P - 1) {
                int x = 1ll * i * (4 + 3 * (P - i)) % P;
                if (!x) ans++; else if (_[x]) ans += 2;
            }
            printf("%d\n", ml(ml(P, P), qPow(ans, Mo - 2)));
            For (i, 0, P - 1) _[i] = 0;
        }
    }

    return 0;
}
