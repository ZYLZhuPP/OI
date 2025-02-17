#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x >= Mo ? Mo : x < 0 ? -Mo : 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

int n, Q, t, T, tot, m, rt, _2[N];
char a[N];

struct Node {
    int l, r, d, t, lst;
} o[N];
#define ls o[u].l
#define rs o[u].r

void redo(int u) {
    mul(o[u].d, _2[T - o[u].lst]);
    o[u].lst = T;
}

int node(int t) {
    ++tot;
    o[tot].l = o[tot].r = o[tot].d = 0;
    o[tot].t = t;
    o[tot].lst = T;
    return tot;
}

int dfs(int &u, int k, int t) {
    if (!u) u = node(t);
    redo(u);
    if (k == m) {
        o[u].t = T; ls = rs = 0;
        int ret = mo(_2[T - t] - 1 - o[u].d);
        o[u].d = _2[T - t] - 1;
        return ret;
    }
    int ret = a[k + 1]=='L'? dfs(ls, k + 1, o[u].t + 1): dfs(rs, k + 1, o[u].t + 1);
    add(o[u].d, ret);
    return ret;
}

void init() {
    _2[0] = 1;
    For (i, 1, N - 1) _2[i] = mo(_2[i - 1] << 1);
}

int main() {
    init(); 
    scanf("%d", &Q);
    while (Q--) {
        T = 1;
        scanf("%d", &n);
        rt = node(0);
        char op[2];
        while (n--) {
            scanf("%s", op);
            if (op[0] == 'G') {
                scanf("%d", &t);
                T += t;
                redo(rt);
                printf("%d\n", mo(_2[T] - 1 - o[rt].d));
            } else {
                scanf("%s", a + 1);
                m = strlen(a + 1);
                dfs(rt, 0, 0);
                printf("%d\n", mo(_2[T] - 1 - o[rt].d));
            }
        }
    }
    
    return 0;
}

