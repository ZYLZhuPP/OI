#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

namespace LT {
    struct Node {
        int l, r, d;
        ll v, ad, mu;
        Node(ll v = 0): v(v) { l = r = d = ad = 0; mu = 1; }
    } o[N];
    int tot;
#define ls o[p].l
#define rs o[p].r
    inline void up(int p) { if (o[ls].d < o[rs].d) swap(ls, rs); o[p].d = o[rs].d + 1; }
    inline void mark(int p, ll ad, ll mu) { (o[p].v *= mu) += ad; o[p].mu *= mu; o[p].ad *= mu; o[p].ad += ad; }
    inline void down(int p) { if (o[p].ad || o[p].mu ^ 1) mark(ls, o[p].ad, o[p].mu), mark(rs, o[p].ad, o[p].mu), o[p].ad = 0, o[p].mu = 1; }
    inline int merge(int p, int q) {
        if (!p || !q) return p | q;
        if (o[q].v < o[p].v) swap(p, q);
        down(p); rs = merge(rs, q); up(p);
        return p;
    }
    inline void ins(int &p, int v) {
        int q = ++tot; o[q] = Node(v);
        p = merge(p, q);
    }
    inline void pop(int &p) {
        down(p); p = merge(ls, rs);
    }
}
using namespace LT;

int main() {

    return 0;
}
