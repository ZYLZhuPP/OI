#include <bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

inline int read() {
    int x=0,ch=getchar(),minus=0;
    for(;ch<'0'||ch>'9';ch=getchar()) minus|=(ch=='-');
    for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+(ch^48);
    return minus?-x:x;
}

int a[N],pos[N],n;
ll f[N], ans;

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x ; x -= lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x <= n; x += lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int main() {
    int T=read();
    while(T--) {
        ans = 0;
        n=read();
        for(int i=1;i<=n;i++) pos[a[i]=read()]=i, o[i] = 0;
        For (i, 1, n) ans += query(a[i]), upd(a[i], 1);
        f[0] = 0;
        For (i, 1, n) {
            f[i] = f[i - 1];
            if (i > 1) cmin(f[i], f[i - 2] + (pos[i]<pos[i - 1]? -1: 1));
        }
        printf("%lld\n", f[n] + ans);
    }
    return 0;
}