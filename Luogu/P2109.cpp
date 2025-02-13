#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 15, Mo = 65521;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int K, a[N][N];
ll n;

struct mat {
    int o[N][N];
    mat() { memset(o, 0, sizeof o); }
    mat operator * (const mat &a) const {
        mat r;
        For (k, 1, 2 * K) For (i, 1, 2 * K) For (j, 1, 2 * K) add(r.o[i][j], ml(o[i][k], a.o[k][j]));
        return r;
    }
};
inline mat qPow(mat a, ll b) { mat r=a; for (b--;b;b>>=1,a=a*a) if (b&1) r=r*a; return r; }

int Det(int n) {
    int res = 1;
    For (i, 1, n) {
        int k = i;
        For (j, i, n) if (a[j][i]) { k = j; break; }
        if (k ^ i) res = Mo - res, swap(a[i], a[k]);
        int iv = qPow(a[i][i], Mo - 2);
        For (j, i + 1, n) {
            int x = ml(a[j][i], iv);
            For (k, i, n) add(a[j][k], -ml(a[i][k], x));
        }
        mul(res, a[i][i]);
    }
    return res;
}

inline int is(const int &i, const int &j) { return i^j? (abs(i-j)<=K? Mo - 1: 0): (min(i - 1, K) + min(n - i, (ll)K)); }

inline void solve0() {
    For (i, 1, n) For (j, 1, n) a[i][j] = is(i, j);
    printf("%d", Det(n - 1));
}

inline void solve() {
    mat A;
    For (i, 1, 2 * K) A.o[i][1] = i^K? Mo - 1: 2 * K;
    For (i, 2, 2 * K) A.o[i - 1][i] = 1;
    A = qPow(A, n - 2 * K - 1);
    For (i, 1, K) {
        For (j, 1, 2 * K) {
            int x = is(i, j);
            For (k, 1, 2 * K) add(a[i][k], ml(A.o[k][j], x));
        }
    }
    For (i, K + 1, 2 * K) For (j, 1, 2 * K) a[i][j] = is(2 * K + 2 - i, 2 * K + 2 - j);
    printf("%d", ml((K + 1) * (n - K - 1) & 1? Mo - 1: 1, Det(2 * K)));
}

int main() {
    io >> K >> n;
    if (n <= 2 * K + 1) solve0();
    else solve();

    return 0;
}
