#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2005;
int n, t;
long double p, f[N][N], ans;

int main() {
    scanf("%d%Lf%d", &n, &p, &t);
    f[0][0] = 1;
    For (i, 1, t) {
        f[i][0] = f[i - 1][0] * (1 - p);
        For (j, 1, n - 1) f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j] * (1 - p);
        f[i][n] = f[i - 1][n] + f[i - 1][n - 1] * p;
    }

    For (i, 1, n) ans += f[t][i] * i;
    printf("%.8Lf", ans);

    return 0;
}
