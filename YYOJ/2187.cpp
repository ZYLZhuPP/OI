#include<bits/stdc++.h>
using namespace std;

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

int n, m, x, y, X, Y, ans;

int main() {
    io >> n >> m >> x >> y >> X >> Y;
    if (n > m) swap(n, m), swap(x, y), swap(X, Y);
    if ((x==X && abs(y - Y) == 1) || (y==Y && abs(x - X) == 1)) return puts("-1"), 0;
    int a = X - 1, b = Y - 1, c = n - X, d = m - Y, e = abs(x - X)==1 && abs(y - Y)==1;
    if (max(max(a, b), max(c, d)) <= 1) ans = 1;
    else if (n <= 2 && !(e && b > 1 && d > 1)) ans = 2;
    else if ((a<=1 && b<=1 && (x!=X+1 || y!=Y+1)) || (b<=1 && c<=1 && (y!=Y+1 || x!=X-1)) || (c<=1 && d<=1 && (x!=X-1 || y!=Y-1)) || (d<=1 && a<=1 && (y!=Y-1 || x!=X+1))) ans = 2;
    else ans = 3;
    printf("%d", ans);

    return 0;
}
