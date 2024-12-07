#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef pair<int, int > P;
const int N = 2e5 + 5;
const lf inf = 1e18;

int n;
P a[N], b[N];

inline lf dist(const P &a, const P &b) { return sqrt(1ll * (a.st - b.st) * (a.st - b.st) + 1ll * (a.nd - b.nd) * (a.nd - b.nd)); }

lf solve(int l, int r) {
    if (l == r) return inf;
    int m = (l + r) >> 1;
    lf d1 = solve(l, m), d2 = solve(m + 1, r), d = min(d1, d2);
    int t = 0;
    For (i, l, r) if (abs(a[i].st - a[m].st) < d) b[++t] = a[i];
    sort(b + 1, b + t + 1, [](P a, P b) { return a.nd < b.nd; });
    For (i, 1, t - 1) For (j, i + 1, t)
        if (b[j].nd - b[i].nd < d) d = min(d, dist(b[i], b[j])); else break;
    return d;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    For (i, 1, n) cin >> a[i].st >> a[i].nd;
    sort(a + 1, a + n + 1);
    printf("%.4lf\n", solve(1, n));

    return 0;
}