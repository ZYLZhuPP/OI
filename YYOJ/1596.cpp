#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5;

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
	inline IO& operator >> (char &x){
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline IO& operator >> (char *x){
		while ((c = gc()) < 33 && ~c);
		while (c > 32) *x++ = c, c = gc();
		*x = 0; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, q, x;
char c, st[N];

struct Node {
    int s0, s1, s;
    Node() { s0 = s1 = s = 0; }
    Node(int x) {
        s0 = x == 0;
        s1 = x == 1;
        s = 0;
    }
    Node operator + (const Node &x) const {
        Node res;
        res.s0 = s0 + x.s0;
        res.s1 = s1 + x.s1;
        res.s = min(s + x.s0, s1 + x.s);
        return res;
    }
};

struct seg {
    int lim; char ch;
    vector<Node > o;
    void init() {
        for (lim = 1; lim < n; lim <<= 1);
        o.resize(lim << 1);
        For (i, 0, n - 1) o[lim + i] = Node(st[i] > ch);
        rFor (i, lim - 1, 1) o[i] = o[i << 1] + o[i << 1 | 1];
    }
    void upd(int x, int c) {
        x += lim;
        o[x] = Node(c > ch);
        while (x >>= 1) o[x] = o[x << 1] + o[x << 1 | 1];
    }
} tr[25];

void init() { For (i, 0, 24) tr[i].ch = 'a' + i, tr[i].init(); }
void upd(int x, int c) { For (i, 0, 24) tr[i].upd(x, c); }
int solve() {
    int res = 0;
    For (i, 0, 24) res += tr[i].o[1].s;
    return res;
}

int main() {
    io >> st; n = strlen(st);
    init();
    printf("%d\n", solve());

    io >> q;
    while (q--) {
        io >> x >> c; x--;
        upd(x, c);
        printf("%d\n", solve());
    }

    return 0;
}
