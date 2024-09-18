#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=5e4+5;
const int pN=6e3;

int n,ans,ma1[N],ma2[N];
int mip[N],pri[pN],cnt[N],psiz;
ll s[N];
int head[N],nxt[2*N],to[2*N],t;

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

void add(int u,int v){
	nxt[++t]=head[u];
	to[t]=v;
	head[u]=t;
}

void init_prime(){
	for(int i=2;i<=n;i++){
		if(mip[i]==0){
			mip[i]=i;
			pri[++psiz]=i;
			cnt[i]=1;
		}
		for(int j=1;j<=psiz;j++){
			if(pri[j]>mip[i]||pri[j]>n/i)
				break;
			mip[pri[j]*i]=pri[j];
			cnt[pri[j]*i]=mip[i]==pri[j]?cnt[i]+1:1;
		}
	}
}

ll get(int x,int y){
	return ((ll)pow(x,y+1)-1)/(x-1);
}

void init_edge(){
	s[1]=1;
	add(1,0);
	add(0,1);
	for(int i=2;i<=n;i++){
		s[i]=s[i/(int)pow(mip[i],cnt[i])]*get(mip[i],cnt[i]);
		if(s[i]-i<i){
			add(s[i]-i,i);
			add(i,s[i]-i); 
		}
	}
}

void init(){
	init_prime();
	init_edge();
}

void dfs(int u,int pre){
	for(int i=head[u];i;i=nxt[i])if(to[i]^pre){
		int v=to[i];
		dfs(v,u);
		if(ma1[u]<=ma1[v]+1){
			ma2[u]=ma1[u];
			ma1[u]=ma1[v]+1;
		}else if(ma2[u]<ma1[v]+1)
			ma2[u]=ma1[v]+1;
	}
	ans=max(ans,ma1[u]+ma2[u]);
}

int main(){
	read(n);
	init();
	dfs(1,-1);
	printf("%d",ans);
	return 0;
} 
