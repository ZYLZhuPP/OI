#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define mkp make_pair
#define st first
#define nd second
template<class C> inline bool cmax(C &x, const C &y) { return x<y? x=y, 1: 0; }
typedef long long ll;
const int N = 1e6 + 5;

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

vector<pair<int, int > > a;
int n, L, R, l[N], r[N], tot;
ll ans;

void solve(int x, int y, int le, int ri) {
    if (x > y) return;
    int k = (x + y) >> 1;
    ll res = 0, pos = le;
    For (i, le, ri) if (i ^ k)
        if (cmax(res, 1ll * (r[k] - l[i]) * (r[i] - l[k])))
            pos = i;

    ans = max(ans, res);
    solve(x, k - 1, le, pos);
    solve(k + 1, y, pos, ri);
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> L >> R;
        a.push_back(mkp(L, R));
    }
    sort(a.begin(), a.end());

    for (auto &e : a) {
        int L = e.st, R = e.nd;
        if (R <= r[tot]) cmax(ans, 1ll * (r[tot] - l[tot]) * (R - L));
        else l[++tot] = L, r[tot] = R;
    }

    solve(1, tot, 1, tot);

    printf("%lld", ans);

    return 0;
}
