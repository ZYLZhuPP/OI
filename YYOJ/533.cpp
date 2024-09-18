#include<bits/stdc++.h>
#include<time.h>
using namespace std;

typedef long long ll;

const int N=(1<<15)+5;
const int INF=INT_MAX/2; 

struct Point{
	int lc,rc,bst,heap;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define bst(x) t[x].bst
	#define heap(x) t[x].heap
}t[N];

struct line{
	int head=-1,tail=-1;
}avail;

int tt,root=0,n,x;
ll ans;
int ava[N];

#define head avail.head
#define tail avail.tail

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

int addavail(int k)
{
	tail=(tail+1)%N;
	ava[tail]=k;
}

int getavail()
{
	if(head^tail){
		head=(head+1)%N;
		return ava[head];
	}
	else return ++tt;
}

void turnr(int &k)
{
	int p=lc(k);
	lc(k)=rc(p),rc(p)=k;
	k=p;
}

void turnl(int &k)
{
	int p=rc(k);
	rc(k)=lc(p),lc(p)=k;
	k=p;
}

int getrand()
{
	return rand()*rand()+rand();
}

void insert(int &k,int key)
{
	if(!k){
		k=getavail();
		bst(k)=key;
		heap(k)=getrand();
		lc(k)=lc(k)=0;
		return;
	}
	if(bst(k)==key);
	else if(key<bst(k)){
		insert(lc(k),key);
		if(heap(k)>heap(lc(k)))
			turnr(k);
	}else{
		insert(rc(k),key);
		if(heap(k)>heap(rc(k)))
			turnl(k);
	}
}

int getlast(int key)
{
	int x=root,s=-INF;
	while(x){
		if(bst(x)<=key)
			s=bst(x),x=rc(x);
		else
			x=lc(x);
	}
	return s;
}

int getnext(int key)
{
	int x=root,s=INF;
	while(x){
		if(bst(x)>=key)
			s=bst(x),x=lc(x);
		else
			x=rc(x);
	}
	return s;
}

int main()
{
	srand(time(0));
	read(n);
	read(x);
	insert(root,x);
	ans=x;
	for(int i=2;i<=n;i++){
		read(x);
		ans+=min(abs(x-getlast(x)),abs(getnext(x)-x));
		insert(root,x);
	}
	printf("%lld",ans);
}
