#include<bits/stdc++.h>
using namespace std;

const int N=1e5, MA=50;

int n,cnt[MA+5][2*N+5],up[MA+5][2*N+5],last[MA+5],x;
long long ans;

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

int main(){
	for(int i=1; i<=MA; i++) last[i]=N, cnt[i][N]=1;
	read(n);
	for(int i=1; i<=n; i++){
		read(x);
		for(int j=1; j<=MA; j++)if(j^x){
			int ne=last[j]+1;
			up[j][ne]=up[j][last[j]]-cnt[j][ne];
			cnt[j][ne]++;
			ans+=up[j][last[j]=ne];
		}else{
			int ne=last[j]-1;
			up[j][ne]=up[j][last[j]]+cnt[j][last[j]];
			cnt[j][ne]++;
			ans+=up[j][last[j]=ne];
		}
	}
	printf("%lld", ans);
	return 0;
}
