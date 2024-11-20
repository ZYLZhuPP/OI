#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, K, a[N], fa[N], sz[N], ans;
unordered_map<int, int > mp;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i], mp[a[i]] = i, fa[i] = i;
    For (i, 1, n) {
        sz[i] = 1;
        int x = a[i] - K;
        if (mp.count(x)) {
            x = mp[x];
            if (x < i) {
                x = find(x);
                ans -= (sz[x] + 1) / 2;
                fa[x] = i; sz[i] += sz[x];
            }
        }
        x = a[i] + K;
        if (mp.count(x)) {
            x = mp[x];
            if (x < i) {
                x = find(x);
                ans -= (sz[x] + 1) / 2;
                fa[x] = i; sz[i] += sz[x];
            }
        }
        ans += (sz[i] + 1) / 2;
        printf("%d ", ans);
    }

    return 0;
}
