#include<bits/stdc++.h>
using namespace std;

const int N=205;
const int INF=INT_MAX/2;

int n,a[N<<1],sum[N<<1];
int f[2][N<<1][N<<1]; 

#define gc() getchar()

template<class T>
inline void read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(;!isdigit(ch);ch=gc())
		if(!(ch^'-'))
			f=-1;
	for(;isdigit(ch);ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
}

int solve1(int l,int r){
	if(l==r)
		return 0;
	if(f[0][l][r]^-1)
		return f[0][l][r];
	int res=INF;
	for(int i=l;i<r;i++)
		res=min(res,solve1(l,i)+solve1(i+1,r));
	return f[0][l][r]=res+sum[r]-sum[l-1];
}

int solve2(int l,int r){
	if(l==r)
		return 0;
	if(f[1][l][r]^-1)
		return f[1][l][r];
	int res=-INF;
	for(int i=l;i<r;i++)
		res=max(res,solve2(l,i)+solve2(i+1,r));
	return f[1][l][r]=res+sum[r]-sum[l-1];
}

int main(){
	read(n);
	memset(f,-1,sizeof(f));
	for(int i=1;i<=n;i++){
		read(a[i]);a[n+i]=a[i];
	}
	for(int i=1;i<=n<<1;i++)
		sum[i]=sum[i-1]+a[i];
	int ans1=INF,ans2=-INF;
	for(int i=1;i<=n;i++){
		ans1=min(ans1,solve1(i,i+n-1));
		ans2=max(ans2,solve2(i,i+n-1));
	}
	printf("%d\n%d",ans1,ans2);
	return 0;
}
