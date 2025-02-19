#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

int n, m, a[N], f[N], g[N], s[N], ans;
char t[N];

int main() {
    scanf("%s", t + 1); n = strlen(t + 1);
    int x = 0;
    For (i, 1, n) if (t[i] & 1) a[++m] = x, x = 0; else x++;
    a[++m] = x;
    if (m == 1) return printf("%d", n), 0;
    ans = ml(a[1] + 1, a[m] + 1);
    For (i, 0, n) g[i] = 1;
    s[1] = f[1] = 1;
    For (i, 2, m - 1) {
        For (j, 0, a[i]) add(f[i], s[i - 1] - s[g[j] - 1]);
        For (j, 0, a[i]) g[j] = i;
        s[i] = mo(s[i - 1] + f[i]);
    }
    mul(ans, s[m - 1]);
    printf("%d", ans);

    return 0;
}
