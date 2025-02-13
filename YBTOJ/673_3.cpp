#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define st first
#define nd second
const int N = 1e5 + 5, M = 11, Mo = 1e5 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }

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

struct Bit {
    int o[N];
    Bit() { memset(o, 0, sizeof o); }
#define lowbit(x) ((x) & -(x))
    inline void upd(int i, int d) { for (; i < N; i += lowbit(i)) add(o[i], d); }
    inline int pre(int i) { int r = 0; for (; i; i -= lowbit(i)) add(r, o[i]); return r; }
    inline int suf(int i) { return mo(pre(N - 1) - pre(i - 1)); }
} up[M], down[M];

pair<int, int > xy[N];
int n, k, a[N];

int main() {
    io >> n >> k;
    For (i, 1, n) io >> xy[i].st >> xy[i].nd;
    sort(xy + 1, xy + n + 1);
    For (i, 1, n) a[i] = xy[i].nd;

    For (i, 1, n) {
        int x = a[i];
        up[0].upd(x, 1); down[0].upd(x, 1);
        For (j, 1, k) {
            up[j].upd(x, mo(up[j].pre(x - 1) + down[j - 1].pre(x - 1)));
            down[j].upd(x, mo(up[j - 1].suf(x + 1) + down[j].suf(x + 1)));
        }
    }
    printf("%d", mo(up[k].suf(1) + down[k].suf(1)));
    return 0;
}
