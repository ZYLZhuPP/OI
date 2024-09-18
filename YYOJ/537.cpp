#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

struct Point{
	int son[2],bst,heap,siz,cnt;
	bool tab;
	#define lc(x) tr[x].son[0]
	#define rc(x) tr[x].son[1]
	#define son(x,y) tr[x].son[y]
	#define bst(x) tr[x].bst
	#define heap(x) tr[x].heap
	#define siz(x) tr[x].siz
	#define cnt(x) tr[x].cnt
	#define tab(x) tr[x].tab
}tr[N];

int n,m,root,l,r;

namespace Pt_avail{
	int ptnum=0,head=-1,tail=-1;
	int ava[N];
	
	int add_avail(int k){
		tail=(tail+1)%N;
		ava[tail]=k;
	}
	
	int get_avail(){
		if(head!=tail){
			head=(head+1)%N;
			return ava[head];
		}
		else 
			return ++ptnum;
	}
}
using Pt_avail::add_avail;
using Pt_avail::get_avail;

#define gc() getchar()

template<class T>
inline void read(T &x)
{
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

void mark(int now){
	tab(now)=!tab(now);
	swap(lc(now),rc(now));
}

void pushdown(int now){
	if(!tab(now))
		return;
	mark(lc(now));
	mark(rc(now));
	tab(now)=0; 
}

void pushup(int now){
	siz(now)=siz(lc(now))+siz(rc(now))+cnt(now); 
}

void split_rank(int now,int rank,int &u,int &v){
	if(!now){
		u=v=0;
		return;
	}
	pushdown(now);
	int &lc=lc(now),&rc=rc(now);
	if(siz(lc)<rank){
		split_rank(rc,rank-siz(lc)-cnt(now),rc,v);
		u=now;
	}else{ 
		split_rank(lc,rank,u,lc);
		v=now;
	}
	pushup(now);
}

int merge(int u,int v){
	if(!u || !v)
		return u+v;
	if(heap(u)<heap(v))
		return pushdown(u),rc(u)=merge(rc(u),v),pushup(u),u;
	return pushdown(v),lc(v)=merge(u,lc(v)),pushup(v),v;
}

void overturn(int l,int r){
	int x,y,z;
	split_rank(root,r,y,z);
	split_rank(y,l-1,x,y);
	mark(y);
	root=merge(x,merge(y,z));
}

int get_rand(){
	return rand()*rand()+rand();
}

int new_built(int val){
	int u=get_avail();
	siz(u)=cnt(u)=1;
	bst(u)=val;
	heap(u)=get_rand(); 
	return u;
}

void insert_back(int val){
	int u=new_built(val);
	root=merge(root,u);
}

void write(int now){
	if(now){
		pushdown(now);
		write(lc(now));
		printf("%d ",bst(now));
		write(rc(now));
	}
}

int main(){
	srand(time(0));
	read(n);read(m);
	for(int i=1;i<=n;i++)
		insert_back(i);
	for(int i=1;i<=m;i++){
		read(l);read(r);
		overturn(l,r);
	}
	write(root);
	return 0;
} 
