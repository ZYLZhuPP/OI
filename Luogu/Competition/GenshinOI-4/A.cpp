#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

int n, m, l, r;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    For (i, 1, m) cin >> l >> r;
    printf("%d\n", (n + 1) / 2);
    int x = n / 2;
    For (i, 1, n - x) printf("%d %d\n", i, i + x);

    return 0;
}
