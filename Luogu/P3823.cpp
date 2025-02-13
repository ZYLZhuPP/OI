#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
typedef pair<ull, int > P;
const int N = 2e5 + 5, S = 1e7 + 5, Mo = 998244353;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int n, m, ans, pre[N], suf[N], L[N], R[N], a[N], c[N];
char s[S];
P b[N][51];

namespace Hash {
    const int Base = 131, Mod = 1e7 + 7;
    ull h1[S], _1[S]; int h2[S], _2[S];
    vector<pair<ull, int > > mp[Mod];
    inline void init() {
        _1[0] = _2[0] = 1;
        For (i, 1, S - 1) _1[i] = _1[i - 1] * Base, _2[i] = (_2[i - 1] * Base) % Mod;
    }
    inline void init(int s[], int n) {
        For (i, 1, n) {
            int c = s[i];
            h1[i] = h1[i - 1] * Base + c;
            h2[i] = (h2[i - 1] * Base + c) % Mod;
        }
    }
    inline P ha(int l, int r) {
        return {h1[r] - h1[l - 1] * _1[r - l + 1], (h2[r] - 1ll * h2[l - 1] * _2[r - l + 1] % Mod + Mod) % Mod};
    }
    inline void add(P x, int d) {
        auto [h1, h2] = x;
        for (auto &[x, cnt] : mp[h2]) if (x == h1) return cnt += d, void();
        mp[h2].pb({h1, d});
    }
    inline int query(P x) {
        auto [h1, h2] = x;
        for (auto &[x, cnt] : mp[h2]) if (x == h1) return cnt;
        return 0;
    }
}
using namespace Hash;

inline void merge(int x, int y) {
    suf[x] = y; pre[y] = x;
    int l = 0, r = 0;
    while (x && l < 50) L[++l] = x, x = pre[x];
    while (y && r < 50) R[++r] = y, y = suf[y];
    rFor (i, l, 1) c[l - i + 1] = a[L[i]];
    For (i, 1, r) c[l + i] = a[R[i]];
    init(c, l + r);
    For (i, 1, l) For (j, i + 1, 50) {
        int x = l - i + 1, y = x + j - 1;
        if (y > l + r) break;
        add(b[L[i]][j] = ha(x, y), 1);
    }
}

inline void split(int x, int y) {
    suf[x] = pre[y] = 0;
    int l = 0, r = 0;
    while (x && l < 50) L[++l] = x, x = pre[x];
    while (y && r < 50) R[++r] = y, y = suf[y];
    For (i, 1, l) For (j, i + 1, 50) {
        int x = l - i + 1, y = x + j - 1;
        if (y > l + r) break;
        add(b[L[i]][j], -1);
    }
}

int main() {
    init();
    io >> n >> m;
    For (i, 1, n) io >> a[i], b[i][1] = {a[i], a[i]}, add(b[i][1], 1);
    while (m--) {
        int op, x, y, k;
        io >> op;
        if (op == 1) io >> x >> y, merge(x, y);
        else if (op == 2) io >> x, split(x, suf[x]);
        else {
            scanf("%s", s + 1); io >> k;
            x = strlen(s + 1);
            For (i, 1, x) c[i] = s[i] ^ 48;
            init(c, x);
            ans = 1;
            For (i, 1, x - k + 1) if (ans) ans = 1ll * ans * query(ha(i, i + k - 1)) % Mo;
            printf("%d\n", ans);
        }
    }

    return 0;
}
