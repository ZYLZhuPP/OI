#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

struct Node {
    int a, b;
    bool operator < (const Node &x) const { return min(a, x.b) < min(b, x.a); } 
} x[N];

int n, s[N], sum, ans;

int main() {
    io >> n;
    For (i, 1, n) io >> x[i].a >> x[i].b;
    sort(x + 1, x + n + 1);
    rFor (i, n, 1) s[i] = s[i + 1] + x[i].b;
    For (i, 1, n) sum += x[i].a, ans = max(ans, sum + s[i]);
    printf("%d", ans);

    return 0;
}