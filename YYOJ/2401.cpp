#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

int l[13][10], r[13][10], p[4][4][10];
char a[13][15];

int main() {
    For (i, 0, 12) scanf("%s", a[i]);
    For (i, 0, 12) For (j, 0, 12) {
        if (i % 4 == 0 || j % 4 == 0 || a[i][j] == '.') continue;
        int x = i / 4, y = j / 4, c = a[i][j] ^ 48;
        if (l[i][c]++ || r[j][c]++ || p[x][y][c]++) { puts("GRESKA"); return 0; }
    }
    puts("OK");

    return 0;
}
