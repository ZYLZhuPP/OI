#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 998244353;
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

int n, K, _[3][N], f[N][N], g[N][N], ans, a[N];

inline void solve0() {
    For (i, 1, n) f[i][i] = 1;
    For (i, 1, n) {
        For (j, i, n) For (k, 1, j / i) g[j][k] = f[j][k], f[j][k] = 0;
        For (j, i, n) {
            int x = 0;
            rFor (k, j / i, 1) {
                add(x, g[j][k]);
                if (j + k * _[K][i + 1] <= n) add(f[j + k * _[K][i + 1]][k], x);
            }
            add(ans, x);
        }
    }
}

inline bool check(vector<int > &a) {
    int k = a.size();
    if (k >= 22) return 0;
    int s = 0, t = 1, res = 0;
    For (i, 0, k - 1) s += a[i];
    rFor (i, k - 1, 0) {
        res += t * (2 * s - a[i] + 1) * a[i] / 2;
        if (res > n) return 0;
        t++; s -= a[i];
    }
    return 1;
}

inline bool ok(int k) {
    vector<int > b; For (i, 1, k) b.pb(a[i]);
    if (!check(b)) return 0;
    For (i, 1, K - 3) {
        vector<int > c; int t = 1;
        while (!b.empty()) {
            int x = b.back(); b.pop_back();
            For (j, 1, x) c.pb(t);
            t++;
        }
        swap(b, c);
        if (!check(b)) return 0;
    }
    ans++;
    return 1;
}

inline bool solve(int k, int x) {
    a[k] = x; if (!ok(k)) return 0;
    For (i, x, n) if (!solve(k + 1, i)) break;
    return 1;
}

int main() {
    freopen("function.in", "r", stdin);
    freopen("function.out", "w", stdout);
    io >> n >> K;
    For (i, 1, n) _[1][i] = 1, _[2][i] = i;
    if (K <= 2) solve0();
    else For (i, 1, n) if (!solve(1, i)) break;
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
