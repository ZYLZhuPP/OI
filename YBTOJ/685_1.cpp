#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

int n, p[N << 1];
ll ans, pre[N], suf[N];
char s[N];

void init() {
    ans = 0;
    memset(pre, 0, sizeof pre);
    memset(suf, 0, sizeof suf);
}

void manacher(char *st) {
    int n = strlen(st);
    string s = "@";
    For (i, 0, n - 1) s += '#', s += st[i];
    s += "#$";

    int r = 0, m = 0;
    For (i, 2, 2 * n) {
        p[i] = max(1, min(p[2 * m - i], r - i));
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > r) r = i + p[i], m = i;
    }
}

int main() {
    while (~scanf("%s", s)) {
        init();
        manacher(s);
        n = strlen(s);
        For (i, 2, 2 * n) {
            int x = i / 2, r = p[i] / 2;
            pre[x - r + 1]++; pre[x + 1]--;
            x = (i + 1) / 2;
            suf[x]++; suf[x + r]--;
        }
        For (i, 1, n) pre[i] += pre[i - 1], suf[i] += suf[i - 1];
        For (i, 1, n - 1) suf[i] += suf[i - 1], ans += suf[i] * pre[i + 1];

        printf("%lld\n", ans);
    }

    return 0;
}
