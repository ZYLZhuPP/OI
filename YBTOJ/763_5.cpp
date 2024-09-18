#include<bits/stdc++.h>
#define pb push_back
#define REP(i,n) for(int i=0;i<(n);i++)
using namespace std;
typedef long long ll;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

const ll inf=4e18;
const int N=750005;
struct ask{
	int *a,*b,n;
	void c(){ n=0,a=b=NULL; }
	void pb(int x,int y){
		if((n&-n)==n){
			a=(int*)realloc(a,(n*2+1)*(sizeof n));
			b=(int*)realloc(b,(n*2+1)*(sizeof n));
		}
		a[n]=x,b[n++]=y;
	}
} q[N];
struct list{
	int *a,n;
	void c(){ n=0,a=NULL; }
	void pb(int x){
		if((n&-n)==n){
			a=(int*)realloc(a,(n*2+1)*(sizeof n));
		}
		a[n++]=x;
	}
} li[N];
struct dsu{
	int p[N];
	void r(int n){ REP(i,n+1) p[i]=i; }
	inline int f(int x){ return p[x]==x?x:p[x]=f(p[x]); }
	void s(int x,int y){ p[f(x)]=f(y); }
} L,R,p;
int s[N],*h,n,Q,m,tim;
vector<ll> ans;
ll f[N],g[N];

void era(int x){
	if(R.f(x)!=x) return;
	R.s(x,x+1);	if(x) L.s(x,x-1);
}
int pre(int x){
	int y=(x?L.f(x-1):0);
	return !y&&R.f(y)!=y?-1:y;
}
ll val(int x,int y){
	return f[x]+(ll)h[x]*y;
}
void upd(int x,int y){
	if(x==-1) return;
	ll t=(h[x]==h[y]?(f[x]>=f[y]?-1:N):(f[y]-f[x]-1)/(h[x]-h[y])+1);
	if(t<=tim) era(x),upd(pre(y),y);
	else if(t<N) li[t].pb(y);
}

void solve(){
	L.r(n),R.r(n),p.r(n),m=0;
	REP(i,n){
		ll mn=inf;
		while(m&&h[s[m]]<h[i]){
			mn=min(mn,val(s[m],i-1)+h[i]);
			p.s(s[m],i),era(s[m--]);
		}
		g[i]=(!m?(ll)h[i]*(i+1):g[s[m]]+(ll)h[i]*(i-s[m]));
		f[i]=min(mn,g[i])-(ll)h[i]*i;
		s[++m]=i;
		while(pre(i)!=-1&&val(pre(i),i)>=val(i,i)) era(pre(i));
		tim=i,upd(pre(i),i);
		REP(k,li[i].n){
			int x=li[i].a[k];
			if(R.f(x)!=x) continue;
			era(pre(x)),upd(pre(x),x);
		}
		REP(k,q[i].n){
			int j=q[i].a[k],id=q[i].b[k],mx=p.f(j);
			if(mx==i) continue;
			ans[id]=min(ans[id],val(R.f(mx+1),i)
					   -g[mx]+(ll)h[mx]*(mx-j+1));
		}
		li[i].c(),q[i].c();
	}
}
int main() {
    vector<int> H,L,R;
	cin >> n >> Q;
	int x, y;
	REP(i, n) io >> x, H.pb(x);
	REP(i, Q) io >> x >> y, L.pb(x), R.pb(y);
	h=&H.front();
	ans.resize(Q);
	REP(i,Q) ans[i]=(L[i]==R[i]?H[L[i]]:inf),q[R[i]].pb(L[i],i);
	solve(),reverse(H.begin(),H.end()),h=&H.front();
	REP(i,Q) q[n-1-L[i]].pb(n-1-R[i],i);
	solve();
	for (auto &x : ans) printf("%lld\n", x);
	return 0;
}

