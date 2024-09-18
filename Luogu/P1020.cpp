#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 5e4 + 5;

int n, a[N], x, ans1, ans2;

namespace BIT {
    int o[M];
#define lowbit(x) ((x) & -(x))
    void upd(int x, int v) { for (; x < M; x += lowbit(x)) o[x] = max(o[x], v); }
    int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r = max(r, o[x]); return r; }
}
using namespace BIT;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    while (cin >> x) a[++n] = x;
    For (i, 1, n) {
        x = query(a[i] - 1) + 1;
        ans2 = max(ans2, x);
        upd(a[i], x);
    }
    memset(o, 0, sizeof o);
    reverse(a + 1, a + n + 1);
    For (i, 1, n) {
        x = query(a[i]) + 1;
        ans1 = max(ans1, x);
        upd(a[i], x);
    }
    cout << ans1 << endl;
    cout << ans2;

    return 0;
}
