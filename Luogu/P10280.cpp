#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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
    inline bool operator ~ () const { return ~c; }
} io;

int n, K;
ll ans;
char a[N], b[N];
set<pair<int, int > > se[2];

int main() {
    io >> n >> K;
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    For (i, 1, n) if (a[i] ^ b[i]) {
        int x = a[i] & 1;
        if (se[!x].empty()) se[x].insert({i % K, i});
        else {
            auto it = se[!x].lower_bound({i % K, 0});
            if (it == se[!x].end()) it = se[!x].begin();
            ans += (i - it->second - 1) / K + 1;
            se[!x].erase(it);
        }
    }
    printf("%lld", ans);

    return 0;
}
