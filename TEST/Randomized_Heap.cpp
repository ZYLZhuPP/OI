#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) f|=-!(c^45);
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

typedef struct Node {
	int val, pos;
	Node *lc, *rc, *fa;
	Node(int val, int pos, Node *lc = nullptr, Node *rc = nullptr, Node *fa = nullptr): val(val), pos(pos), lc(lc), rc(rc), fa(fa) {}
	bool operator < (const Node &x) const {
		return val^x.val? val<x.val: pos<x.pos;
	}
}Pt, *pPt;

int n, m, fa[N];
pPt tr[N];
bool out[N];

pPt merge(pPt u, pPt v) {
	if (!u || !v)
		return u? u: v;
	if (*v < *u)
		swap(u, v);
	if (rand() & 1)
		swap(u->lc, u->rc);
	u->lc = merge(u->lc, v);
	return u->lc->fa = u;
}

int getRt(int u) {
	return ~fa[u]? fa[u] = getRt(fa[u]): u; 
}

pPt &isson(pPt u) {
	return u->fa->lc == u? u->fa->lc: u->fa->rc;
}

void erase(pPt u) {
	if (u->lc || u->rc) {
		pPt v = merge(u->lc, u->rc);
		if (u->fa) 
			isson(u) = v;
		v->fa = u->fa;
		fa[v->pos] = fa[u->pos];
		fa[u->pos] = v->pos;
	}
	tr[u->pos] = nullptr;
	out[u->pos] = 1;
	delete u;
}

int main() {
	srand(time(0));
	io >> n >> m;
	for (int i = 1; i <= n; i++) {
		fa[i] = -1;
		int x;
		io >> x;
		tr[i] = new Pt(x, i);
	}
	
	while (m--) {
		int opt;
		io >> opt;
		if (opt == 1) {
			int u, v;
			io >> u >> v;
			if (!out[u] && !out[v]) {
				int fu = getRt(u), fv = getRt(v);
				if (fu != fv) {
					if (*tr[fv] < *tr[fu])
						swap(fu, fv);
					merge(tr[fu], tr[fv]);
					fa[fv] = fu;
				}
			}
		} else {
			int u;
			io >> u;
			if (!out[u]) {
				int rt = getRt(u);
				printf("%d\n", tr[rt]->val);
				erase(tr[rt]);
			} else {
				puts("-1");
			}
		}
	}
	return 0;
} 
