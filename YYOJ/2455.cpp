#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int Mo = 998244353, inv3 = 332748118;

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

inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

int T, Ans, ans, n, op, K;

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> op >> K;
        if (op == 1 || K == 1) {
            int k = (n - K + 1) / 2;
            if (k) {
                add(ans, ml(n, (2ll * k * k - k) % Mo));
                add(ans, -ml(ml(2, inv3), ml(ml(k, k + 1), 2 * k + 1)));
                add(ans, ml(k, (3ll * k + 1) % Mo));
                mul(ans, 2);
            }
            if ((n - K + 1) & 1) {
                k++;
                add(ans, ml(n, (4ll * k - 3) % Mo));
                add(ans, (-4ll * k * k + 6ll * k - 2) % Mo);
            }
        } else {
            int k = (n - K + 1) / 2;
            if (k) {
                add(ans, ml(n, (2ll * k * k + k) % Mo));
                add(ans, -ml(ml(2, inv3), ml(ml(k, k + 1), 2 * k + 1)));
                add(ans, ml(k, k + 1));
                mul(ans, 2);
            }
            if ((n - K + 1) & 1) {
                k++;
                add(ans, ml(n, (4ll * k - 1) % Mo));
                add(ans, (-4ll * k * k + 2 * k) % Mo);
            }
        }
        Ans ^= ans;
    }
    printf("%d", Ans);

    return 0;
}
