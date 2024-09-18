#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, a[N], p[N], ans;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    For (i, 1, n) cin >> a[i], p[a[i]] = i;
    For (i, 1, n) if (a[i] ^ p[i]) ans = 1;
    puts(ans? "NO": "YES");

    return 0;
}
