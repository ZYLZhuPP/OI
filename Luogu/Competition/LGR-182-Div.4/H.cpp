#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

int n, ans, f[N][N][26];
char st[N];

int main() {
    cin >> (st + 1); n = strlen(st + 1);
    For (i, 1, n) {
        For (j, i, n) {
            int mx = 0;
            f[i][j][st[j] - 'a']++;
            For (k, 0, 25) f[i][j][k] += f[i][j - 1][k], mx = max(mx, f[i][j][k]);
            if (mx <= (j - i + 1) / 2) ans++;
        }
    }
    cout << ans;

    return 0;
}
