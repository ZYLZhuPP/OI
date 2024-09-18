#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

int n, p[N << 1], L[N << 1], R[N << 1], ans;
char s[N];

void manacher(char *st) {
    string s = "@";
    For (i, 0, n - 1) s += '#', s += st[i];
    s += "#$";

    int r = 0, m = 0;
    For (i, 2, 2 * n) {
        p[i] = max(1, min(p[2 * m - i], r - i));
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > r) r = i + p[i], m = i;
        cmax(R[i - p[i] + 1], p[i] - 1); cmax(L[i + p[i] - 1], p[i] - 1);
    }

    for (int i = 3; i <= 2 * n - 1; i += 2) cmax(R[i], R[i - 2] - 2);
    for (int i = 2 * n - 1; i >= 3; i -= 2) cmax(L[i], L[i + 2] - 2);
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    manacher(s);
    for (int i = 3; i <= 2 * n - 1; i += 2) cmax(ans, L[i] + R[i]);
    printf("%d", ans);

    return 0;
}