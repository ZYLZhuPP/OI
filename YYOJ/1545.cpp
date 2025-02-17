#include<bits/stdc++.h>
using namespace std;

typedef unsigned int Uint;

const int N = 5e5 + 5, logN = 22;

template<class C> inline bool chkmax(C & x, const C &y) {return x<y? x=y, 1: 0;}

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, n_, ans, cnt, v[N];
Uint a[N], st[N][logN];

Uint gcd(Uint a, Uint b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int main() {
    io >> n;
    for (int i = 1; i <= n; i++) {
        io >> a[i];
        st[i][0] = a[i]; 
    }
    
    n_ = log2(n); 
    for (int i = 1; i <= n_; i++) {
        for (int j = 1; j <= n - (1 << i) + 1; j++) {
            st[j][i] = gcd(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        int l = i, r = i;
        for (int j = n_; j >= 0; j--) {
            int l_ = l - (1 << j), r_ = r + (1 << j);
            if (l_ >= 1 && st[l_][j] % a[i] == 0) l = l_;
            if (r_ <= n && st[r + 1][j] % a[i] == 0) r = r_;
        }
        chkmax(ans, r - l);
        chkmax(v[l], r - l);
    }
    
    for (int i = 1; i <= n; i++) if (v[i] == ans) cnt++;
    printf("%d %d\n", cnt, ans);
    for (int i = 1; i <= n; i++) if (v[i] == ans) printf("%d ", i);
    return 0;
} 
