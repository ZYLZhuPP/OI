#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class Treap{
    typedef long long ll;
    typedef unsigned long long ull;

private:
    struct Pt{
        ull heap;
        ll bst,val,lc,rc,siz;
        Pt():siz(0){}
        Pt(ull heap_, ll bst_, ll val_):heap(heap_),bst(bst_),val(val_),lc(0),rc(0),siz(1){}
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
    ll new_pt(ll bst, ll val);
    void split_key(ll p, ll key, ll &u, ll &v);
    void split_rank(ll p, ll rank, ll &u, ll &v);
    ll merge(ll u, ll v);
    void pushup(ll p);

public:
    ll maid;

    Treap():rt(0),maid(0){
        srand(time(0));
        tr.push_back(Pt());
    }
    ll size(){return tr[rt].siz;}
    void insert(ll bst, ll val);
    void insert(ll val);
    void erase_key(ll lbst, ll rbst);
    void erase_key(ll bst);
    void erase_rank(ll lrank, ll rrank);
    void erase_rank(ll rank);
    ll rank(ll bst);
    ll count(ll bst);
    ll pre(ll bst);
    ll suf(ll bst);
    ll number(ll rank);
    const ll operator[](ll bst);
    const ll operator+(ll rank);

};

ll Treap:: new_pt(ll bst, ll val){tr.push_back(Pt(get_rand(),bst,val)); return ++maid;}

void Treap:: split_key(ll p, ll key, ll &u ,ll &v){
    if(!p) {u=v=0; return;}
    if(bst(p)<=key) {u=p; split_key(rc(u), key, rc(u), v);}
    else {v=p; split_key(lc(v), key, u, lc(v));}
    pushup(p);
}

void Treap:: split_rank(ll p, ll rank, ll &u ,ll &v){
    if(!p) {u=v=0; return;}
    if(siz(lc(p))+1<=rank) {u=p; split_rank(rc(u), rank-siz(lc(p))-1, rc(u), v);}
    else {v=p; split_rank(lc(v), rank, u, lc(v));}
    pushup(p);
}

ll Treap:: merge(ll u, ll v){
    ll ret;
    if(!u || !v) ret=u+v;
    else if(heap(u)<heap(v)) {ret=u; rc(u)=merge(rc(u), v);}
    else {ret=v; lc(v)=merge(u, lc(v));}
    pushup(ret);
    return ret; 
}

void Treap:: pushup(ll p){siz(p)=siz(lc(p))+siz(rc(p))+1;}

void Treap:: insert(ll bst, ll val){
    ll x,y,ne=new_pt(bst, val);
    split_key(rt, bst, x, y);
    rt=merge(merge(x, ne), y);
}

void Treap:: insert(ll val){insert(val ,val);}

const ll Treap:: operator[](ll bst){
    ll x,p;
    split_key(rt, bst-1, rt, p);
    split_key(p, bst, p, x);
    ll ret=val(p);
    rt=merge(merge(rt, p), x);
    return ret;
}

const ll Treap:: operator+(ll rank){return number(rank);}

ll Treap:: rank(ll bst){
    ll x;
    split_key(rt, bst-1, rt, x);
    ll ret=siz(rt)+1;
    rt=merge(rt, x);
    return ret;
}

ll Treap:: count(ll bst){
    ll x,p;
    split_key(rt, bst-1, rt, p);
    split_key(p, bst, p, x);
    ll ret=siz(p);
    rt=merge(merge(rt, p), x);
    return ret;
}

ll Treap:: pre(ll bst){
    ll x;
    split_key(rt, bst-1, rt, x);
    ll ret=rt;
    while(rc(ret)) ret=rc(ret);
    rt=merge(rt, x);
    return bst(ret);
}

ll Treap:: suf(ll bst){
    ll x;
    split_key(rt, bst, x, rt);
    ll ret=rt;
    while(lc(ret)) ret=lc(ret);
    rt=merge(x, rt);
    return bst(ret);
}

void Treap:: erase_key(ll lbst, ll rbst){
    ll x,p;
    split_key(rt, lbst-1, rt, p);
    split_key(p, rbst, p, x);
    rt=merge(rt, x);
}

void Treap:: erase_rank(ll lrank, ll rrank){
    ll x,p;
    split_rank(rt, lrank-1, rt, p);
    split_rank(p, rrank-lrank+1, p, x);
    rt=merge(rt, x);
}
    
void Treap:: erase_key(ll bst){erase_key(bst, bst);}
   
void Treap:: erase_rank(ll rank){erase_rank(rank, rank);}

ll Treap:: number(ll rank){
    ll x,p;
    split_rank(rt, rank-1, rt, p);
    split_rank(p, 1, p, x);
    ll ret=bst(p);
    rt=merge(merge(rt, p), x);
    return ret;
}

int main(){
    Treap a;
    ll n;
    cin>>n;
    for(int i=1; i<=n; i++){
        a.insert(i, i+2);
    }
    a.insert(5, 5);
    a.erase_key(1,3);
    cout<<a[5]<<endl;
    cout<<a.rank(7)<<endl;
    cout<<a+1<<endl;
    return 0;
}
