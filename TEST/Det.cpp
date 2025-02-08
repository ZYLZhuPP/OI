#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 55;
const double eps = 1e-8;

int n;
double a[N][N];

inline double Det(int n) {
    double res = 1, x;
    For (i, 1, n) {
        int k = i;
        For (j, i + 1, n) if (fabs(a[k][i]) < fabs(a[j][i])) k = j;
        if (k ^ i) res = -res, swap(a[i], a[k]);
        if (fabs(a[i][i]) <= eps) return 0;
        For (j, i + 1, n) {
            x = a[j][i] / a[i][i];
            For (k, i, n) a[j][k] -= a[i][k] * x;
        }
        res *= a[i][i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) For (j, 1, n) cin >> a[i][j];
    cout << Det(n);

    return 0;
}
