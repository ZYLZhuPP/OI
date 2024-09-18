#include<bits/stdc++.h>
using namespace std;

typedef vector<int >::iterator It;

int n;
vector<int> a;

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

void init(){
	a.reserve(n+1);
}

bool cmp(int X, int Y){
	return X<Y;
}

template<class C> void clear(C &x){C().swap(x);}


#define fo() for(auto &x: a)

int main(){
	read(n);
	init();
	for(int i=1; i<=n; i++){
		int x; read(x); a.push_back(x);
	}
	fo() cout<<x<<endl;
	clear(a);
	fo() cout<<x<<endl;
	return 0;
} 
