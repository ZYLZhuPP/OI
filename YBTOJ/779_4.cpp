#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int M = 250, N = 5e4 + 5;
inline bool cmax(int &x, const int &y) { return y>x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

struct Node {
    int g, s;
    Node(int _g = 0, int _s = 0) : g(_g), s(_s) { }
    bool operator < (const Node &a) const { return g < a.g; }
} v[M][N], pr[M][M], sf[M][M];
vector<Node > o;

int n, m, B, be[N], bl[N], br[N], d[N], li[N], s[N], f[M][M][M];

inline int S(int l, int r) { return s[r] - s[l - 1]; }
inline int G(int L, int R) { return f[be[L]][L - bl[be[L]]][R - bl[be[L]]]; }

int st[N], tp;
void Sort(Node f[]) {
    sort(o.begin(), o.end());
    tp = 0;
    For (i, 0, (int)o.size() - 1) {
        while (tp && o[i].s >= o[st[tp]].s) --tp;
        st[++tp] = i;
    }
    f[0].s = tp; For (i, 1, tp) f[i] = o[st[i]];
    o.resize(0);
}

void Pre(int x) {
    For (L, bl[x], br[x]) {
        int st = 0x3f3f3f3f;
        For (R, L, br[x]) {
            st = min(st + d[R], li[R]), f[x][L - bl[x]][R - bl[x]] = st;
        }
    }
    For (L, bl[x], br[x]) For (R, L, br[x]) o.pb(Node(G(L, R), S(L, R)));
    Sort(v[x]);
    For (R, bl[x], br[x]) o.pb(Node(G(bl[x], R), S(bl[x], R)));
    Sort(pr[x]);
    For (L, bl[x], br[x]) o.pb(Node(G(L, br[x]), S(L, br[x])));
    Sort(sf[x]);
}

Node Move(int L, int R, int cr, int st) {
    int r = cr;
    For (u, L, R)
        cr = min(max(cr, st) + d[u], li[u]), cmax(r, cr);
    return Node(cr, r);
}

int Go(Node f[], int st) {
    int L = 1, R = f[0].s;
    while (L + 1 < R) {
        int m = (L + R) >> 1;
        f[m].g > f[m].s + st ? R = m : L = m;
    }
    int r = min(f[L].g, f[L].s + st); ++L;
    if (L <= f[0].s) cmax(r, min(f[L].g, f[L].s + st));
    return r;
}

int Work(int L, int R, int st) {
    if (be[L] == be[R]) return Move(L, R, st, st).s;
    Node x = Move(L, br[be[L]], st, st); int cr = max(x.g, st), A = x.s;
    For (u, be[L] + 1, be[R] - 1) {
        cmax(A, Go(pr[u], cr)); 
        cmax(A, Go(v[u], st)); 
        cr = min(G(bl[u], br[u]), S(bl[u], br[u]) + cr);
        cmax(cr, Go(sf[u], st)); 
        cmax(cr, st); 
    }
    return max(A, Move(bl[be[R]], R, cr, st).s);
}

int main() {
    io >> n >> m;
    B = sqrt(n);
    For (i, 1, n) io >> d[i], s[i] = s[i - 1] + d[i];
    For (i, 1, n) io >> li[i];
    For (i, 1, n) {
        be[i] = (i - 1) / B + 1; br[be[i]] = i;
        !bl[be[i]] ? bl[be[i]] = i : 0; 
    }
    For (i, 1, be[n]) Pre(i);
    while (m--) {
        int L, R, st;
        io >> L >> R >> st;
        printf("%d\n", Work(L, R, st));
    }
    return 0;
}
