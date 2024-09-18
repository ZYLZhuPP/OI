#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e4+5;

int n,m,h,t,q[N];
ll a[N],f[2][N];
ll *f0,*f1;

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

ll test1(int x, int y){
    return (f0[y]-f0[x]+a[y+1]*a[y+1]-a[x+1]*a[x+1]);
}

ll test2(int x, int y){
    return 2*(a[y+1]-a[x+1]);
}

ll test(int x, int y, ll z){
	return test1(x,y)-z*test2(x,y);
}

int main(){
	read(n); read(m);
	for(int i=1; i<=n; i++) read(a[i]);
	sort(a+1, a+n+1);
	f0=f[0]; f1=f[1];
    for(int i=1; i<=n; i++) f1[i]=(a[i]-a[1])*(a[i]-a[1]);
	for(int i=2; i<=m; i++){
		swap(f0, f1);
		h=1; t=0;
		for(int j=i; j<=n; j++){
			while(h<t && test1(q[t-1],q[t])*test2(q[t],j-1)>=test1(q[t],j-1)*test2(q[t-1],q[t])) t--;
			q[++t]=j-1;
			while(h<t && test(q[h], q[h+1], a[j])<=0) h++;
			f1[j]=f0[q[h]]+(a[j]-a[q[h]+1])*(a[j]-a[q[h]+1]);
		}
	}
	printf("%lld", f1[n]);
	return 0;
}
