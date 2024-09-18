#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5;

int n, T, mx, a[N], tot;
char s[N];
bool flag;

int sa[N], h[N], cnt[N], _[2][N], *x = _[0], *rk = _[1];
template<class C> void SA(const C *s, int n, int m) {
    int t = 0;
    For (i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[rk[i] = s[i]]++;
    For (i, 1, m) cnt[i] += cnt[i - 1];
    rFor (i, n, 1) sa[cnt[rk[i]]--] = i;

    for (int j = 1; ; j <<= 1) {
        swap(x, rk);

        t = 0; For (i, n - j + 1, n) rk[++t] = i;
        For (i, 1, n) if (sa[i] > j) rk[++t] = sa[i] - j;

        For (i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[x[rk[i]]]++;
        For (i, 1, m) cnt[i] += cnt[i - 1];
        rFor (i, n, 1) sa[cnt[x[rk[i]]]--] = rk[i];

        m = 0; For (i, 1, n) rk[sa[i]] = m += x[sa[i - 1]] ^ x[sa[i]] || x[sa[i - 1] + j] ^ x[sa[i] + j];
        if (m == n) break;
    }

    For (i, 1, n) {
        m = max(0, h[rk[i - 1]] - 1);
        while (s[sa[rk[i] - 1] + m] == s[i + m]) m++;
        h[rk[i]] = m;
    }
}

int f[20][N];
void init() {
    tot = mx = 0; flag = 0;
    For (i, 1, n) f[0][i] = h[i];
    for (int i = 1; (1 << i) <= n; ++i)
        For (j, 1, n - (1 << i) + 1)
            f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
}

int LCP(int x, int y) {
    x = rk[x], y = rk[y];
    if (x > y) swap(x, y);
    int o = log2(y - x);
    return min(f[o][x + 1], f[o][y - (1 << o) + 1]);
}

int main() {
    while (scanf("%s", s + 1) && s[1] ^ '#' && ++T) {
        n = strlen(s + 1);
        SA(s, n, 122);
        init();

        For (l, 1, n) {
            for (int i = 1; i + l <= n; i += l) {
                int k = LCP(i, i + l), res = k / l + 1;
                if (k % l) {
                    int le = i - (l - (k % l));
                    if (le > 0 && LCP(le, le + l)) res++;
                }

                if (res > mx) {
                    mx = res;
                    a[tot = 1] = l;
                } else if (res == mx && a[tot] < l) a[++tot] = l;
            }
        }

        For (i, 1, n) {
            For (j, 1, tot) if (LCP(sa[i], sa[i] + a[j]) >= (mx - 1) * a[j]) {
                flag = 1;
                printf("Case %d: ", T);
                For (k, 0, mx * a[j] - 1) putchar(s[sa[i] + k]);
                puts("");
                break;
            }
            if (flag) break;
        }
    }

    return 0;
}
