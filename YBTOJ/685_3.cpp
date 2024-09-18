#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;

int n, p[N << 1], ans;
vector<pair<int, int > > a;
char s[N];

void init() {
    ans = 0;
    a.resize(0);
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
    while (~scanf("%s", s)) {
        init();
        manacher(s);
        n = strlen(s);
        For (i, 2, 2 * n) {
            int r = p[i] / 2, x = (i / 2) - r + 1, y = ((i + 1) / 2) + r - 1;
            if (r) a.push_back(mkp(x, y));
        }
        sort(a.begin(), a.end());
        
        int r = 0, i = 0;
        while (r < n) {
            int ma = 0;
            while (i < a.size() && a[i].first <= r + 1) ma = max(ma, a[i].second), i++;
            r = ma; ans++;
        }

        printf("%d\n", ans - 1);
    }

    return 0;
}
