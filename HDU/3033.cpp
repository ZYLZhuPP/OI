#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
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

int n, V, ans, K, f[11][N];
vector<pair<int, int > > th[11];

int main() {
    while (~(io >> n >> V >> K)) {
        int id, v, w;
        while (n--) io >> id >> v >> w, th[id].pb({v, w});
        memset(f, -1, sizeof f);
        f[0][0] = 0;
        For (i, 1, K) for (auto &[v, w] : th[i]) {
            rFor (j, V, v) {
                if (~f[i][j - v]) cmax(f[i][j], f[i][j - v] + w);
                if (~f[i - 1][j - v]) cmax(f[i][j], f[i - 1][j - v] + w);
            }
        }
        ans = -1;
        For (i, 0, V) cmax(ans, f[K][i]);
        if (~ans) printf("%d\n", ans);
        else puts("Impossible");
        For (i, 1, K) th[i].resize(0);
    }

    return 0;
}
