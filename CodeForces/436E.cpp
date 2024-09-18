#include <bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef array<int, 2 > P;
const int N = 1e6 + 5;

int n, m, a[N], cnt[N], vis[N];
ll ans;
priority_queue<P > A, B;

inline bool empty(priority_queue<P > &q) {
    while (!q.empty() && vis[q.top()[1]]) q.pop();
    return q.empty();
}

inline P top(priority_queue<P > &q) {
    empty(q); return q.top();
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    For (i, 0, n - 1) cin >> a[i] >> a[i + n], a[i + n] -= a[i], A.push({-a[i], i}), B.push({-(a[i] + a[i + n]), i});
    while (m--) {
        int i = top(A)[1]; A.pop();
        if (m && !empty(B) && a[i] + -top(A)[0] >= -top(B)[0]) A.push({-a[i], i}), i = top(B)[1], B.pop();
        if (i < n) A.push({-a[i + n], i + n});
        ans += a[i], cnt[i % n]++, vis[i] = 1;
    }
    printf("%lld\n", ans);
    For (i, 0, n - 1) printf("%d", cnt[i]);
    return 0;
}