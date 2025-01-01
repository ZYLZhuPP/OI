#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, q, ans;
char a[N], b[N];

inline int get(int i) { return (i&1? 1: -1) * (a[i] - b[i]); }

int main() {
    io >> n >> q;
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    For (i, 1, n) ans += get(i);
    puts(ans%26? "ne": "da");
    char ch[3]; int x;
    while (q--) {
        io >> x; scanf("%s", ch);
        ans -= get(x); a[x] = ch[0]; ans += get(x);
        puts(ans%26? "ne": "da");
    }

    return 0;
}
