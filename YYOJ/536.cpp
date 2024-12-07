#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int q;

template<class T, class TT>
class Treap{
    typedef long long ll;
    typedef unsigned long long ull;

private:
    struct Pt{
        ull heap;
        T bst;
        TT val;
        ll lc,rc,siz;
        Pt():siz(0){}
        Pt(ull heap_, T bst_, TT val_):heap(heap_),bst(bst_),val(val_),lc(0),rc(0),siz(1){}
    };
    vector<Pt> tr;
#define heap(x) (tr[x].heap)
#define bst(x) (tr[x].bst)
#define val(x) (tr[x].val)
#define lc(x) (tr[x].lc)
#define rc(x) (tr[x].rc)
#define siz(x) (tr[x].siz)
    ll rt;

    ull get_rand(){return (ull)rand()*rand()+rand();}
    
    ll new_pt(T bst, TT val){tr.push_back(Pt(get_rand(),bst,val)); return ++maid;}
    
    void split_key(ll p, T key, ll &u, ll &v){
        if(!p) {u=v=0; return;}
        if(bst(p)<key) {u=p; split_key(rc(u), key, rc(u), v);}
        else {v=p; split_key(lc(v), key, u, lc(v));}
        pushup(p);
    }
    
    void split_key_(ll p, T key, ll &u, ll &v){
        if(!p) {u=v=0; return;}
        if(bst(p)<=key) {u=p; split_key_(rc(u), key, rc(u), v);}
        else {v=p; split_key_(lc(v), key, u, lc(v));}
        pushup(p);
    }
    
    void split_rank(ll p, T rank, ll &u, ll &v){
        if(!p) {u=v=0; return;}
        if(siz(lc(p))+1<=rank) {u=p; split_rank(rc(u), rank-siz(lc(p))-1, rc(u), v);}
        else {v=p; split_rank(lc(v), rank, u, lc(v));}
        pushup(p);
    }
    
    ll merge(ll u, ll v){
        ll ret;
        if(!u || !v) ret=u+v;
        else if(heap(u)<heap(v)) {ret=u; rc(u)=merge(rc(u), v);}
        else {ret=v; lc(v)=merge(u, lc(v));}
        pushup(ret);
        return ret; 
    }

    void pushup(ll p){siz(p)=siz(lc(p))+siz(rc(p))+1;}

public:
    ll maid;

    Treap():rt(0),maid(0){
        srand(time(0));
        tr.push_back(Pt());
    }
    
    ll size(){return tr[rt].siz;}
    
    void insert(T bst, TT val){
        ll x, ne=new_pt(bst, val);
        split_key_(rt, bst, rt, x);
        rt=merge(merge(rt, ne), x);
    }
    
    void erase_key(T lbst, T rbst){
        ll x,p;
        split_key(rt, rbst, rt, x);
        split_key_(rt, lbst, rt, p);
        rt=merge(rt, x);
    }
    
    void erase_rank(ll lrank, ll rrank){
        ll x,p;
        split_rank(rt, rrank, rt, x);
        split_rank(rt, lrank-1, rt, p);
        rt=merge(rt, x);
    }
    
    void erase_key(T bst){erase_key(bst, bst);}
    
    void erase_rank(ll rank){erase_rank(rank, rank);}
    
    ll rank(T bst){
        ll x;
        split_key(rt, bst, rt, x);
        ll ret=siz(rt)+1;
        rt=merge(rt, x);
        return ret;
    }
    
    ll count(T bst){
        ll x,p;
        split_key_(rt, bst, rt, x);
        split_key(rt, bst, rt, p);
        ll ret=siz(p);
        rt=merge(merge(rt, p), x);
        return ret;
    }
    
    T pre(T bst){
        ll x;
        split_key(rt, bst, rt, x);
        ll ret=rt;
        while(rc(ret)) ret=rc(ret);
        rt=merge(rt, x);
        return bst(ret);
    }
    
    T suf(T bst){
        ll x;
        split_key_(rt, bst, x, rt);
        ll ret=rt;
        while(lc(ret)) ret=lc(ret);
        rt=merge(x, rt);
        return bst(ret);
    }
    
    T number(ll rank){
        ll x,p;
        split_rank(rt, rank, rt, x);
        split_rank(rt, rank-1, rt, p);
        ll ret=p;
        rt=merge(merge(rt, p), x);
        return bst(ret);
    }
    
    const TT operator[](T bst){
        ll x,p;
        split_key_(rt, bst, rt, x);
        split_key(rt, bst, rt, p);
        ll ret=p;
        rt=merge(merge(rt, p), x);
        return val(ret);
    }
    
    const T operator+(ll rank){return number(rank);}
    
};

int main(){
	Treap<int, int > t;
	io>>q;
	while(q--){
		int k,x;
		io>>k>>x;
		if(k==1) t.insert(x, x);
		else if(k==2) t.erase_rank(t.rank(x));
		else if(k==3) printf("%lld\n", t.rank(x));
		else if(k==4) printf("%d\n", t+x);
		else if(k==5) printf("%d\n", t.pre(x));
		else printf("%d\n", t.suf(x));
	}
    return 0;
}
