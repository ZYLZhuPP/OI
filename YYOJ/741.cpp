#include<bits/stdc++.h>
using namespace std;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int ans = -1, sum[10], a[10][10], b[10], vh[10][10], vl[10][10], vg[10][10];

int cmp(int a, int b) {
    return sum[a] < sum[b];
}

int w(int i, int j) {
    return 10 - max(abs(i-4), abs(j-4));
}

int f(int i, int j) {
    return i / 3 * 3 + j / 3;
}

void dfs(int k, int num) {
    if (num + (81 - k)*81 < ans)
        return;
    
    if (k == 81) {
        ans = max(ans, num);
        return;
    }

    int i = b[k / 9], j = k % 9, b = f(i, j);

    if (a[i][j])
        dfs(k + 1, num + a[i][j]*w(i, j));

    for (int l = 1; l <= 9; l++) {
        if (!vh[i][l] && !vl[j][l] && !vg[b][l]) {
            vh[i][l] = vl[j][l] = vg[b][l] = 1;
            dfs(k + 1, num + l*w(i, j));
            vh[i][l] = vl[j][l] = vg[b][l] = 0;
        }
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        b[i] = i;

        for (int j = 0; j < 9; j++) {
            io >> a[i][j];

            if (a[i][j]) {
                vh[i][a[i][j]] = vl[j][a[i][j]] = vg[f(i, j)][a[i][j]] = 1;
            } else
                sum[i]++;
        }
    }

    sort(b, b + 9, cmp);
    dfs(0, 0);
    printf("%d", ans);
    return 0; 
}
