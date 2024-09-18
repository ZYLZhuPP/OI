#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, m, x, y;
long double p, pp[N], ans;
vector<int > a[N];

namespace BIT {
    long double v[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, long double d) {
        for (; x <= n; x += lowbit(x)) v[x] += d;
    }
    inline long double pre(int x) {
        long double res = 0;
        for (; x; x -= lowbit(x)) res += v[x];
        return res;
    }
}

int main() {
    io >> n >> m;
    scanf("%Lf", &p);
    For (i, 1, n) pp[i] = 1;
    For (i, 1, m) {
        io >> x >> y;
        a[x].push_back(y);
        pp[x] *= (1.L - p);
    }
    For (i, 1, n) sort(a[i].begin(), a[i].end());
    
    rFor (i, n, 1) {
        long double P = p / (1 - pp[i]);
        for (auto &x : a[i])
            ans += P * BIT::pre(x - 1),
            P *= 1 - p;
        P = p / (1 - pp[i]);
        for (auto &x : a[i])
            BIT::upd(x, P),
            P *= 1 - p;
    }

    printf("%.2Lf", ans);

    return 0;
}
