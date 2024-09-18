#include <bits/stdc++.h>
using namespace std;

int n, m, f[1000005];

inline bool check(int k) {
    int c[9], l = 0;
    while (k) {
        c[++l] = k % 10, k /= 10;
        if (c[l] == 4) return 0;
        if (c[l] == 6 && c[l - 1] == 2) return 0;
    }
    return 1;
}

int main() {
    for (int i = 1; i <= 1000000; i++) f[i] = f[i - 1] + check(i);
    while (scanf("%d%d", &n, &m) && (n != 0 || m != 0)) printf("%d\n", f[m] - f[n - 1]);
}