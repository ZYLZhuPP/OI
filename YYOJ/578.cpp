#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
const int INF=INT_MAX;

int n,m,ans=-INF,a[N],s[N];
int q[N],h,t;

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
	read(n); read(m);
	for(int i=1; i<=n; i++) read(a[i]), s[i]=s[i-1]+a[i];
	h=1;
	for(int i=1; i<=n; i++){
		int ne=i-1;
		if(h<=t && q[h]<i-m) h++;
		while(h<=t && s[q[t]]>=s[ne]) t--;
		q[++t]=ne;
		ans=max(ans, s[i]-s[q[h]]);
	}
	printf("%d", ans);
	return 0;
} 
