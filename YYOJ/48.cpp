#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=3e6+5, MACH=2;

int T,n,trie[N][MACH],triesiz,ans;
ull x;

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

int find(ull x){
	vector<int> di;
	for(int i=0; i<32; i++) di.push_back(x%2), x/=2;
	int u=0;
	ull res=0;
	for(int i=31; i>=0; i--){
		res*=2;
		int ch=di[i];
		if(trie[u][!ch]) res++, u=trie[u][!ch];
		else u=trie[u][ch];
	}
	return res;
}

void insert(ull x){
	vector<int> di;
	for(int i=0; i<32; i++) di.push_back(x%2), x/=2;
	int u=0;
	for(int i=31; i>=0; i--){
		int ch=di[i];
		if(!trie[u][ch]) trie[u][ch]=++triesiz;
		u=trie[u][ch];
	}
}

int main(){
	read(n);
	for(int i=1; i<=n; i++){
		read(x);
		ans=max(ans, find(x));
		insert(x);
	} 
	printf("%d", ans);
	return 0;
} 
