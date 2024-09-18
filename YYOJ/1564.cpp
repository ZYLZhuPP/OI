#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 65, Mo = 998244353;
inline int mo(int &x) { return x -= x>=Mo? Mo: 0; }
inline int gmo(int x) { return mo(x); }
inline void add(int &x, int y) { mo(x += y); }

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
	inline bool operator ~ () {return ~c;}
} io;

ll n, t;
int cnt1, cnt2, ans, C[N][N], f[N][N];

int qPow(int a, ll b) {
	int res = 1; 
	while (b) {
		if (b & 1) res = 1ll * res * a % Mo; 
		a = 1ll * a * a % Mo;
		b >>= 1;
    }
	return res; 
}

void init() {
    C[0][0] = 1;
    For (i, 1, 60) {
        C[i][0] = 1;
        For (j, 1, 60) C[i][j] = gmo(C[i - 1][j] + C[i - 1][j - 1]);
    }
}

int main() {
    io >> n >> t;
    init();
    For (i, 0, 60) if (t >> i & 1) {
        if ((1ll << i) % 3 == 1) cnt1++;
        else cnt2++;
    }

    For (i, 0, cnt1) For (j, 0, cnt2)
        For (a, 0, i) For (b, 0, j)
            if ((a + b * 2) % 3 == 0)
                add(f[i][j], 1ll * C[i][a] * C[j][b] % Mo);

    For (i, 0, cnt1) For (j, 0, cnt2) {
        int res = 1ll * qPow(f[cnt1 - i][cnt2 - j], n) * C[cnt1][i] % Mo * C[cnt2][j] % Mo;
        if ((i + j) & 1) add(ans, Mo - res);
        else add(ans, res);
    }

    printf("%d", ans);

    return 0;
}
