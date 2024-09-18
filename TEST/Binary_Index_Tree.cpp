#include<bits/stdc++.h>
using namespace std;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

template<class C=int>
class BIT{
public:
	const int N;
	BIT(int siz): N(siz){
		tr.resize(N+1);
	}
	BIT(vector<C > in): N(in.size()-1), tr(in){
		for(int pos=1; pos<=N; pos++){
			int pos_=pos+lowbit(pos);
			if(pos_<=N) tr[pos_]+=tr[pos];
		}
	}
	void add(int pos, C ad){
		for(; pos<=N; pos+=lowbit(pos)) tr[pos]+=ad;
	}
	C operator () (int pos) const{
		C res=0;
		for(; pos>0; pos-=lowbit(pos)) res+=tr[pos];
		return res;
	}
	C operator () (int l, int r) const{
		return (*this)(r)-(*this)(l-1);
	}
	const C operator [] (int pos) const{
		return tr[pos];
	}
private:
	vector<C > tr;
	inline int lowbit(int x) const{return x&-x;}
};

int main(){
	vector<int > a(11);
	for(int i=1; i<=10; i++) io>>a[i];
	BIT<> tr(a);
	cout<<tr(1,3);
	return 0;
} 
