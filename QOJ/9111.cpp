#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double Lf;
const int N = 1e3 + 5, S = 4e3 + 5, Mo = 998244353;
const Lf eps = 1e-11;
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int T, n, m, vis[N][S], tim;
Lf f[N][S];
char t[N];

namespace ACAM {
    int ch[S][26], tot = 1, fail[S], sum[S];
    char s[S];

    inline void add(char s[], int x) {
        int n = strlen(s + 1), u = 1;
        For (i, 1, n) {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
        sum[u] += x;
    }

    inline void build() {
        For (i, 0, 25) ch[0][i] = 1;
        queue<int > q; q.push(1);
        fail[1] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); sum[u] += sum[fail[u]];
            For (i, 0, 25) (ch[u][i]? q.push(ch[u][i]), fail[ch[u][i]]: ch[u][i]) = ch[fail[u]][i];
        }
    }
}
using namespace ACAM;

inline bool ok(Lf x) {
    f[0][1] = 0; vis[0][1] = ++tim;
    For (i, 0, n - 1) For (j, 1, tot) if (vis[i][j] == tim) {
        int c = t[i + 1] - 'a', k = ch[j][c];
        if (vis[i + 1][j] ^ tim) vis[i + 1][j] = tim, f[i + 1][j] = f[i][j];
        else cmax(f[i + 1][j], f[i][j]);
        if (vis[i + 1][k] ^ tim) vis[i + 1][k] = tim, f[i + 1][k] = f[i][j] + sum[k] - x;
        else cmax(f[i + 1][k], f[i][j] + sum[k] - x);
    }
    For (i, 1, tot) if (vis[n][i] == tim && f[n][i] > eps) return 1;
    return 0;
}

inline void solve() {
    For (i, 1, tot) fail[i] = sum[i] = 0, memset(ch[i], 0, sizeof ch[i]);
    tot = 1;
    io >> n >> m;
    scanf("%s", t + 1);
    int x;
    For (i, 1, m) scanf("%s", s + 1), io >> x, add(s, x);
    build();
    Lf l = 0, r = 2e8;
    while (r - l > eps) {
        Lf mid = (l + r) / 2;
        if (ok(mid)) l = mid;
        else r = mid;
    }
    For (i, 1, n) {
        ll x = round(l * i);
        if (fabs(x - l * i) < n * eps) { printf("%d\n", ml(x % Mo, qPow(i, Mo - 2))); return; }
    }
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
