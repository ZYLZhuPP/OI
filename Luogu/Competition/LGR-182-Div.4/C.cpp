#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

int n, ans;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    int s = 0, l = 0, x;
    For (i, 1, n) {
        cin >> x;
        s += (x - l); s = min(s, 50); l = x;
        ans += s / 8; s %= 8;
    }
    cout << ans;

    return 0;
}
