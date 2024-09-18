#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
const int N = 2e4 + 5;

bool flag;
int T, n, p[N << 1];
ull L[N << 1], R[N << 1];
char s[N];

void init() {
    flag = 0;
    memset(L, 0, sizeof L);
    memset(R, 0, sizeof R);
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
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%s", s);
        manacher(s);
        n = strlen(s);
        For (i, 2, 2 * n) {
            if (i - p[i] == 0) L[i + p[i] - 1] = 1;
            if (i + p[i] == 2 * n + 2) R[i - p[i] + 1] = 1;
        }
        rFor (i, 2 * n, 0) L[i] |= L[i + 1] << 1;
        For (i, 1, 2 * n + 1) R[i] |= R[i - 1] << 1;
        For (i, 4, 2 * (n - 1)) if (p[i] - 1) {
            int r = p[i];
            while (r > 64) flag |= L[i - r] & R[i + r], r -= 64;
            for (; r > (i & 1); r--) flag |= L[i - r] & R[i + r] & 1ull;
            if (flag) break;
        }
        puts(flag? "Yes": "No");
    }

    return 0;
}
