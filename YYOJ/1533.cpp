#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5, Sq = 405;
const ll Mo = 998244353;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

int n, m, st[Sq], ed[Sq], bel[N], cnt[Sq][N], c[N], op;
ll v[N], add[Sq][N], sum[Sq], l, r, x, y;

int main() {
    io >> n >> m;
    int sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        st[i] = (i - 1) * sq + 1;
        ed[i] = i * sq;
    }
    ed[sq] = n;
    for (int i = 1; i <= sq; i++) {
        for (int j = st[i]; j <= ed[i]; j++) {
            bel[j] = i;
            io >> c[j];
            cnt[i][c[j]]++;
        }
    }

    while (m--) {
        io >> op;
        if (op == 1) {
            io >> l >> r >> x >> y;
            int bl = bel[l], br = bel[r];

            if (bl == br) {
                for (int i = l; i <= r; i++) if (c[i] == x) v[i] += y, sum[bl] += y;
            } else {
                for (int i = l; i <= ed[bl]; i++) if (c[i] == x) v[i] += y, sum[bl] += y;
                for (int i = st[br]; i <= r; i++) if (c[i] == x) v[i] += y, sum[br] += y;
                for (int i = bl + 1; i <= br - 1; i++) add[i][x] += y, sum[i] += cnt[i][x] * y;
            }
        } else if (op == 2) {
            io >> l >> r;
            int bl = bel[l], br = bel[r];
            ll ans = 0;

            if (bl == br) {
                for (int i = l; i <= r; i++) ans = (ans + v[i] + add[bl][c[i]]) % Mo;
            } else {
                for (int i = l; i <= ed[bl]; i++) ans = (ans + v[i] + add[bl][c[i]]) % Mo;
                for (int i = st[br]; i <= r; i++) ans = (ans + v[i] + add[br][c[i]]) % Mo;
                for (int i = bl + 1; i <= br - 1; i++) ans = (ans + sum[i]) % Mo;
            }

            printf("%lld\n", ans);
        } else if (op == 3) {
            io >> x >> y;
            int bx = bel[x];

            v[x] = v[x] + add[bx][c[x]] - add[bx][y];
            cnt[bx][c[x]]--;
            c[x] = y;
            cnt[bx][y]++;
        }
    }

    return 0;
}
