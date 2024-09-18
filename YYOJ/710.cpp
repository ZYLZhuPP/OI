#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
const int INF=INT_MAX;

long long n,L,R,f[N],a[N],q[N],h,t;

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
	memset(f, 127, sizeof(f));
	read(n); read(L); read(R);
	for(int i=1; i<=n; i++) read(a[i]);
	f[0]=0;
	h=1;
	for(int i=1; i<=n; i++){
		if(h<=t && q[h]<i-R-1) h++;
		if(i>L){
			while(h<=t && f[q[t]]>=f[i-L-1]) t--;
			q[++t]=i-L-1;
			f[i]=f[q[h]]+a[i];
		}
	}
	if(f[n]>=INF) printf("-1");
	else printf("%lld", f[n]);
	return 0;
} 
