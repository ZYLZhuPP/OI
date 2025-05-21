#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int sa[N][3], sb[N][3], s[N][3][3], S[3][3], mp[128];

void init(string a, string b) {
    mp['A'] = 0, mp['C'] = 1, mp['T'] = 2;
    int n = a.size();
    For (i, 1, n) {
        For (j, 0, 2) sa[i][j] = sa[i - 1][j], sb[i][j] = sb[i - 1][j];
        sa[i][mp[a[i - 1]]]++, sb[i][mp[b[i - 1]]]++;
        For (j, 0, 2) For (k, 0, 2) s[i][j][k] = s[i - 1][j][k];
        s[i][mp[a[i - 1]]][mp[b[i - 1]]]++;
    }
}

int get_distance(int x, int y) {
    y++;
    For (i, 0, 2) if (sa[y][i] - sa[x][i] != sb[y][i] - sb[x][i]) return -1;
    int ans = 0;
    For (i, 0, 2) For (j, 0, 2) S[i][j] = s[y][i][j] - s[x][i][j];
    For (i, 0, 2) For (j, 0, i - 1) {
        int x = min(S[i][j], S[j][i]);
        ans += x;
        S[i][j] -= x, S[j][i] -= x;
    }
    ans += 2 * (S[0][1] + S[1][0]);
    return ans;
}
