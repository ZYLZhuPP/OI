#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e5+5;

ll n,k,a[N],s[N],f[N];
ll h,t,q[N];

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

int main(){
    read(n); read(k);
    for(int i=1; i<=n; i++) read(a[i]), s[i]=s[i-1]+a[i];
    h=1;
    for(int i=1; i<=k; i++) f[i]=s[i];
    for(int i=2; i<=n; i++){
        if(h<=t && q[h]<i-k-1)h++;
        while(h<=t && (f[q[t]]-s[q[t]+1])<=(f[i-2]-s[i-1]))t--;
        q[++t]=i-2;
        if(i>k) f[i]=f[q[h]]-s[q[h]+1]+s[i];
    }
    printf("%lld\n", f[n]);
    return 0;
}
