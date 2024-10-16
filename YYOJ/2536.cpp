#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int m, P, s[N], A[N], tot;
ll n, Ans;
vector<int > C[N];
vector<array<int, 3 > > ans;

inline void solveb(int a, int b) {
    if (tot == 1e5) return;
    for (auto &c : C[n % a + b]) if (tot < 1e5) ans.pb({a, b, c}), tot++;
}

inline void solvea(int a) {
    if (tot == 1e5) return;
    For (b, 0, P) solveb(a, b);
}

int main() {
    io >> n >> m >> P; n = n * n + 1;
    For (c, m + 1, P) for (int i = m; i < 2 * P; i += c) C[i].pb(c);
    For (i, 0, 2 * P - 1) s[i] = (i? s[i - 1]: 0) + C[i].size();
    For (i, 0, P - 1) A[i] = s[i + P] - (i? s[i - 1] : 0);
    For (a, 1, P) {
        Ans += A[n % a];
        if (A[n % a]) solvea(a);
    }
    printf("%lld\n", Ans);
    for (auto &[a, b, c] : ans) printf("%d %d %d\n", a, b, c);

    return 0;
}
