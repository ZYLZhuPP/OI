#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

string process(vector<vector<string > > a, int i, int j, int k, int n) {
    string res;
    int o = 2 * (n - k - 1);
    if (i == o && j == o) {
        int m = k * 2 + 3;
        vector<vector<char > > mp(m, vector<char >(m, 0));
        vector<int > fa(m * m);
        iota(fa.begin(), fa.end(), 0);
        function<int(int) > find = [&](int x) { return fa[x]^x? fa[x] = find(fa[x]): x; };
        auto to = [&](int i, int j) { return i * m + j; };
        int ans = 0;
        auto mer = [&](int i, int j) {
            i = find(i); j = find(j);
            if (i ^ j) fa[i] = j, ans--;
        };

        if (!k) For (i, 0, 2) For (j, 0, 2) mp[i][j] = a[i][j][0] - '0';
        else {
            For (i, 0, 1) For (j, 0, 1) mp[i][j] = a[i][j][0] - '0';
            For (k, 0, 1) {
                for (int i = 1, j = 2, s = 0; j < m; j += i==0, i ^= 1, s++)
                    mp[i + k][j] = a[k][2][s] - '0';
                for (int j = 1, i = 2, s = 0; i < m; i += j==0, j ^= 1, s++)
                    mp[i][j + k] = a[2][k][s] - '0';
            }
            rFor (i, 99, 88) ans = ans << 1 | (a[2][2][i] - '0');
        }
        For (i, 0, m - 1) For (j, 0, m - 1) ans += mp[i][j];
        For (i, 0, m - 1) For (j, 0, m - 1) if (mp[i][j]) {
            if (i + 1 < m && mp[i + 1][j]) mer(to(i, j), to(i + 1, j));
            if (j + 1 < m && mp[i][j + 1]) mer(to(i, j), to(i, j + 1));
        }
        if (k) {
            int lst = -1, k = 0;
            stack<int > stk;
            for (int i = 2, j = m - 1; i <= m; i += j==2, j -= j>2) {
                if (i == m || !mp[i][j]) {
                    if (~lst) {
                        if (a[2][2][k] == '1') {
                            int u = stk.top(); stk.pop();
                            mer(u, lst);
                        }
                        if (a[2][2][k + 1] == '1') stk.push(lst);
                        k += 2;
                    }
                    lst = -1;
                } else lst = to(i, j);
            }
        }

        if (k == n - 1) {
            For (i, 0, 99) res += (ans&1) + '0', ans >>= 1;
        } else {
            int lst = -1;
            vector<int > p;
            for (int i = 0, j = m - 1; i <= m; i += j==0, j -= j>0) {
                if (i == m || !mp[i][j]) {
                    if (~lst) p.pb(lst);
                    lst = -1;
                } else lst = to(i, j);
            }
            For (i, 0, (int)p.size() - 1) {
                string x = "00";
                For (j, 0, i - 1) if (find(p[j]) == find(p[i])) x[0] = '1';
                For (j, i + 1, (int)p.size() - 1) if (find(p[j]) == find(p[i])) x[1] = '1';
                ans -= x[0]=='0';
                res += x;
            }
            while (res.size() < 88) res += '0';
            For (i, 88, 99) res += (ans&1) + '0', ans >>= 1;
        }
    } else if (i == o) {
        res = a[2][0];
        if (!k) res = a[2][1][0] + res;
        res = a[0][1][0] + (a[0][0][0] + (a[1][1][0] + (a[1][0][0] + res)));
        res.resize(100);
    } else if (j == o) {
        res = a[0][2];
        if (!k) res = a[1][2][0] + res;
        res = a[1][0][0] + (a[0][0][0] + (a[1][1][0] + (a[0][1][0] + res)));
        res.resize(100);
    } else res = a[0][0];
    return res;
}
