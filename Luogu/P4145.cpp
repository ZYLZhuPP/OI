#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int maxn=1e5+10;
int n,m,cnt;
int a[maxn];
struct node{
	int l,r;
	int sum,mx;
}t[maxn<<2];
inline void upd(int i){
	t[i].sum=t[i<<1].sum+t[i<<1|1].sum;
	t[i].mx=max(t[i<<1].mx,t[i<<1|1].mx);
}
inline void build(int i,int l,int r){
	t[i].l=l,t[i].r=r;
	if(l==r){
//		scanf("%lld",&t[i].sum);
		t[i].mx=t[i].sum=a[l];
		return;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	upd(i);
}
inline void change(int i,int l,int r){
	if(t[i].l>r||t[i].r<l||t[i].mx==1)return;
	if(t[i].l==t[i].r){
		t[i].sum=floor(sqrt(t[i].sum));
		t[i].mx=t[i].sum;
		return ;
	}
	change(i<<1,l,r);
	change(i<<1|1,l,r);
	upd(i);
}
inline int query(int i,int l,int r){
	if(t[i].l>r||t[i].r<l)return 0;
	if(l<=t[i].l&&t[i].r<=r)return t[i].sum;
	return query(i<<1,l,r)+query(i<<1|1,l,r);
}
inline void init(){
//	for(int i=0;i<=4e5;i++)t[i].sum=0;
	memset(t,0,sizeof(t)); 
}
inline void ipt(){
	++cnt;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
//	printf("Case #%lld:\n",cnt);
	build(1,1,n);
}
inline void solve(){
	scanf("%lld",&m);
	while(m--){	
		int op,l,r;
		scanf("%lld%lld%lld",&op,&l,&r);
		if(l>r)swap(l,r);
		if(op==0)change(1,l,r);
		else {
			int ans=query(1,l,r);
			printf("%lld\n",ans);
		}
	}
}
signed main(){
	scanf("%lld",&n);
	init();
	ipt();
	solve();
	return 0;
}
