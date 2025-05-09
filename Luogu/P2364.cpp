#include<bits/stdc++.h>
using namespace std;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    inline IO& operator >> (char *x){
        while(c<33) c=gc();
        for(; c>32; c=gc()) (*x++)=c;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
} io;

char a[107], b[107], c[107];
int la, lb, lc;
int dp[107][107][107];
string ans[107][107][107];

int main() {
    io >> (a + 1) >> (b + 1) >> (c + 1);
    la = strlen(a + 1), lb = strlen(b + 1), lc = strlen(c + 1);

    for (int i = 1; i <= la; i++)
        for (int j = 1; j <= lb; j++)
            for (int k = 1; k <= lc; k++) {
                if (a[i] == b[j] && b[j] == c[k])
                    if (dp[i - 1][j - 1][k - 1] + 1 > dp[i][j][k]) {
                        dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                        ans[i][j][k] = ans[i - 1][j - 1][k - 1] + a[i];
                    }
                    
                if (dp[i - 1][j][k] > dp[i][j][k]) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    ans[i][j][k] = ans[i - 1][j][k];
                }
                
                if (dp[i][j - 1][k] > dp[i][j][k]) {
                    dp[i][j][k] = dp[i][j - 1][k];
                    ans[i][j][k] = ans[i][j - 1][k];
                }
                
                if (dp[i][j][k - 1] > dp[i][j][k]) {
                    dp[i][j][k] = dp[i][j][k - 1];
                    ans[i][j][k] = ans[i][j][k - 1];
                }
            }

    cout << ans[la][lb][lc];
    return 0;
}
