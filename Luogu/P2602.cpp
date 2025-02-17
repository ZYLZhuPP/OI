#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll dp[15][15];
vector<int > v;

ll dfs(int p, bool pre, bool done, int k, int tot) {
    if(p == -1) return tot;
    if(pre && !done && dp[p][tot] != -1) return dp[p][tot];
    int limit = done ? v[p] : 9;
    ll res = 0;
    for(int now = 0; now <= limit; now++) 
        res += dfs(p - 1, pre || now, done && (now == limit), k, tot + ((now || pre) && (now == k)));
    if(pre && !done) dp[p][tot] = res;
    return res;
}

ll solve(ll x, int k) {
    v.clear();
    for(; x; v.push_back(x % 10), x /= 10);
    return dfs(v.size() - 1, 0, 1, k, 0);
}

int main() {
    ll a, b;
    scanf("%lld%lld", &a, &b);
    for(int i = 0; i < 10; i++)
        memset(dp, -1, sizeof(dp)), printf("%lld ", solve(b, i) - solve(a - 1, i));
    return 0;
}
