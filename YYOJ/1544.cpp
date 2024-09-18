#include<bits/stdc++.h>
using namespace std;

const int N = 5, M = 2e5 + 5;
const int INF = 0x1f1f1f1f;

template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

int n, m, Q, x, y, xx, yy, opt;
bool g[M][N];

#define lc (p << 1)
#define rc (p <<1 | 1)
#define me p, l, r
#define Lc lc, l, mid
#define Rc rc, mid + 1, r
#define Mid int mid = ((l + r) >> 1)
#define P int p, int l, int r
#define Rt 1, 1, n

struct IO {
	char c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline IO& operator >> (bool &x) {
		while (!isdigit(c = gc()) && ~c);
		x = c ^ 48;
		return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

template<class VAL>
class SMT {
private:
    struct Node {
        VAL v;

	    Node(VAL v = VAL()): v(v) {}
	    
	    Node operator + (const Node &x) {
	    	return Node(v + x.v);
	    }
    };
	vector<Node > tr;
	
	void pushup(P) { tr[p] = tr[lc] + tr[rc]; }

	void build(P, VAL a[]) {
		if (l == r) return (void)(tr[p] = Node(a[l]));
		Mid; build(Lc, a); build(Rc, a);
		pushup(me);
	}

public:
	int n;
	
	SMT(int n, VAL a[]): n(n) {
		tr.reserve((n << 2) + 1);
        build(Rt, a);
	}

    ~SMT() {vector<Node > ().swap(tr);}
	
	void pt_modify(P, int goal, VAL ne) {
	    if (goal < l || r < goal) return;
	    if (l == r) {tr[p].v = ne; return;}
	    Mid; pt_modify(Lc, goal, ne); pt_modify(Rc, goal, ne);
	    pushup(me);
	}
	
	VAL range_query(P, int L, int R) {
		if (r < L || R < l) return VAL();
    	if (L <= l && r <= R) return tr[p].v;
    	Mid; return range_query(Lc, L, R) + range_query(Rc, L, R);
	}
};

struct A55 {
    int v[5][5];
    A55(int x = 0) {memset(v, 31, sizeof(v)); for (int i = 0; i < n; ++i) v[i][i] = x;}
    A55(bool g[]) {
        memset(v, 31, sizeof(v));
        for (int i = 0; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                if (g[j]) v[i][j] = i - j;
                else break;
            }
            for (int j = i; j < n; ++j) {
                if (g[j]) v[i][j] = j - i;
                else break;
            }
        }
    }

    A55 operator + (const A55 &x) const {
        A55 res(INF);
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) 
                for (int k = 0; k < n; ++k)
                    chkmin(res.v[i][j], v[i][k] + x.v[k][j]);
        return res;
    }
}a[M];

int main() {
    io >> n >> m >> Q;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) io >> g[j][i];
    }

    for (int i = 1; i <= m; ++i) a[i] = A55(g[i]);

    SMT<A55 > smt(m, a);

    while (Q--) {
        io >> opt;
        if (opt == 1) {
            io >> x >> y; x--;
            g[y][x] ^= 1;
            smt.pt_modify(1, 1, m, y, A55(g[y]));
        } else {
            io >> x >> y >> xx >> yy; x--; xx--;
            int ans = smt.range_query(1, 1, m, y, yy).v[x][xx];
            if (ans >= INF) puts("-1");
            else printf("%d\n", ans + yy - y);
        }
    }

	return 0;
}
