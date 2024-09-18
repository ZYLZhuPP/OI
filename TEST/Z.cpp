#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e7 + 5;

int la, lb, z[N], p[N];
char a[N], b[N];
ll ans1, ans2;

int main() {
    scanf("%s", a + 1); la = strlen(a + 1);
    scanf("%s", b + 1); lb = strlen(b + 1);
    z[1] = lb;
    int l = 0, r = 0;
    For (i, 2, lb) {
        z[i] = max(0, min(z[i - l + 1], r - i + 1));
        while (i + z[i] <= lb && b[i + z[i]] == b[z[i] + 1]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    l = r = 0;
    For (i, 1, la) {
        p[i] = max(0, min(z[i - l + 1], r - i + 1));
        while (i + p[i] <= la && a[i + p[i]] == b[p[i] + 1]) p[i]++;
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    For (i, 1, lb) ans1 ^= 1ll * i * (z[i] + 1);
    For (i, 1, la) ans2 ^= 1ll * i * (p[i] + 1);
    printf("%lld\n%lld", ans1, ans2);

    return 0;
}
