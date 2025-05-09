#include<bits/stdc++.h>

const int maxn = 1e5;
int n, f[maxn + 5];
char s[maxn + 5];
const int numlen[8] = {1, 2, 3, 2, 1, 2, 3, 4};
const char num[8][5] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII"};

void solve() {
    scanf("%s", s);
    n = strlen(s);
    f[n] = 0;
    for(int i = n - 1; i >= 0; -- i) {
        f[i] = 1e9;
        for(int j = 0; j <= 7; ++ j) {
            if(i + numlen[j] - 1 >= n) {
                continue;
            }

            bool ok = true;
            for(int k = 0; k < numlen[j]; ++ k) {
                if(num[j][k] != s[i + k]) {
                    ok = false;
                    break;
                }
            }

            if(ok) {
                f[i] = std::min(f[i], f[i + numlen[j]] + 1);
            }
        }
    }

    int i = 0;
    while(i < n) {
        for(int j = 0; j <= 7; ++ j) {
            if(i + numlen[j] - 1 >= n) {
                continue;
            }

            bool ok = true;
            for(int k = 0; k < numlen[j]; ++ k) {
                if(num[j][k] != s[i + k]) {
                    ok = false;
                    break;
                }
            }

            if(ok && f[i] == f[i + numlen[j]] + 1) {
                putchar('0' + j + 1);
                i = i + numlen[j];
                break;
            }
        }
    }
    putchar('\n');
    return;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t --) {
        solve();
    }
    return 0;
}
