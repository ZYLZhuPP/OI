#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e7 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

int n, p[N << 1], ans;
char st[N];

int main() {
    scanf("%s", st + 1);
    int n = strlen(st + 1);
    string s = "@";
    For (i, 1, n) s += '#', s += st[i];
    s += "#$";

    int r = 0, m = 0;
    For (i, 2, 2 * n) {
        p[i] = max(1, min(p[2 * m - i], r - i));
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > r) r = i + p[i], m = i;
        cmax(ans, p[i] - 1);
    }
    printf("%d", ans);

    return 0;
}
