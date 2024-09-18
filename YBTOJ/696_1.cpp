#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 3e5 + 5;

char s[N];
ll ans;

namespace PAM {
    int to[N][26], fa[N], len[N], cnt[N], tot, ed, now; const char *s_;
    void init() { len[tot = 1] = -1; fa[0] = fa[1] = 1; }
    int find(int p) { while (s_[now] ^ s_[now - len[p] - 1]) p = fa[p]; return p; }
    void add(const int c) {
        int p = find(ed);
        if (!to[p][c]) {
            int q = ++tot; len[q] = len[p] + 2;
            fa[q] = to[find(fa[p])][c]; to[p][c] = q;
        }
        ed = to[p][c]; cnt[ed]++;
    }
    void ins(const char *s) {
        int n = strlen((s_ = s) + 1);
        For (i, 1, n) now = i, add(s[i] - 'a');
    }
}
using namespace PAM;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    init();
    cin >> (s + 1); ins(s);
    rFor (i, tot, 1) cnt[fa[i]] += cnt[i], ans = max(ans, 1ll * cnt[i] * len[i]);
    cout << ans;

    return 0;
}
