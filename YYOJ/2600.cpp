#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
bitset<N> b[N], bb[N];
const int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };

int n, m, col, cnt, ans;
int c[N][N];
char ch;

inline void dfs1(int x, int y) {
    c[x][y] = col;
    cnt++;
    for(int k = 0, _x, _y; k < 4; k++) {
        _x = x + dx[k], _y = y + dy[k];
        if(!c[_x][_y] && b[_x][_y]) dfs1(_x, _y);
    }
}

inline bool check(int x1, int y1, int x2, int y2) {
    bool flag = 1;
    bb[x1][y1] = 1;
    for(int k = 0, _x1, _y1, _x2, _y2; flag && k < 4; k++) {
        _x1 = x1 + dx[k], _y1 = y1 + dy[k], _x2 = x2 + dx[k], _y2 = y2 + dy[k];
        if(!bb[_x1][_y1] && b[_x1][_y1]) {
            if(!b[_x2][_y2]) flag = 0;
            else flag &= check(_x1, _y1, _x2, _y2);
        }
    }
    bb[x1][y1] = 0;
    return flag;
}


inline void solve() {
    col = ans = 0;
    scanf("%d%d", &n, &m);
    for(int j = 0; j <= m + 1; j++) b[0][j] = b[n + 1][j] = 0;
    for(int i = 1; i <= n; i++) {
        b[i][0] = b[i][m + 1] = 0;
        for(int j = 1; j <= m; j++) {
            ch = getchar(); while(ch != '.' && ch != 'O') ch = getchar();
            b[i][j] = (ch == '.');
            c[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        if(!c[i][j] && b[i][j]) {
            cnt = 0;
            col++;
            dfs1(i, j);
            if(cnt > (n * m) / 2) { ans += cnt; continue; }
            bool flag = 0;
            for(int ii = 1; !flag && ii <= n; ii++) for(int jj = 1; !flag && jj <= m; jj++) 
                if(c[i][j] != c[ii][jj] && b[ii][jj]) flag |= check(i, j, ii, jj);
            if(!flag) ans += cnt;
        }
    printf("%d\n", ans);
}

int main() {
    int T; scanf("%d", &T);
    while(T--) solve();
    
    return 0;
}
