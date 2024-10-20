#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 155, M = 3e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int K, q, f[M], g[M], s[M], ans[N][2][M];
vector<array<int, 2 > > op[N];

int main() {
    io >> K;
    io >> q;
    For (i, 1, q) {
        int n, x;
        io >> n >> x;
        op[x - 1].pb({i, 0});
        op[n - x].pb({i, 1});
    }
    f[0] = 1;
    For (i, 1, 150) {
        for (auto &[id, x] : op[i - 1]) memcpy(ans[id][x], f, sizeof f);
        int n = min(M - 1, K * i * (i + 1) / 2);
        memcpy(g, f, sizeof f);
        For (r, 0, i - 1) For (j, 0, (n - r) / i) {
            s[j] = mo((j? s[j - 1]: 0) + g[j * i + r]);
            add(f[j * i + r], mo((j? s[j - 1]: 0) - (j>K? s[j - K - 1]: 0)));
        }
    }
    For (i, 1, q) {
        int Ans = 0;
        For (j, 0, M - 1) add(Ans, ml(ans[i][0][j], ans[i][1][j]));
        mul(Ans, K + 1);
        add(Ans, -1);
        printf("%d\n", Ans);
    }

    return 0;
}
