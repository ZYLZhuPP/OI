#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int W;

inline ll ext_odd(int k, int D, int cnt = W - 1) {
    if (!k) return 0;
    return 1ll * (cnt + (k > 1)) * max(0, D - (k * W - 1));
}
inline ll ext_even(int k, int D, int cnt = W - 1) {
    if (!k) return 0;
    int fir = max(D - (k * W - 1), 0), las = max(D - (k * W + cnt - 1), 0);
    return 1ll * (fir + las) * (fir - las + 1) / 2;
}
inline ll calc_odd(int k, int D) {
    int lim = (D + 1) / W; k = min(k, lim);
    if (!k) return 0; ll ans = ext_odd(1, D);
    ans += 1ll * W * (1ll * (D + 1) * (k - 1) - 1ll * (2 + k) * (k - 1) / 2 * W);
    return ans;
}
inline ll calc_even(int k, int D) {
    int lim = (D + 1) / W; k = min(k, lim);
    if (!k) return 0; ll ans = 0; int r = (D + 2 - W) / W;
    while (k > r) ans += ext_even(k, D), --k;
    ans += (1ll * W * (2 * D + 3) * k - 1ll * W * W * k - 1ll * W * W * k * (k + 1)) / 2;
    return ans;
}
inline ll solve(int D, int H) {
    if (W > H || !D) return 0;
    D = min(D, H); ll ans = 0;
    int kmax = (H + 1) / W, cnt = (H + 1) % W;
    if (cnt < W - 1) {
        if (kmax & 1) ans += ext_odd((kmax + 1) / 2, D, cnt);
        else ans += ext_even(kmax / 2, D, cnt);
        --kmax;
    }
    ans += calc_odd((kmax + 1) / 2, D);
    ans += calc_even(kmax / 2, D);
    if (D >= W) ans -= 1ll * (D - W) * (D - W + 1) / 2;
    return ans;
}
inline void WORK() {
    int dL, dR, hL, hR; cin >> dL >> dR >> hL >> hR >> W;
    cout << solve(dR, hR) - solve(dL - 1, hR) - solve(dR, hL - 1) + solve(dL - 1, hL - 1) << "\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while (T--) WORK();
    
    return 0;
}
