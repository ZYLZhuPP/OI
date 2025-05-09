#include"fun.h"
#include<bits/stdc++.h>
using namespace std;

//int hoursRequired(int X, int Y);
//int attractionsBehind(int X, int Y);

#define pb push_back
#define dist hoursRequired
#define siz attractionsBehind
#define size(x) ((int)x.size())
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int sz[N], depG[N], bel[N], cnt, lst, G;
bool cmp(const int &a, const int &b) { return depG[a] < depG[b]; }
vector<int > pt[4], ans;

int get(int x) {
    int a = x % 3 + 1, b = a % 3 + 1;
    int A = size(pt[a])? *pt[a].rbegin(): G;
    int B = size(pt[b])? *pt[b].rbegin(): G;
    if (depG[A] > depG[B]) { ans.pb(A); pt[a].pop_back(); return a; }
    else { ans.pb(B); pt[b].pop_back(); return b; }
}

vector<int > createFunTour(int n, int Q) {
    int mn = n;
    For (i, 1, n - 1) {
        sz[i] = siz(0, i);
        if (n - sz[i] <= n / 2 && sz[i] < mn) mn = sz[G = i];
    }
    int son[4];
    For (i, 0, n - 1) {
        depG[i] = dist(G, i);
        if (depG[i] == 1) son[++cnt] = i;
    }
    For (i, 1, cnt) {
        int u = son[i];
        For (v, 0, n - 1) if (v ^ G)
            if (i<cnt? dist(u, v) < depG[v]: !bel[v]) pt[i].pb(v), bel[v] = i;
    }
    For (i, 1, cnt) sort(pt[i].begin(), pt[i].end(), cmp);
    For (i, 1, n - 2) {
        bool flag = 0;
        if (cnt == 3) {
            int a = 1, b = 2, c = 3;
            if (size(pt[b]) > size(pt[a])) swap(a, b);
            if (size(pt[c]) > size(pt[a])) swap(a, c);
            if (abs(size(pt[a]) - size(pt[b]) - size(pt[c])) <= 1) {
                for (auto &u : pt[c]) pt[b].pb(u);
                sort(pt[b].begin(), pt[b].end(), cmp);
                pt[c].resize(0); cnt = 2;
                if (lst == b || lst == c) {
                    if (depG[*ans.rbegin()] < depG[*pt[b].rbegin()]) {
                        ans.pb(*pt[b].rbegin()); pt[b].pop_back(); flag = 1;
                    }
                    lst = b;
                }
            }
        }
        if (!flag) lst = get(lst);
    }
    ans.pb(G);
    if (size(pt[1])) ans.pb(pt[1][0]);
    if (size(pt[2])) ans.pb(pt[2][0]);
    if (size(pt[3])) ans.pb(pt[3][0]);

    return ans;
}
