#include<bits/stdc++.h>
using namespace std;

typedef long long ll; 

const int N=34;

ll a,b,f[N][N<<1][2];
vector<int> di;

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

ll dfs(int pos, int d, bool done, bool zero){
	if(pos==-1) return d>=0?1:0;
	if(!done && ~f[pos][d+N][zero]) return f[pos][d+N][zero];
	int limit=done?di[pos]:1;
	ll res=0;
	res+=dfs(pos-1, d+zero, done && !limit, zero);
	if(limit) res+=dfs(pos-1, d-1, done, 1);
	if(!done) f[pos][d+N][zero]=res;
	return res;
}

ll solve(ll x){
	di.clear();
	while(x) di.push_back(x%2), x/=2;
	return dfs(di.size()-1, 0, 1, 0);
}

int main(){
	memset(f, -1, sizeof(f));
	read(a); read(b);
	printf("%lld", solve(b)-solve(a-1));
	return 0;
}
