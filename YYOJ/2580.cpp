#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef bitset<169 > B;
const int N = 1e6 + 5, M = 4e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

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
	inline bool operator ~ () const { return ~c; }
} io;

int T, n, mip[N], pri[M], psz, _2[N], ans, co[N];
bitset<M > vis;
B o[169], a[N], w[M], b;

inline void init() {
    _2[0] = 1; For (i, 1, N - 1) _2[i] = mo(_2[i - 1] << 1);
    For (i, 2, N - 1) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            if (psz > 168) co[i] = psz;
            else a[i][psz] = 1;
        }
        For (j, 1, mip[i]) {
            if (pri[j] > (N - 1) / i) break;
            int x = i * pri[j];
            mip[x] = j; co[x] = co[i];
            a[x] = a[i]; if (j <= 168) a[x][j] = 1;
        }
    }
}

inline bool ins(B a) {
    For (i, 1, 168) if (a[i]) {
        if (!b[i]) return o[i] = a, b[i] = 1;
        else a ^= o[i];
    }
    return 0;
}

int main() {
    init();
    io >> T;
    For (t, 1, T) {
        ans = 0; vis = 0; b = 0;
        io >> n;
        int x;
        For (i, 1, n) {
            io >> x;
            int c = co[x];
            if (!c) ans += !ins(a[x]);
            else {
                if (!vis[c]) w[c] = a[x], vis[c] = 1;
                else ans += !ins(a[x] ^ w[c]);
            }
        }
        printf("%d\n", _2[ans] - 1);
    }

    return 0;
}
