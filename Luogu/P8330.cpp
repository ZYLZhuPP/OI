#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, M = 205;

struct IO {
    int c, f;
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

int T, n, B, ans[N], a[N], b[N], m, cnt[N];
vector<int > pos[N];
int pre[N], to[M][N], s[N];

int main() {
    io >> T;
    while (T--) {
        io >> n; B = 0;
        For (i, 1, n) io >> a[i], b[i] = a[i], pos[i].resize(ans[i] = 0);
        sort(b + 1, b + n + 1); m = unique(b + 1, b + n + 1) - b - 1;
        For (i, 1, n) pos[a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b].push_back(i);
        For (i, 1, m) B = max(B, cnt[i] = (int)pos[i].size());
        B = min(B, min((int)sqrt(n), 200));

        For (i, 1, m) {
            if (cnt[i] <= B) continue;

            memset(pre, 0, sizeof pre);
            for (int &x : pos[i]) pre[x] = 1;
            For (j, 1, n) pre[j] += pre[j - 1];

            For (j, 1, m) {
                if (i == j) continue;

                int mx = 1, cur = 1;
                For (k, 1, cnt[j] - 1) mx = max(mx, cur = max(1, cur - (pre[pos[j][k]] - pre[pos[j][k - 1]]) + 1));
                ans[i] = max(ans[i], mx + cnt[i]);

                mx = pre[pos[j][0]], cur = max(pre[pos[j][0]] - 1, 0);
                For (k, 1, cnt[j] - 1) {
                    mx = max(mx, cur += pre[pos[j][k]] - pre[pos[j][k - 1]]);
                    if (cur) cur--;
                }
                ans[j] = max(ans[j], mx + cnt[j]);
            }
        }

        For (i, 1, B) {
            int id = 0;
            memset(s, 0, sizeof s);

            int r = 0;
            For (l, 1, n) {
                while (s[id] < i) {
                    s[a[r = r < n? r + 1: 1]]++;
                    if (s[a[r]] > s[id]) id = a[r];
                }
                to[i][l] = r; //printf("%d %d %d\n", i, l, r);
                s[a[l]]--;
            }
        }

        For (i, 1, m) {
            if (cnt[i] > B) continue;
            
            int t = 0;
            For (l, 0, cnt[i] - 1) {
                while (t < B && to[t + 1][1] < pos[i][l]) t++;
                if (t) ans[i] = max(ans[i], t - l + cnt[i]);

                int r = l, p = pos[i][l] + 1;
                if (p > n) continue;
                For (k, 1, B) {
                    if (to[k][p] < p) break;

                    while (r < cnt[i] && pos[i][r] <= to[k][p]) r++;
                    ans[i] = max(ans[i], k - (r - l - 1) + cnt[i]);
                }
            }
        }

        int mx = 0;
        For (i, 1, m) mx = max(mx, ans[i]);
        printf("%d\n", mx); //puts("");
        For (i, 1, m) if (ans[i] == mx) printf("%d\n", b[i]);
    }


    return 0;
}
