#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, M = 5e4 + 5, S = 305;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, x, k;
int l, r, q[M];
ll y, sum[M], g[M], f[M];
vector<ll > v[S];

int time(int x, int y, int s, int d) {
    ll de = f[x * s + d] - f[y * s + d];
    int l = y, r = k;
    int res = k + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (de + sum[mid - x] - sum[mid - y] <= 0) res = mid, r = mid - 1;
        else l = mid + 1;
    }

    return res;
}

int main() {
    io >> n >> m;
    For (i, 1, n) {
        io >> x >> y;
        v[x].push_back(y);
    }

    For (s, 1, S - 1) {
        if (v[s].empty()) continue;
        sort(v[s].begin(), v[s].end());
        k = m / s; int cnt = v[s].size();
        For (i, 1, min(k, cnt)) sum[i] = sum[i - 1] + v[s][cnt - i];
        For (i, cnt + 1, k) sum[i] = sum[i - 1];

        For (d, 0, s - 1) {
            g[0] = f[d];
            l = r = 1; q[r] = 0;
            For (i, 1, k) {
                while (l < r && time(q[l], q[l + 1], s, d) <= i) l++;
                g[i] = max(f[i * s + d], f[q[l] * s + d] + sum[i - q[l]]);
                while (l < r && time(q[r], i, s, d) <= time(q[r - 1], q[r], s, d)) r--;
                q[++r] = i;
            }
            For (i, 0, k) f[i * s + d] = g[i];
        }
    }

    For (i, 1, m) printf("%lld ", f[i]);

    return 0;
}
