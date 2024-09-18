#include<bits/stdc++.h>
using namespace std;

typedef set<int >::iterator It;

const int N=2e5+5;

int n,h[N],pos[N],ans,ad[N];

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

set<int > tr;
void init(){
	pos[0]=0;
	pos[N-1]=-1;
	tr.insert(0);
	tr.insert(N-1);
	for(int i=1; i<=n; i++){
		It it=upper_bound(tr.begin(), tr.end(), h[i]);
		int r=*it, l=*(--it);
		if(pos[r]>pos[l]) ad[h[i]]++;
		tr.insert(h[i]);
	}
}

int main(){
	read(n);
	for(int i=1; i<=n; i++) read(h[i]), pos[h[i]]=i;
	init();
	puts("0");
	for(int i=1; i<=n; i++){
		if(pos[i]<pos[i-1]) ans--;
		ans+=ad[i];
		printf("%d\n", ans);
	}
	return 0;
} 
