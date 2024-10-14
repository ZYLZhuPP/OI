#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e7 + 5, Mo = 998244353;
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

int n, ans, x, y;
char a[N];

int main() {
    scanf("%s", a + 1);
    n = strlen(a + 1);
    if (n == 1 && a[1] == '1') return puts("0"), 0;
    int x = 0, y = 0;
    For (i, 1, n) {
        int c = a[i] ^ 48;
        x = (10ll * x + c) % Mo;
        y = (10ll * y + c) % (Mo - 1);
    }
    add(x, -2);
    int z = qPow(qPow(2, y), y);
    ans = ml(z, (2ll * x * x + 5ll * x + 3) % Mo);
    printf("%d", ans);

    return 0;
}
