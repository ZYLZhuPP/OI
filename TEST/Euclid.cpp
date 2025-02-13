#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll Euclid(ll a, ll b, ll c, ll n) {
    if (n < 0) return 0;
    if (!a) return b / c * (n + 1);
    ll res = a / c * n * (n + 1) / 2 + b / c * (n + 1);
    a %= c, b %= c; ll m = (a * n + b) / c;
    return res + n * m - Euclid(c, c - b - 1, a, m - 1);
}

int main() {

    return 0;
}
