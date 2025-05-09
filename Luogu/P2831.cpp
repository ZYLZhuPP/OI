#include<bits/stdc++.h>
using namespace std;

const int N = 20;
const int STA = (1 << N) + 5;
const long double dd = 1e-18;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) f|=-!(c^45);
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline IO& operator >> (long double &x){
        long double p(1);
        for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
        for(x=0; isdigit(c); c=gc()) x=x*10+(c^48);
        if(!(c^46)) while(isdigit(c=gc())) x+=(c^48)*(p/=10); x*=f;
        return *this;
    } 
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int T, n, m, sta[N][N], Sta, f[STA], l, st[N][N];
long double x[N], y[N], a, b;

void init() {
    memset(f, 31, sizeof f);
    f[0] = 0;
    Sta = (1 << n) - 1;
}

int main() {
    io >> T;

    while (T--) {
        io >> n >> m;
        init();

        for (int i = 0; i < n; i++)
            io >> x[i] >> y[i];

        for (int i = 0; i < n; i++) {
            st[i][i] = (1 << i);

            for (int j = i + 1; j < n; j++) {
                st[i][j] = (1 << i);
                a = (y[i]*x[j] - y[j]*x[i]) / (x[i]*x[i]*x[j] - x[j]*x[j]*x[i]);

                if (a < 0) {
                    st[i][j] |= (1 << j);
                    b = (y[i]*x[j]*x[j] - y[j]*x[i]*x[i]) / (x[i]*x[j]*x[j] - x[j]*x[i]*x[i]);

                    for (int k = 0; k < n; k++)
                        if (k ^ i && k ^ j) {
                            if (fabs(x[k]*x[k]*a + b * x[k] - y[k]) < dd)
                                st[i][j] |= (1 << k);
                        }
                }
            }
        }

        for (int sta = 0; sta <= Sta; sta++) {
            l = -1;

            for (int i = 0; i < n; i++)
                if (!(sta & (1 << i))) {
                    l = i;
                    break;
                }

            if (~l) {
                for (int i = l; i < n; i++)
                    f[sta | st[l][i]] = min(f[sta | st[l][i]], f[sta] + 1);
            }
        }

        printf("%d\n", f[Sta]);
    }

    return 0;
}
