#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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
    inline bool operator ~ () { return ~c; }
} io;

struct Node {
    int a, b;
    bool operator < (const Node &x) const { return (a<=b && (x.a>x.b || a<x.a)) || (a>b && x.a>x.b && b>x.b); }
} x[N];

int n;
ll s[N], sum, ans;

int main() {
    io >> n;
    For (i, 1, n) io >> x[i].a >> x[i].b;
    sort(x + 1, x + n + 1);
    For (i, 1, n) s[i] = s[i - 1] + x[i].b;
    For (i, 1, n) sum += x[i].a, ans = max(ans, sum - s[i - 1]);
    printf("%lld", ans);

    return 0;
}