#include<cstdio>
#include<algorithm>
#define Mod (20170408)
using namespace std;

const int MAXN = 105, MAXM = 20000007;

int n, m, P;

class Matrix {
    private : 
    int a[MAXN][MAXN];
    public : 
    int n, m;
    inline int& operator () (const int &x, const int &y) {
        return a[x][y];
    }
    inline void Init(int x, int y) {
        n = x, m = y;
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
                a[i][j] = 0;
    }
    inline void Unit() {
        for (int i = 1; i <= n; ++ i)
            a[i][i] = 1;
    }
    inline Matrix operator * (Matrix &B) {
        Matrix C; C.Init(n, m); 
        for (int i = 1; i <= n; ++ i)
            for (int k = 1; k <= m; ++ k)
                for (int j = 1; j <= B.m; ++ j)
                    C(i, j) = (C(i, j) + 1ll * a[i][k] * B(k, j) % Mod) % Mod;
        return C;
    }
}A, B;
inline Matrix fsp(Matrix x, int p) {
    Matrix res; res.Init(P, P); res.Unit();
    for (; p; p >>= 1) {
        if (p & 1) res = res * x;
        x = x * x;
    } 
    return res;
}

int ct, prim[MAXM];
bool vis[MAXM];
int cnt[2][MAXN];
inline void Euler() {
    cnt[0][1] = cnt[1][1] = 1;
    for (int i = 2; i <= m; ++ i) {
        ++ cnt[0][i % P];
        if (!vis[i]) prim[++ ct] = i;
        else ++ cnt[1][i % P];
        for (int j = 1; j <= ct && prim[j] * i <= m; ++ j) {
            vis[i * prim[j]] = 1;
            if (i % prim[j] == 0) break;
        }
    }
}
inline void Prew() {
    A.Init(P, P); B.Init(P, P);
    for (int j = 1; j <= P; ++ j) 
        for (int t = 0, i = j; t < P; ++ t, i = i % P + 1)
            A(i, j) = cnt[0][t], B(i, j) = cnt[1][t];
}

int main()
{
    scanf ("%d%d%d", &n, &m, &P);
    Euler(); Prew();
    A = fsp(A, n); B = fsp(B, n);
    return printf ("%d\n", (A(1, 1) - B(1, 1) + Mod) % Mod), 0;
}
