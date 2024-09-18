#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5, P = 2e7 + 5;

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

int n, m, phi[P], pri[P], psz, mip[P];
bool flag;

namespace BIT {
    ll o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline ll query(int x) { ll r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

void init_Phi() {
    phi[1] = 1;
    For (i, 2, P - 1) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            phi[i] = i - 1;
        }
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne >= P) break;
            mip[ne] = j;
            if (j ^ mip[i]) phi[ne] = phi[i] * phi[pri[j]];
            else phi[ne] = phi[i] * pri[j];
        }
    }
}

inline int qPow(ll a, ll b, int p) {
    flag = 0;
    if (b && a > p) flag = 1, a %= p;
    if (!a) return 0;
    if (!b) return 1;
    ll r = 1;
    while (b) {
        if (b & 1) {
            r *= a;
            if (r > p) flag = 1, r %= p;
        }
        b >>= 1;
        if (!b) break;
        a *= a;
        if (a > p) flag = 1, a %= p;
    }
    return r;
}

inline int solve(int l, int r, int p) {
    ll x = query(l);
    flag = x > p;
    if (p == 1 || x % p == 0) return 0;
    if (x % p == 1) return 1;
    if (l == r) return x % p;
    ll y = solve(l + 1, r, phi[p]);
    if (flag) y += phi[p];
    return qPow(x, y, p);
}

int main() {
    init_Phi();
    io >> n >> m;
    int op, x, l, r;
    For (i, 1, n) io >> x, upd(i, x), upd(i + 1, -x);
    while (m--) {
        io >> op >> l >> r >> x;
        if (op == 1) upd(l, x), upd(r + 1, -x);
        else if (op == 2) printf("%d\n", solve(l, r, x));
    }

    return 0;
}
