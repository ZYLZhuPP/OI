#include<bits/stdc++.h>
using namespace std;

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
	inline bool operator ~ () {return ~c;}
}io;

template<class VAL>
class SMT {
private:
    struct Node {
        bool tag;
        VAL v, tagv;

	    Node(VAL v = VAL(), bool tag = 0, VAL tagv = VAL()): tag(tag), v(v), tagv(tagv) {}
	    
	    Node operator + (const Node &x) {
	    	return Node(v + x.v);
	    }

    	void mark(VAL tagv) { v = this->tagv = tagv; tag = 1; }
    };
	vector<Node > tr;
	
	void pushup(P) { tr[p] = tr[lc] + tr[rc]; }
	
	void pushdown(P) {
        if (tr[p].tag) {
    		tr[lc].mark(tr[p].tagv); tr[rc].mark(tr[p].tagv);
            tr[p].tag = 0;
        }
	}

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
	

	void rebuild(int n, VAL a[]) {
		tr.resize((n << 2) + 1);
		build(Rt, a);
	}
	
	void range_modify(P, int L, int R, VAL x) {
		if (r < L || R < l) return;
   		if (L <= l && r <= R) return tr[p].mark(x);
    	pushdown(me);
    	Mid; range_modify(Lc, L, R, x); range_modify(Rc, L, R, x);
    	pushup(me);
	}
	
	VAL range_query(P, int L, int R) {
		if (r < L || R < l) return VAL();
    	if (L <= l && r <= R) return tr[p].v;
    	pushdown(me);
    	Mid; return range_query(Lc, L, R) + range_query(Rc, L, R);
	}
};

class MAX {
public:
    int v;
    MAX(int v = 0): v(v) {}
    MAX operator + (const MAX &x) const {
        return MAX(max(v, x.v));
    }
};

int main() {
    int n;
    io >> n;
    MAX a[n + 1];
    for (int i = 1; i <= n; ++i) {
        int x;
        io >> x;
        a[i] = MAX(x);
    }

    SMT<MAX > seg(n, a);
    
    while (1) {
        int op;
        io >> op;
        if (!op) break;
        if (op == 1) {
            int l, r, x;
            io >> l >> r >> x;
            seg.range_modify(Rt, l, r, MAX(x));
        }
        if (op == 2) {
            int l, r;
            io >> l >> r;
            cout << seg.range_query(Rt, l, r).v;
        }
    }

	return 0;
}
