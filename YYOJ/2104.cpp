#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5005;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int f[N], k, cnt, tot, ans, a[N], s;

int main() {
    For (i, 2, 4999) f[i] = i * (i - 1) / 2;
    io >> k;
    int x = k, y = 4999;
    while (x <= f[y - 1]) y--;
    cnt = y; x = f[y] - x; //cout << cnt << endl;
    while (x) {
        while (x < f[y]) y--;
        x -= f[y]; a[++tot] = y; s += y;
    }
    
    int A = tot, B = cnt - s;

    ans = 1 + cnt + tot;
    printf("%d\n", ans);
    For (i, 2, A + 1) printf("1 %d 1\n", i);
    For (i, A + 2, A + 1 + B) printf("1 %d 2\n", i);
    cnt = A + 1 + B;
    For (i, 1, tot) 
        For (j, 1, a[i]) printf("%d %d 1\n", i + 1, ++cnt);

    return 0;
}
