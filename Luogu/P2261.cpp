#include<bits/stdc++.h>
using namespace std;

long long n, k, ans;

int main() {
    cin >> n >> k;
    ans = n * k;
    for (int l = 1, r; l <= min(k, n); l = r + 1)
         r = min(k / (k / l), n), ans -= 1ll * (k / l) * (r - l + 1) * (l + r) >> 1;
    printf("%lld", ans);

    return 0;
}
