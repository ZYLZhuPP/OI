#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll Mo;
inline ll mo(ll x) { return x -= x>=Mo? Mo: 0; }
inline void add(ll &x, const ll &y) { x = mo(x + y); }
inline ll ml(ll x, ll y) { ll r = 0; for (; y; y >>= 1, add(x, x)) if (y & 1) add(r, x); return r; }
inline void mul(ll &x, const ll &y) { x = ml(x, y); }
inline ll qPow(ll x, ll y) { ll r = 1; for (; y; y >>= 1, mul(x, x)) if (y & 1) mul(r, x); return r; }

ll n, m;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> Mo;
    cout << ml(qPow(n, m - 1), qPow(m, n - 1));

    return 0;
}
