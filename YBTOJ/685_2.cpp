#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
inline bool cmax(int &x, int y) { return x<y? x=y, 1: 0; }

int n, p[N << 1];
int ans, L[N], R[N];
char s[N];

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
    scanf("%s", s);
    manacher(s);
    n = strlen(s);
    
    For (i, 2, 2 * n) {
        int d = p[i] - 1, r = p[i] / 2, x = (i / 2) - r + 1, y = ((i + 1) / 2) + r - 1;
        cmax(R[x], d); cmax(L[y], d);
    }
    For (i, 1, n) cmax(R[i], R[i - 1] - 2), cmax(L[n - i + 1], L[n - i + 2] - 2);
    
    For (i, 1, n - 1) cmax(ans, L[i] + R[i + 1]);
    printf("%d\n", ans);

    return 0;
}
