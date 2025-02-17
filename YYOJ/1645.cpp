#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (auto i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~() {return ~c;}
} io;

ll T, ans, n, m, k, D, x, cnt[5005], s[N], a[N];

ll get(ll i, ll o) {
    return o*(m+k-i) + n*(i-1) + min(n, o+(D - s[i - 1]*n - o*(s[m] - s[i-1]))/a[i]);
}

int main() {
    io >> T;
    while (T--) {
        io >> n >> m >> k >> D;
        For (i, 1, m) io >> x, cnt[x]++;
        int t = 0;
        For (i, 1, 5000) while (cnt[i]) a[++t] = i, --cnt[i];
        For (i, 1, m) s[i] = s[i - 1] + a[i];
        
        if (n * s[m] <= D) {
            printf("%lld\n", n * (m + k));
            continue;
        }
        
        ans = 0;
        ll l = 0, r = 0;
        For (i, 1, m) {
            if (s[i - 1] * n > D) break;
            l = (i<m && s[i] * n <= D)? min(n, (D - n * s[i]) / (s[m] - s[i]) + 1): 0;
            r = min(n, (D - n * s[i - 1]) / (s[m] - s[i - 1]));
            if (s[i - 1] * n + l * (s[m] - s[i - 1]) <= D) ans = max(ans, get(i, l));
            ans = max(ans, get(i, r));
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
} 
