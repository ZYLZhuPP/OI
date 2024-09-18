#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1; 
}

ll n,k,ans,g[N],pos[N],gsiz,h[N],s[N];

ll gcd(ll x, ll y){return y?gcd(y,x%y):x;}

int main(){
    read(n); read(k);
    for(int i=1; i<=n; i++) read(h[i]), s[i]=s[i-1]+h[i];
    for(int i=1; i<=n; i++){
        for(int j=1; j<=gsiz; j++) g[j]=gcd(g[j], h[i]);
        g[++gsiz]=h[i]; pos[gsiz]=i;
        int nesiz=0;
        for(int j=1; j<=gsiz; j++)if(g[j]!=g[j-1]) g[++nesiz]=g[j], pos[nesiz]=pos[j];
        gsiz=nesiz;
        for(int j=1; j<=gsiz; j++)if(i-pos[j]+1>=k) ans=max(ans, g[j]*(s[i]-s[pos[j]-1]));
    }
    printf("%lld", ans);
    return 0;
}
