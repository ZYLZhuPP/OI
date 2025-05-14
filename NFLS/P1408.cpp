#include"icc.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

mt19937 rnd(time(0));
int fa[N], id[N], a[N], b[N], cnt;
bool no[N][N], ok[N];
vector<int > pt[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

void run(int n) {
    For (i, 1, n) fa[i] = i, pt[i] = {i};
    For (o, 1, n - 1) {
        int m = 0, A = 0, B = 0;
        For (i, 1, n) if (find(i) == i) id[++m] = i, ok[i] = 1;
        For (i, 1, m) For (j, 1, m) no[id[i]][id[j]] = 0;
        do {
            cnt++;
            shuffle(id + 1, id + m + 1, rnd);
            A = B = 0;
            For (i, 1, m / 2) for (auto &x : pt[id[i]]) a[++A] = x;
            For (i, m / 2 + 1, m) for (auto &x : pt[id[i]]) b[++B] = x;
            if (query(A, B, a + 1, b + 1)) break;
            For (i, 1, m / 2) For (j, m / 2 + 1, m) no[id[i]][id[j]] = no[id[j]][id[i]] = 1;
        } while (1);
        bool flag = 0;
        do {
            flag = 0;
            For (i, 1, m / 2) if (ok[id[i]]) {
                bool pd = 1;
                For (j, m / 2 + 1, m) if (ok[id[j]] && !no[id[i]][id[j]]) { pd = 0; break; }
                if (pd) ok[id[i]] = 0, flag = 1;
            }
            For (i, m / 2 + 1, m) if (ok[id[i]]) {
                bool pd = 1;
                For (j, 1, m / 2) if (ok[id[j]] && !no[id[i]][id[j]]) { pd = 0; break; }
                if (pd) ok[id[i]] = 0, flag = 1;
            }
        } while (flag);
        A = B = 0;
        For (i, 1, m / 2) if (ok[id[i]]) for (auto &x : pt[id[i]]) a[++A] = x;
        For (i, m / 2 + 1, m) if (ok[id[i]]) for (auto &x : pt[id[i]]) b[++B] = x;
        int l = 1, r = A, aa = 0, bb = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (query(mid, B, a + 1, b + 1)) aa = mid, r = mid - 1;
            else l = mid + 1;
        }
        B = 0;
        For (i, m / 2 + 1, m) if (ok[id[i]] && !no[find(a[aa])][id[i]]) for (auto &x : pt[id[i]]) b[++B] = x;
        l = 1, r = B;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (query(A, mid, a + 1, b + 1)) bb = mid, r = mid - 1;
            else l = mid + 1;
        }
        int u = a[aa], v = b[bb];
        setRoad(u, v);
        u = find(u), v = find(v);
        for (auto &x : pt[u]) pt[v].pb(x);
        fa[u] = v; pt[u].resize(0);
    }
}
