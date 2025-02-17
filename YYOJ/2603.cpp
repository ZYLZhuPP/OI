#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;

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

int n, m, S, lim, a[10];
ll ans;
vector<int > A, B;

inline void dfs(int k, int s, vector<int > &b) {
    if (k > lim) return b.pb(S - s), void();
    int x = 1;
    while (x <= s / a[k]) {
        dfs(k + 1, s - x * a[k], b);
        x *= a[k];
    }
}

int main() {
    io >> n >> S; m = (n + 1) / 2;
    For (i, 1, n) io >> a[i];
    lim = m; dfs(1, S, A); sort(A.begin(), A.end());
    lim = n; dfs(m + 1, S, B); sort(B.begin(), B.end());
    int s = B.size();
    for (auto &x : A) {
        while (s && B[s - 1] + x > S) s--;
        ans += s;
    }
    printf("%lld", ans);

    return 0;
}
