#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 16e3 + 5, S = 1 << 9, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int T, n, ans, f[M], g[M], a[N];
char s[N];
bool p2[S], p4[S];
vector<int > F, G;

inline int trans(int x, int i, int v0) {
    int v3 = x / 1600, v2 = x / 160 % 10, v1 = x / 16 % 10;
    int y = (x & 7) << 1 | ((x&1 && v0 == a[i]) || (i>1 && x&2 && p2[1 << v0 | 1 << v1] && (1 << v0 | 1 << v1) == (1 << a[i] | 1 << a[i - 1])) || (i>3 && x&8 && p4[1 << v0 | 1 << v1 | 1 << v2 | 1 << v3] && (1 << v0 | 1 << v1 | 1 << v2 | 1 << v3) == (1 << a[i] | 1 << a[i - 1] | 1 << a[i - 2] | 1 << a[i - 3])));
    return y? (v2 * 100 + v1 * 10 + v0) << 4 | y: 0;
}

int main() {
    p2[3] = p2[3 << 1] = p2[3 << 3] = p2[3 << 4] = p2[3 << 6] = p2[3 << 7] = 1;
    p2[9] = p2[9 << 1] = p2[9 << 2] = p2[9 << 3] = p2[9 << 4] = p2[9 << 5] = 1;
    p4[27] = p4[27 << 1] = p4[27 << 3] = p4[27 << 4] = 1;
    io >> T;
    while (T--) {
        ans = 0;
        scanf("%s", s + 1); n = strlen(s + 1);
        For (i, 1, n) a[i] = s[i] - '1';
        f[1] = 1; F.pb(1);
        For (i, 1, n) {
            for (auto &x : F) g[x] = f[x], f[x] = 0;
            swap(F, G); F.resize(0);
            unordered_set<int > se;
            For (j, i - 3, i + 3) if (j > 0 && j <= n) se.insert(a[j]);
            for (auto &c : se) for (auto &x : G) {
                int y = trans(x, i, c);
                if (!y) continue;
                if (!f[y]) f[y] = g[x], F.pb(y);
                else add(f[y], g[x]);
            }
        }
        for (auto &x : F) if (x & 1) add(ans, f[x]);
        printf("%d\n", ans);
        for (auto &x : F) f[x] = 0;
        F.resize(0);
    }

    return 0;
}
