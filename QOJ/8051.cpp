#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

int T, s, n, d, a[N];
ll ans;

int main() {
    io >> T;
    while (T--) {
        s = ans = 0;
        io >> n >> d;
        For (i, 1, n) io >> a[i], s += a[i];
        if (d == 1) printf("%lld\n", 1ll * s * (s - 1) / 2);
        else if (d == 2) {
            ans = 1ll * s * (s - 1) / 2;
            For (i, 1, n) ans -= 1ll * a[i] * (a[i] - 1) / 2;
            printf("%lld\n", ans);
        } else {
            sort(a + 1, a + n + 1);
            int lst = a[n];
            rFor (i, n, 0) {
                if (a[i] < lst) {
                    int x = n - i;
                    ans += 1ll * (lst - a[i]) * x * (x - 1) / 2;
                    lst = a[i];
                }
            }
            printf("%lld\n", ans);
        }
    }

    return 0;
}
