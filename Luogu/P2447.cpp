#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

int n, m, ans;
bitset<N > a[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    int x;
    For (i, 1, m) cin >> a[i] >> x, a[i][n] = x;
    For (i, 1, n) {
        x = i;
        while (x <= m && !a[x].test(i - 1)) x++;
        if (x > m) return puts("Cannot Determine"), 0;
        swap(a[i], a[x]); ans = max(ans, x);
        For (j, 1, m) if (j ^ i) if (a[j].test(i - 1)) a[j] ^= a[i];
    }
    printf("%d\n", ans);
    rFor (i, n, 1) puts(a[i].test(n)? "?y7M#": "Earth");

    return 0;
}
