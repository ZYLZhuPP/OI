#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll T, a, b;

inline ll solve(ll a, ll b) {
    ll f1 = b, f2 = a, ans = 0, x = 1;
    while (f2) {
        if (f1 > f2) ans += x * ((f1 - 1) / f2), f1 = (f1 - 1) % f2 + 1;
        else ans += f2 / f1, f2 %= f1, x = 2;
    }
    return ans + 2 * (f1 - 1);
}

int main() {
    cin >> T;
    while(T--) cin >> a >> b, cout << solve(a, b) << endl;
    return 0;
}