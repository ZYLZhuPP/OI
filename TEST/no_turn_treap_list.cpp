#include<bits/stdc++.h>
using namespace std;

#define p0 nullptr

typedef long long ll;
typedef unsigned long long ull;

mt19937 rnd(time(0));

template<class BST = ll, class VAL = ll>
class Treap {
private:
    typedef pair<BST, VAL > Pr;
    typedef struct Node {
        const ull heap;
        BST bst;
        VAL val;
        ll siz;
        Node *lc, *rc;

        Node(): heap(rnd()), bst(BST()), val(VAL()), siz(0), lc(p0), rc(p0) {}
        Node(BST bst, VAL val, Node *lc = p0, Node *rc = p0): heap(rnd()), bst(bst), val(val), siz(1), lc(lc), rc(rc) {}

        Pr pr() {return make_pair(bst, val);}
    } *pN;
    pN rt, x, p;

#define goL p->lc, u, p->lc
#define goR p->rc, p->rc, v
#define v(p, a) (p? p->a: 0ll)
#define P(p) (p? p->pr(): make_pair(0ll, 0ll))

    void split_key(pN p, pN &u, pN &v, BST key) {
        if (!p) {u = v = p0; return;}
        if (p->bst < key) {u = p; split_key(goR, key);}
        else {v = p; split_key(goL, key);}
        pushup(p);
    }

     void split_key_(pN p, pN &u, pN &v, BST key) {
        if (!p) {u = v = p0; return;}
        if (!(key < p->bst)) {u = p; split_key_(goR, key);}
        else {v = p; split_key_(goL, key);}
        pushup(p);
    }


    void split_rank(pN p, pN &u, pN &v, ll rank) {
        if (!p) {u = v = p0; return;}
        if (v(p->lc, siz) + 1 <= rank) {u = p; split_rank(goR, rank - v(p->lc, siz) - 1);}
        else {v = p; split_rank(goL, rank);}
        pushup(p);
    }

    pN merge(pN u, pN v) {
        if (!u) return v; if (!v) return u;
        if (u->heap < v->heap) {u->rc = merge(u->rc, v); return pushup(u);}
        else {v->lc = merge(u, v->lc); return pushup(v);}
    }
   
    pN pushup(pN p){p->siz = v(p->lc, siz) + v(p->rc, siz) + 1; return p;}

public:

    Treap() {
        rt = x = p = p0;
    }
    
    ll size() {return rt->siz;}
    
    void insert(BST bst, VAL val) {
        pN ne = new Node(bst, val);
        split_key(rt, rt, x, bst);
        rt = merge(merge(rt, ne), x);
    }
    
    void erase_key(BST lbst, BST rbst) {
        split_key(rt, rt, p, lbst);
        split_key_(p, p, x, rbst);
        rt = merge(rt, x);
    }
    
    void erase_rank(ll lrank, ll rrank) {
        split_rank(rt, rt, p, lrank - 1);
        split_rank(p, p, x, rrank-lrank+1);
        rt = merge(rt, x);
    }
    
    void erase_key(BST bst){erase_key(bst, bst);}
    
    void erase_rank(ll rank){erase_rank(rank, rank);}
    
    ll rank(BST bst){
        split_key(rt, rt, x, bst);
        ll res = v(rt, siz) + 1;
        rt = merge(rt, x);
        return res;
    }
    
    ll count(BST bst){
        split_key(rt, rt, p, bst);
        split_key_(p, p, x, bst);
        ll res = v(p, siz);
        rt = merge(merge(rt, p), x);
        return res;
    }

    ll count(BST lbst, BST rbst){
        split_key(rt, rt, p, lbst);
        split_key_(p, p, x, rbst);
        ll res = v(p, siz);
        rt = merge(merge(rt, p), x);
        return res;
    }
    
    Pr pre(BST bst){
        split_key(rt, rt, x, bst);
        pN res = rt; if(res) while(res->rc) res = res->rc;
        rt = merge(rt, x);
        return P(res);
    }
    
    Pr suf(BST bst){
        split_key_(rt, x, rt, bst);
        pN res = rt; if(res) while(res->lc) res = res->lc;
        rt = merge(x, rt);
        return P(res);
    }
    
    const Pr operator () (ll rank){
        split_rank(rt, rt, p, rank - 1);
        split_rank(p, p, x, 1);
        pN res = p;
        rt = merge(merge(rt, p), x);
        return P(res);
    }
    
    const VAL operator [] (BST bst) {
        split_key(rt, rt, p, bst);
        split_key_(p, p, x, bst);
        VAL res = v(p, val);
        rt = merge(merge(rt, p), x);
        return res;
    }    
};

int main(){
    Treap<> tr;
    tr.insert(1, 2);
    tr.insert(2, 3);
    tr.insert(3, 4);
    cout << tr.count(4) << endl;
    cout << tr.count(1, 3) << endl;
    cout << tr.suf(5).second << endl;
    return 0;
}
