#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

int n, mn = INT_MAX, mx = INT_MIN, x;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    For (i, 1, n) cin >> x, mx = max(mx, x), mn = min(mn, x);
    cout << (long long)mx + mn;

    return 0;
}
