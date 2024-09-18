#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=22;
const ll Mo=1e9+7;

struct DP{
	ll cnt,su,po;
}f[N][8][8];

ll t,l,r,rest7[N][10],restmo[N][10];
vector<int> di;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(;!isdigit(ch);ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(;isdigit(ch);ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

DP dfs(int pos, ll su, ll re, bool done){
	if(pos==-1) return (su && re)?(DP){1, 0, 0}:(DP){0, 0, 0};
	if(!done && ~f[pos][su][re].cnt) return f[pos][su][re];
	int limit=done?di[pos]:9;
	DP res={0, 0, 0};
	for(int i=0; i<=limit; i++)if(i^7){
		ll now=restmo[pos][i];
		DP ret=dfs(pos-1, (su+i)%7, (re+rest7[pos][i])%7, done && (i==limit));
		(res.cnt+=ret.cnt)%=Mo;
		(res.su+=ret.su+ret.cnt*now%Mo)%=Mo;
		(res.po+=ret.po+2*ret.su*now%Mo+ret.cnt*(now*now%Mo)%Mo)%=Mo;
	}
	if(!done) f[pos][su][re]=res;
	return res;
}

DP solve(ll x){
	di.clear();
	if(!x) return {0, 0, 0};
	while(x) di.push_back(x%10), x/=10;
	return dfs(di.size()-1, 0, 0, 1); 
} 

void init(){
	ll k=1;
	for(int pos=0; pos<N; pos++){
		for(int i=0; i<=9; i++){
			rest7[pos][i]=k*i%7;
			restmo[pos][i]=k*i%Mo;
		}
		k*=10;
	}
}

int main(){
	memset(f, -1, sizeof(f));
	init();
	read(t);
	while(t--){
		read(l); read(r);
		printf("%lld\n", (solve(r).po-solve(l-1).po+Mo)%Mo);
	}
	return 0;
}
