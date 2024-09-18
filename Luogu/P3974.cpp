#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }

const int N = 1e3 + 7;

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
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int T, n, m;
int a[N][N];
long long f[N][N];

int main() {
    io >> T;
    while (T--) {
        memset(f, 0, sizeof f);
        io >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                io >> a[i][j];
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= 1; j--)
                f[i][j] = max(max(f[i-1][j], f[i][j+1]), f[i-1][j+1]+a[i][j]);
        printf("%lld\n", f[n][1]);
    }
    return 0;
}
