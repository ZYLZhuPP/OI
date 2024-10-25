#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int T, n, a[N], s;

int main() {
    io >> T;
    while (T--) {
        s = 0;
        unordered_map<int, int > mp;
        io >> Mo >> n;
        For (i, 1, n) io >> a[i], mp[a[i]] = i, add(s, a[i]);
        int m = qPow(1ll * n * (n - 1) / 2 % Mo, Mo - 2);
        bool flag = 0;
        For (i, 1, n) {
            int k = ml(m, mo(s - ml(n, a[i])));
            if (!k && n > 1) continue;
            int x = a[i]; bool ok = 1;
            For (j, 1, n - 1) {
                add(x, k);
                if (!mp.count(x)) { ok = 0; break; }
            }
            if (ok) {
                printf("%d %d\n", a[i], k);
                flag = 1;
                break;
            }
        }
        if (!flag) puts("-1");
    }

    return 0;
}
