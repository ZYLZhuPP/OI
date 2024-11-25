#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rnd(time(0));

template<class BST = ll, class VAL = ll>
class Treap {
private:
    typedef pair<BST, VAL > Pr;
    typedef struct Node {
        const ull heap;
        BST bst;
        VAL val;
        ll siz, lc, rc;

        Node(): heap(rnd()), bst(BST()), val(VAL()), siz(0), lc(0), rc(0) {}
        Node(BST bst, VAL val, ll lc = 0, ll rc = 0): heap(rnd()), bst(bst), val(val), siz(1), lc(lc), rc(rc) {}

        Pr pr() {return make_pair(bst, val);}
    } Pt;
    vector<Pt> tr;
#define heap(x) (tr[x].heap)
#define bst(x) (tr[x].bst)
#define val(x) (tr[x].val)
#define siz(x) (tr[x].siz)
#define lc(x) (tr[x].lc)
#define rc(x) (tr[x].rc)
#define pr(x) (tr[x].pr())

    ll rt, x, p;

#define goL lc(p), u, lc(p)
#define goR rc(p), rc(p), v
    
    void split_key(ll p, ll &u, ll &v, BST key) {
        if (!p) {u = v = 0; return;}
        if (bst(p) < key) {u = p; split_key(goR, key);}
        else {v = p; split_key(goL, key);}
        pushup(p);
    }

     void split_key_(ll p, ll &u, ll &v, BST key) {
        if (!p) {u = v = 0; return;}
        if (!(key < bst(p))) {u = p; split_key_(goR, key);}
        else {v = p; split_key_(goL, key);}
        pushup(p);
    }


    void split_rank(ll p, ll &u, ll &v, ll rank) {
        if (!p) {u = v = 0; return;}
        if (siz(lc(p)) + 1 <= rank) {u = p; split_rank(goR, rank - siz(lc(p)) - 1);}
        else {v = p; split_rank(goL, rank);}
        pushup(p);
    }

    ll merge(ll u, ll v) {
        if (!u) return v; if (!v) return u;
        if (heap(u) < heap(v)) {rc(u) = merge(rc(u), v); return pushup(u);}
        else {lc(v) = merge(u, lc(v)); return pushup(v);}
    }
   
    ll pushup(ll p) {siz(p) = siz(lc(p)) + siz(rc(p)) + 1; return p;}

public:
    ll n;

    Treap():rt(0), n(0) {
        tr.push_back(Pt());
    }
    
    ll size() {return siz(rt);}
    
    void insert(BST bst, VAL val) {
        tr.push_back(Pt(bst, val));
        ll ne = ++n;
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
        ll res = siz(rt) + 1;
        rt = merge(rt, x);
        return res;
    }
    
    ll count(BST bst){
        split_key(rt, rt, p, bst);
        split_key_(p, p, x, bst);
        ll res = siz(p);
        rt = merge(merge(rt, p), x);
        return res;
    }

    ll count(BST lbst, BST rbst){
        split_key(rt, rt, p, lbst);
        split_key_(p, p, x, rbst);
        ll res = siz(p);
        rt = merge(merge(rt, p), x);
        return res;
    }
    
    Pr pre(BST bst){
        split_key(rt, rt, x, bst);
        ll res = rt; if(res) while(rc(res)) res = rc(res);
        rt = merge(rt, x);
        return pr(res);
    }
    
    Pr suf(BST bst){
        split_key_(rt, x, rt, bst);
        ll res = rt; if(res) while(lc(res)) res = lc(res);
        rt = merge(x, rt);
        return pr(res);
    }
    
    const Pr operator () (ll rank){
        split_rank(rt, rt, p, rank - 1);
        split_rank(p, p, x, 1);
        ll res = p;
        rt = merge(merge(rt, p), x);
        return pr(res);
    }
    
    const VAL operator [] (BST bst) {
        split_key(rt, rt, p, bst);
        split_key_(p, p, x, bst);
        VAL res = val(p);
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
