#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x - (x>=Mo? Mo: x<0? -Mo: 0); }
inline void add(int &x, int y) { x = mo(x + y); }
inline int mul(int x, int y) { return 1ll * x * y % Mo; }

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
} io;

int n, a[N], d[N], d1[N], d2[N];
int h1, h2, t1, t2, q1[N], q2[N];
int sum1, sum2;
ll ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], d[i] = a[i] - a[i - 1]; d[n + 1] = -a[n];
    For (i, 1, n) ans += max(d[i], 0);
    
    memcpy(d1, d, sizeof(d));
    memcpy(d2, d, sizeof(d));
    For (i, 1, n + 1) {
        if (d[i] > 0) q1[++t1] = i, q2[++t2] = i;
        else if (d[i] < 0) {
            int x1 = -d[i], x2 = -d[i];
            while (x1) {
                int cnt = min(x1, d1[q1[h1]]); x1 -= cnt, d1[q1[h1]] -= cnt;
                add(sum1, mul(cnt, mul(i - q1[h1], i - q1[h1])));
                if (!d1[q1[h1]]) h1++;
            }
            while (x2) {
                int cnt = min(x2, d2[q2[t2]]); x2 -= cnt, d2[q2[t2]] -= cnt;
                add(sum2, mul(cnt, mul(i - q2[t2], i - q2[t2])));
                if (!d2[q2[t2]]) t2--;
            }
        }
    }
    
    printf("%lld\n%d\n%d", ans, sum2, sum1);
    return 0;
}
