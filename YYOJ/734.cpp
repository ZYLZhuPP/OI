#include<bits/stdc++.h>
using namespace std;

const int INF = INT_MAX / 3;

int n,m,r[30],h[30],Min = INF;

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

void dfs(int c, int sn, int S){
	if(c == m+1){
		if(sn > 0) return;
		Min = min(Min, r[1]*r[1]+S);
		return;
	}
	if(S+r[1]*r[1]+(m-c+1)*2 > Min) return;
	if(sn > (r[c-1]-1)*(r[c-1]-1)*(m-c+1)*(h[c-1]-1)) return;
	for(int i=r[c-1]-1; i>=m-c+1; i--){
		for(int j=h[c-1]-1; j>=m-c+1; j--){
			if(sn >= i*i*j){
				r[c] = i;
				h[c] = j;
				dfs(c+1, sn-i*i*j, S+2*i*j);
			}
		}
	}
} 

int main(){
	io>>n>>m;
	r[0] = sqrt(n);
	h[0] = n;
	dfs(1, n, 0);
	printf("%d", Min^INF? Min: 0);
	return 0; 
} 
