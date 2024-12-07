#include<bits/stdc++.h>
using namespace std;

class SMT {
#define lc (p << 1)
#define rc (p <<1 | 1)
#define me p, l, r
#define ls lc, l, mid
#define rs rc, mid + 1, r
#define Mid int mid = ((l + r) >> 1)
#define P int p, int l, int r
public:
	typedef struct Node {
		bool use;
		int lco, rco, sum, tag;
		
		Node(bool use, int lco = -1, int rco = -1, int sum = 0, int tag = -1): use(use), lco(lco), rco(rco), sum(sum), tag(tag) {}
		
		Node operator + (const Node &x) {
			return !use? x: (!x.use? (*this):
				Node(1, lco, x.rco, sum + x.sum + (~rco && rco == x.lco)));
		}
		
		void update(P, int tag) { lco = rco = this->tag = tag; sum = r - l; }
	} Pt;

private:
	vector<Node > tr;
	
	void pushup(P) { tr[p] = tr[lc] + tr[rc]; }
	
	void pushdown(P) {
		Mid; int &tag = tr[p].tag;
		if (~tag) {
			tr[lc].update(ls, tag);
			tr[rc].update(rs, tag);
			tag=-1;
		}
	}
	
public:
	const int maxn;
	
	SMT(int maxn): maxn(maxn) {
		tr.reserve((maxn << 2) + 1);
	}
	
	void build(P) {
		if (l == r) return (void)(tr[p] = Pt(1));
		Mid;
		build(ls); build(rs);
		pushup(me);
	}
	
	void rebuild(int n) {
		tr.resize((n << 2) + 1, Pt(0));
		build(1, 1, n);
	}
	
	void range_modify(P, int L, int R, int co) {
		if (r < L || R < l) return;
   		if (L <= l && r <= R) return tr[p].update(me, co);
    	Mid;
    	pushdown(me);
    	range_modify(ls, L, R, co); range_modify(rs, L, R, co);
    	pushup(me);
	}
	
	Node range_query(P, int L, int R) {
		if (r < L || R < l) return Node(0);
    	if (L <= l && r <= R) return tr[p];
    	Mid; Node res(0);
    	pushdown(me);
    	res = range_query(ls, L, R) + range_query(rs, L, R);
    	return res;
	}
} tr(100);

int main() {
	tr.build(1, 1, 100);
	tr.range_modify(1, 1, 100, 1, 10, 1);
	tr.range_modify(1, 1, 100, 3, 5, 2);
	SMT:: Node a = tr.range_query(1, 1, 100, 2, 20);
	cout << a.sum;
	return 0;
}
