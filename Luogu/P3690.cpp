#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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

struct LCT{
    ll fa, son[2], val, tag;
};
vector<LCT> tr;
#define fa(x) (tr[x].fa)
#define son(x,y) (tr[x].son[y])
#define lc(x) (tr[x].son[0])
#define rc(x) (tr[x].son[1])
#define val(x) (tr[x].val)
#define tag(x) (tr[x].tag)

ll n, m;
vector<ll> a;

bool isroot(ll p) {
    ll f = fa(p);
    return !f || (lc(f) ^ p && rc(f) ^ p);
}

void mark_swap(ll p) { if(p) swap(lc(p), rc(p)), tag(p) ^= 1; }

void pushup(ll p) { val(p) = val(lc(p)) ^ val(rc(p)) ^ a[p]; }

void pushdown(ll p) {
    if (tag(p)) 
		mark_swap(lc(p)), mark_swap(rc(p)), tag(p) = 0;
}

bool isson(ll p) { return p ^ son(fa(p), 0); }

void rotate(ll p) {
    ll s = isson(p), f = fa(p), ff = fa(f), pc = son(p, !s);
    if (!isroot(f)) son(ff, isson(f)) = p; son(p, !s) = f; son(f, s) = pc;
    if (pc) fa(pc) = f; fa(p) = ff; fa(f) = p;
    pushup(f); pushup(p);
}

void pushall(int p) {
	if (!isroot(p))
		pushall(fa(p));
	pushdown(p);
}

void splay(ll p) {
    pushall(p);
    for (ll f; f = fa(p), !isroot(p); rotate(p)) 
		if(!isroot(f)) 
			rotate(isson(p) ^ isson(f)? p: f);
}

void access(ll p) {
    for (ll x = 0; p; p = fa(x = p)) 
		splay(p), rc(p) = x, pushup(p);
}

void makeroot(ll p) {
    access(p); splay(p); mark_swap(p);
}

ll findroot(ll p) {
    access(p); splay(p); pushdown(p);
    while (lc(p)) 
		pushdown(p = lc(p));
    splay(p);
    return p;
}

void link(ll u, ll v) {
    makeroot(u);
    if (findroot(v) ^ u) 
		fa(u) = v;
}

void cut(ll u, ll v) {
	makeroot(u);
	if (findroot(v) == u && fa(v) == u && !rc(v)) {
		fa(v) = lc(u) = 0;
		pushup(u);
	}
}

void pick(ll u, ll v) {
    makeroot(u); access(v); splay(v);
}

void init() {
    tr.reserve(n + 1);
    a.reserve(n + 1);
}

int main() {
    io >> n >> m;
    init();
    for (int i = 1; i <= n; i++) 
		io >> a[i];
		
    while (m--) {
        ll k, u, v;
        io >> k >> u >> v;
        switch (k) {
        case 0:
            pick(u, v); 
			printf("%lld\n", val(v)); 
			break;
        case 1:
            link(u, v); 
			break;
        case 2:
            cut(u, v); 
			break;
        case 3:
        	splay(u);
        	a[u] = v; 
        	break;
        }
    }
    
    return 0;
}
