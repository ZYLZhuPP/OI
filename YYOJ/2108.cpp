#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 1e5 + 5;

ll n, S, ans, c[N];
int len[N], m;
string st[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    cin >> m;
    For (i, 1, m) {
        cin >> st[i] >> c[i];
        len[i] = st[i].length();
    }

    ll S = 0;
    rFor (i, m, 1) {
        ll s = 0, ma = 0;
        rFor (j, len[i] - 1, 0) {
            s += st[i][j]=='M'? 1: -1;
            ma = max(ma, s);
        }
        if (s > 0) ans = max(ans, S + (c[i] - 1) * s + ma - 1);
        else ans = max(ans, S + ma - 1);
        S += s * c[i];
    }

    if (S > 0) puts("-1");
    else printf("%lld", ans);

    return 0;
}
