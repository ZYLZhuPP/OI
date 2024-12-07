#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX / 3;
const int N=105;

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

ll n,x,sum,ma = -INF,mi = INF,a[N];

void dfs(ll res, ll sum, ll s, ll p){
    if(res == 0){
        printf("%lld", s);
        exit(0);
    }
    if(sum == s){
        dfs(res-1, 0, s, ma);
        return;
    }
    for(int i=p; i>=mi; i--) if (a[i] && sum+i <= s){
        a[i]--;
        dfs(res, sum + i, s, i);
        a[i]++;
		if(sum == 0 || sum+i == s) break;
    }
}

int main(){
	io>>n;
    for(int i=1; i<=n; i++){
        io>>x;
        sum += x;
        a[x]++;
        ma = max(ma, x);
        mi = min(mi, x);
    }
    for(int i=ma; i<=sum/2; i++) if(sum%i == 0) dfs(sum / i, 0, i, ma);
    printf("%lld", sum);
    return 0;
}
