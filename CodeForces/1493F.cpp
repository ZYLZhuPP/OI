#include <bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

int N, M;

inline bool checkM(int B, int o, int k) {
    printf("? %d %d %d %d %d %d\n", N, k * B, 1, o * B + 1, 1, (o + k) * B + 1);
    fflush(stdout);
    bool flag; cin >> flag;
    return flag;
}

inline bool solveM(int B, int k) {
    if (k == 1) return 1;
    int x = k / 2;
    return checkM(B, k & 1, x) && solveM(B, k - x);
}

inline bool checkN(int B, int o, int k) {
    printf("? %d %d %d %d %d %d\n", k * B, M, o * B + 1, 1, (o + k) * B + 1, 1);
    fflush(stdout);
    bool flag; cin >> flag;
    return flag;
}

inline bool solveN(int B, int k) {
    if (k == 1) return 1;
    int x = k / 2;
    return checkN(B, k & 1, x) && solveN(B, k - x);
}
 
int main() {
    int n, m;
    cin >> n >> m;
    N = n, M = m;
    int res = 1, x = N, y = M;
    For (i, 2, n) {
        if (i * i > x) break;
        if (x % i) continue;
        int cnt = 1;
        while (!(x % i) && solveN(n / i, i)) {
            cnt++; n /= i; x /= i;
        }
        res *= cnt;
        while (!(x % i)) x /= i; 
    }
    if (x > 1 && solveN(n / x, x)) res *= 2, n /= x;
    For (i, 2, m) {
        if (i * i > y) break;
        if (y % i) continue;
        int cnt = 1;
        while (!(y % i) && solveM(m / i, i)) {
            cnt++; m /= i; y /= i;
        }
        res *= cnt;
        while (!(y % i)) y /= i; 
    }
    if (y > 1 && solveM(m / y, y)) res *= 2, m /= y;
    printf("! %d", res);
    fflush(stdout);

    return 0;
}