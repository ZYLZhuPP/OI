#include <bits/stdc++.h>
//ÎÒ°®ÓÃ#define
#define mid(x, y) (x + y) >> 1
#define getm int m = mid(s, t)
using namespace std;
const int maximum = 1e6 + 9;
int N, M, cnt = 0, a[maximum], ver[maximum];
struct node {
    int l, r, v;
} pzt[maximum << 5];
void build(int s, int t, int p) {
    if (s == t) {
        pzt[p].v = a[t];
        return;
    }
    getm;
    int l = cnt++;
    int r = cnt++;
    pzt[p].l = l, pzt[p].r = r;
    build(s, m, l), build(m + 1, t, r);
    return;
}
int rd(int lo, int s, int t, int p) {
    if (s == t) return pzt[p].v;
    getm;
    if (lo <= m) return rd(lo, s, m, pzt[p].l);
    else if (lo > m) return rd(lo, m + 1, t, pzt[p].r);
    else return -1;
}
void wt(int lo, int s, int t, int p, int x) {
    if (s == t) {
        pzt[p].v = x;
        return;
    }
    getm;
    int nw = cnt++;
    if (lo <= m) {
        pzt[nw] = pzt[pzt[p].l];
        pzt[p].l = nw;
        wt(lo, s, m, nw, x);
    }
    else if (m < lo) {
        pzt[nw] = pzt[pzt[p].r];
        pzt[p].r = nw;
        wt(lo, m + 1, t, nw, x);
    }
    return;
}
int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    ver[0] = cnt++;  //ver_0
    build(1, N, 0);
    for (int i = 1, v, op, loc, val; i <= M; i++) {
        scanf("%d%d%d", &v, &op, &loc);
        if (op == 1) {
            scanf("%d", &val);
            pzt[cnt] = pzt[ver[v]];
            ver[i] = cnt++;
            wt(loc, 1, N, ver[i], val);
        }
        if (op == 2) {
            pzt[cnt] = pzt[ver[v]];
            ver[i] = cnt++;
            printf("%d\n", rd(loc, 1, N, ver[i]));
        }
        //printf("i=%d,ver[i]=%d\n",i,ver[i]);
    }
    return 0;
}
