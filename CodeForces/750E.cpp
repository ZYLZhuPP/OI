#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, q;
char s[N];

namespace Seg {
    struct mat {
        int o[5][5];
        mat() { memset(o, 31, sizeof o); }
        mat(char c) {
            memset(o, 31, sizeof o);
            o[0][0] = c=='2'; o[1][1] = c=='0'; o[2][2] = c=='1';
            o[3][3] = c=='6'||c=='7'; o[4][4] = c=='6';
            if (c == '2') o[0][1] = 0; if (c == '0') o[1][2] = 0;
            if (c == '1') o[2][3] = 0; if (c == '7') o[3][4] = 0;
        }
        mat operator * (const mat &a) const {
            mat r;
            For (k, 0, 4) For (i, 0, 4) For (j, 0, 4) cmin(r.o[i][j], o[i][k] + a.o[k][j]);
            return r;
        }
        mat operator + (const mat &a) const {
            mat r;
            For (k, 0, 4) For (j, 0, 4) cmin(r.o[0][j], o[0][k] + a.o[k][j]);
            return r;
        }
    } o[N << 2], ans;
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] * o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = mat(s[l]), void();
        M; build(goL); build(goR); up(p);
    }
    inline void query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return void(ans = ans + o[p]);
        M; query(goL, x, y); query(goR, x, y);
    }
}
using namespace Seg;

int main() {
    io >> n >> q;
    scanf("%s", s + 1);
    build(1, 1, n);
    while (q--) {
        int l, r;
        io >> l >> r;
        ans = mat(); ans.o[0][0] = 0;
        query(1, 1, n, l, r);
        printf("%d\n", ans.o[0][4]<=n? ans.o[0][4]: -1);
    }

    return 0;
}
