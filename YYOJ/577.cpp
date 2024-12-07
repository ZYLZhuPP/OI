#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int n,k,ans[2][N],a[N];
int mi[N],h1,t1;
int ma[N],h2,t2;

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
	h1=h2=1;
	for(int i=1; i<=n; i++) read(a[i]);
	for(int i=1; i<=n; i++){
		if(h1<=t1 && mi[h1]<i-k+1) h1++;
		while(h1<=t1 && a[mi[t1]]>=a[i]) t1--;
		mi[++t1]=i;
		if(h2<=t2 && ma[h2]<i-k+1) h2++;
		while(h2<=t2 && a[ma[t2]]<=a[i]) t2--;
		ma[++t2]=i;
		if(i>=k) ans[0][i]=mi[h1], ans[1][i]=ma[h2];
	}
	for(int p=0; p<=1; p++, printf("\n"))
	for(int i=k; i<=n; i++) printf("%d ", a[ans[p][i]]);
	return 0;
}
