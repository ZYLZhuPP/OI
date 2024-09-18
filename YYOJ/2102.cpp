#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e6 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    template<class C>
    inline IO& operator >> (C *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

struct Node {
    int len, suf, to[4];
    Node() { len = suf = 0; memset(to, 0, sizeof to); }
} o[N << 1];
char ch[4] = {'A', 'C', 'G', 'T'}, st[N];
int lst, tot, f[N << 1], rt[N], n, ans, op, a[N];

void upd(int c, int r) {
    int p = lst, ne = lst = ++tot; o[ne].len = o[p].len + 1;

    while (p && !o[p].to[c]) o[p].to[c] = ne, p = o[p].suf;
    if (!p) o[ne].suf = r;
    else {
        int q = o[p].to[c];
        if (o[q].len == o[p].len + 1) o[ne].suf = q;
        else {
            int nq = ++tot; o[nq] = o[q];
            o[nq].len = o[p].len + 1;
            o[q].suf = o[ne].suf = nq;
            while (p && o[p].to[c] == q) o[p].to[c] = nq, p = o[p].suf;
        }
    }
}

int getid(char c) { return c=='A'? 0: c=='C'? 1: c=='G'? 2: 3; }
void ins(char st[], int k) {
    int len = strlen(st);
    rt[k] = lst = ++tot;
    For (i, 0, len - 1) upd(getid(st[i]), rt[k]);
}

int to[4];
void connect() {
    rt[n + 1] = tot + 1;
    rFor (i, n, 1) {
        int l = rt[i], r = rt[i + 1] - 1;
        For (k, 0, 3) if (to[k])
            For (p, l, r) if (!o[p].to[k]) o[p].to[k] = to[k];
        For (k, 0, 3) if (o[rt[i]].to[k]) to[k] = o[rt[i]].to[k];
    }
}

int cnt;
void put() { For (i, 1, cnt) putchar(ch[a[i]]); putchar('\n'); }
void dfs(int u) {
    put();
    For (k, 0, 3) {
        int v = o[u].to[k];
        if (!v)  continue;
        a[++cnt] = k;
        dfs(v); cnt--;
    }
}

queue<int > q;
int d[N];
void solve() {
    For (i, 1, tot) if (i == 1 || o[i].suf)
        For (k, 0, 3) if (o[i].to[k]) d[o[i].to[k]]++;
    q.push(1);
    f[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); add(ans, f[u]);
        For (k, 0, 3) {
            int v = o[u].to[k];
            if (!v) continue;
            d[v]--; add(f[v], f[u]);
            if (!d[v]) q.push(v);
        }
    }
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> st;
        ins(st, i);
    }
    connect();
    io >> op;
    if (op == 1) dfs(1);
    solve();
    printf("%d", ans);

    return 0;
}
