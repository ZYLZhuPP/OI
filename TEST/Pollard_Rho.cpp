#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll mul(ll x, ll y, ll Mo) {
    ll r = x * y - Mo * ll(1.L / Mo * x * y);
    return r + Mo * ((r < 0) - (r >= Mo));
}

inline ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a % b);
}

ll Pollard_Rho(ll n) {
    if (!(n & 1)) return 2;
    auto f = [&](ll x) -> ll { return mul(x, x, n) + 1; };
    ll s = 0, t = 0, o = 0, M = 1, m, g;
    for (int i = 0; (i & 0xff) || (g = gcd(M, n)) == 1;
    ++i, s = f(s), t = f(f(t))) {
        if (s == t) s = ++o % n, t = f(s);
        m = mul(M, s - t + n, n);
        if (m) M = m;
    }
    return g;
}

int main() {
    ll n;
    cin >> n;
    cout << Pollard_Rho(n);
    return 0;
}//期望O(n^1/4)找非平凡因子
