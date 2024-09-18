#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, x, a[N], ls[N], rs[N], stk[N], top;

void dfs(int u) {
    if (!u) return;
    cout << u << " ";
    dfs(ls[u]); dfs(rs[u]);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    For (i, 1, n) cin >> x, a[x] = i;
    For (i, 1, n) {
        while (top && a[stk[top]] > a[i]) top--;
        ls[i] = rs[stk[top]]; rs[stk[top]] = i;
        stk[++top] = i;
    }
    dfs(stk[1]);

    return 0;
}
