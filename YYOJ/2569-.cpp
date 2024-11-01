#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e6 + 5;

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

int n, a[N], pos[N];
ll ans[N];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 0, n) pos[i] = n + 1;
    rFor (i, n, 1) {
        pos[a[i]] = i;
        int lst = i;
        For (j, 0, n) {
            if (pos[j] > lst) ans[j] += pos[j] - lst, lst = pos[j];
            if (lst > n) break;
        }
    }
    For (i, 0, n) printf("%lld ", ans[i]);

    return 0;
}
