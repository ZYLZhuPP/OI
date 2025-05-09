#include<bits/stdc++.h>
#define lc (p<<1)
#define rc (p<<1|1)
#define mid ((l + r) >> 1)
const int inf = 1e9;
const int N = 5e5+5;
using namespace std;
struct node{
    int pre, suf, ans, sum;
}tr[N<<2];
int n, m, a[N];
void pushup(int p){
    tr[p].pre = max(tr[lc].pre, tr[lc].sum + tr[rc].pre);
    tr[p].suf = max(tr[rc].suf, tr[rc].sum + tr[lc].suf);
    tr[p].ans = max({tr[lc].ans, tr[rc].ans, tr[lc].suf + tr[rc].pre});
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}
void upd(int p, int l, int r, int pos){
    if(pos < l || pos > r) return;
    if(l == r) return tr[p].pre = tr[p].suf = tr[p].ans = tr[p].sum = a[l], void();
    upd(lc, l, mid, pos), upd(rc, mid + 1, r, pos);
    pushup(p);
}
void build(int p, int l, int r){
    if(l == r) return tr[p] = node{a[l], a[l], a[l], a[l]}, void();
    build(lc, l, mid), build(rc, mid + 1, r);
    pushup(p);
}
node query(int p, int l, int r, int L, int R){
    if(r < L || R < l) return node{-inf, -inf, -inf, 0};
    if(l >= L && r <= R)
        return tr[p];
    node res, a1, a2;
    a1 = query(lc, l, mid, L, R);
    a2 = query(rc, mid + 1, r, L, R);
    res.pre = max(a1.pre, a1.sum + a2.pre);
    res.suf = max(a2.suf, a2.sum + a1.suf);
    res.ans = max({a1.ans, a2.ans, a1.suf + a2.pre});
    res.sum = a1.sum + a2.sum;
    return res;
}
signed main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    while(m--){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1){
            if(x > y) swap(x, y);
            cout << query(1, 1, n, x, y).ans << endl;
        }
        else{
            a[x] = y;
            upd(1, 1, n, x);
        }
    }
    return 0;
}
