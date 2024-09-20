#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, Q, B;
ll S[N], a[500], s[500][500], ans;

namespace BIT {
    ll k[N], b[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(ll o[], int x, const ll &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline ll query(ll o[], int x) { ll r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

inline void Upd(int l, int r, int x) {
    if (l > r) return;
    upd(k, l, x); upd(k, r + 1, -x);
    upd(b, l, -1ll * (l - 1) * x); upd(b, r + 1, 1ll * r * x);
}

inline ll Query(int x) { return x * query(k, x) + query(b, x); }

int main() {
    io >> n >> Q; B = sqrt(n);
    int x;
    For (i, 1, n) io >> x, S[i] = S[i - 1] + x;
    while (Q--) {
        int op, K, l, r, x;
        io >> op;
        if (op == 1) {
            io >> K >> l >> r >> x;
            if (K <= B) {
                For (i, l, r) a[i] = x;
                For (i, 1, K - 1) a[i] += a[i - 1];
                For (i, 0, K - 1) s[K][i] += a[i], a[i] = 0;
            } else {
                while (l <= n) {
                    Upd(max(l, 1), min(r, n), x);
                    l += K; r += K;
                }
            }
        } else {
            io >> l >> r;
            ans = S[r] - S[l - 1] + Query(r) - Query(l - 1);
            For (i, 1, B) {
                int L = l / i, R = r / i;
                if (L == R) ans += s[i][r % i] - (l%i>0? s[i][l % i - 1]: 0);
                else {
                    ans += (R - L - 1) * s[i][i - 1];
                    ans += s[i][i - 1] - (l%i>0? s[i][l % i - 1]: 0);
                    ans += s[i][r % i];
                }
            }
            printf("%lld\n", ans);
        }
    }

    return 0;
}
