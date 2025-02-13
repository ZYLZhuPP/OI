#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 4e5 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, q, op[N], to[N], tot;
ll x[N], y[N], w;
pair<ll, int > b[N];

class Tree {
public:
    struct Node { 
        int no, cd, c; ll s, mx; 
        Node (int no = 0, int cd = 0, int c = 0, ll s = 0, ll mx = 0):
            no(no), cd(cd), c(c), s(s), mx(mx) { }
    } v[N << 2];
    bool now[N];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void pushup(int p) {
        v[p].c = v[ls].c + v[rs].c;
        v[p].s = v[ls].s + v[rs].s;
        v[p].mx = max(v[ls].mx, v[rs].mx);
    }
    public:
    Tree() { memset(now, 0, sizeof(now)); }
    void flip(int p, int l, int r, int x) {
        if (x < l || x > r) return;
        if (l == r) {
            v[p].c = (now[x] ^= 1);
            v[p].mx = v[p].s = now[x] * b[x].st;
            return;
        }
        M; flip(goL, x); flip(goR, x);
        pushup(p);
    }
    void off(int p, int l, int r, int x, int y) {
        if (y < l || x > r) return;
        v[p].cd = 1;
        if (x <= l && r <= y) { v[p] = Node(1, 1, 0, 0, 0); return; }
        M; off(goL, x, y); off(goR, x, y);
        pushup(p);
    }
    void on(int p, int l, int r) {
        if (!v[p].cd) return;
        v[p].no = v[p].cd = 0;
        if (l == r) {
            v[p].c = now[l];
            v[p].mx = v[p].s = now[l] * b[l].st;
            return;
        }
        M; on(goL); on(goR);
        pushup(p);
    }
    int query(int p, int l, int r, int x, ll &s, int &c, ll aim) const {
        if (l > x || v[p].no) return -1;
        if (r <= x) if (v[p].s + s < aim) { s += v[p].s; c += v[p].c; return -1; }
        if (l == r) { s += v[p].s; c += v[p].c; return l; }
        M;
        int res = query(goR, x, s, c, aim);
        if (~res) return res;
        return query(goL, x, s, c, aim);
    }
    int suf(int p, int l, int r, ll x) const {
            //cout << v[p].mx << " " << x << endl;
        if (v[p].no || v[p].mx < x) return -1;
        if (l == r) return l;
        M;
        int res = suf(goL, x);
        if (~res) return res;
        return suf(goR, x);
    }
} tr;

int solve(ll x, ll y) {
    int ans = 0;
    while (x < y) {
        ll aim = y;
        int nxt = tr.suf(1, 1, tot, x);
        //cout << nxt << endl;
        if (nxt == 1) { ans = -1; break; }
        if (nxt == -1) nxt = tot + 1;
        if (nxt <= tot) aim = min(aim, b[nxt].st + 1);
        int pos = tr.query(1, 1, tot, nxt - 1, x, ans, aim);
        //cout << x << endl;
        if (pos == -1) { ans = -1; break; }
        tr.off(1, 1, tot, pos, nxt - 1);
    }
    tr.on(1, 1, tot);
    return ans;
}

int main() {
    io >> n;
    For (i, 1, n) io >> w, b[++tot] = mkp(w, i);
    io >> q;
    For (i, 1, q) {
        io >> op[i];
        if (op[i] == 1) io >> x[i] >> y[i];
        else {
            io >> x[i];
            if (op[i] == 2) b[++tot] = mkp(x[i], n + i);
        }
    }
    sort(b + 1, b + tot + 1);
    For (i, 1, tot) to[b[i].nd] = i;
    For (i, 1, n) tr.flip(1, 1, tot, to[i]);

    For (i, 1, q) {
        if (op[i] == 1) printf("%d\n", solve(x[i], y[i]));
        else if (op[i] == 2) tr.flip(1, 1, tot, to[n + i]);
        else tr.flip(1, 1, tot, tr.suf(1, 1, tot, x[i]));
    }

    return 0;
}
