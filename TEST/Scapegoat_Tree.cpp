#include<bits/stdc++.h>
using namespace std;

const int N = 7e4 + 5;

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

typedef double lf;
lf mp[N];
namespace SGT { //use SGT to maintain dynamic labels
    const lf alp = 0.75, inf = 1e9;
    int rt, tot, id[N], len;
    struct Node {
        int l, r, sz; lf v;
        Node() { l = r = sz = v = 0; }
        Node(lf v): v(v) { l = r = 0; sz = 1; }
    } o[N];
#define ls o[p].l
#define rs o[p].r
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; }
    inline void pia(int p) { if (!p) return; pia(ls); id[++len] = p; pia(rs); }
    inline void build(int &p, int l, int r, lf L = 0, lf R = inf) {
        if (r < l) return void(p = 0);
        int m = (l + r) >> 1; p = id[m];
        lf M = (L + R) / 2; o[p] = Node(mp[p] = M);
        build(ls, l, m - 1, L, M); build(rs, m + 1, r, M, R); up(p);
    }
    inline int ins(int &p, const int &k, lf L = 0, lf R = inf) {
        lf M = (L + R) / 2;
        if (!p) return p = ++tot, o[p] = Node(mp[p] = M), p;
        int res = o[ls].sz>=k? ins(ls, k, L, M): ins(rs, k - o[ls].sz - 1, M, R); up(p);
        if (max(o[ls].sz, o[rs].sz) > alp * o[p].sz) len = 0, pia(p), build(p, 1, len, L, R);
        return res;
    }
    inline int kth(int p, int k) {
        if (o[ls].sz >= k) return kth(ls, k);
        else { k -= o[ls].sz + 1; return k? kth(rs, k): p; }
    }
}
using namespace SGT;

int main() {
    return 0;
}
