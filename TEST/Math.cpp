#include<bits/stdc++.h>
using namespace std;
namespace MATH
{
	const int N=262144,L=18,mo=998244353,G=3;
	int mul(int x,int y){return 1ll*x*y%mo;}
	int add(int x,int y){return x+y<mo?x+y:x+y-mo;}
	int dec(int x,int y){return x-y<0?x-y+mo:x-y;}
	int ksm(int x,int y){int res=1,tmp=x;for(;y&1&&(res=mul(res,tmp)),y;y>>=1)tmp=mul(tmp,tmp);return res;}
	int rader[L+1][N],RN[L+1],g[L+1],Rg[L+1],rev[N];bool completion;	//rev[i]指的是i^(-1)
	void startUp()
	{
    	RN[0]=1;for(int i=1,t=ksm(2,mo-2);i<=L;i++)RN[i]=mul(RN[i-1],t);
    	for(int i=1;i<=L;++i)
	    	for(int j=0;j<(1<<i);++j)rader[i][j]=(rader[i][j>>1]>>1)|((j&1)<<(i-1));
    	for(int i=0;i<L;++i)g[i]=ksm(G,(mo-1)/(1<<i+1)),Rg[i]=ksm(g[i],mo-2);
    	for(int i=0;i<N;++i)rev[i]=ksm(i,mo-2);
    	completion=1;
	}	//必须
	struct poly
	{
    	int f[N];
    	poly(){memset(f,0,sizeof(f));}
		
    	void NTT(int op,int l)
		{
	    	assert(completion);
	    	int T=(1<<l);
	    	for(int i=0;i<T;++i)i<rader[l][i]&&(swap(f[i],f[rader[l][i]]),1);//printf("%d  ",rader[l][i]);putchar('\n');
	    	int i,j,k,w,W,t,p,a0,a1;
	    	for(i=1,p=0;i<T;i<<=1,++p)
		    	for(j=0,W=(op?Rg[p]:g[p]);j<T;j+=i<<1)
			    	for(w=1,a1=(a0=j)+i,k=0;k<i;++k,w=mul(w,W),++a0,++a1)
				    	t=mul(f[a1],w),f[a1]=dec(f[a0],t),f[a0]=add(f[a0],t);
	    	if(!op)return;
	    	for(int i=0;i<T;++i)f[i]=mul(f[i],RN[l]);
		}
    	void opp(int k){for(int i=0;i<(1<<k);++i)f[i]=mo-f[i];}
    	void show(int n){for(int i=0;i<n-1;++i)printf("%d ",f[i]);printf("%d\n",f[n-1]);}
    	void inte(int l){assert(completion);for(int i=(1<<l)-1;i;--i)f[i]=mul(f[i-1],rev[i]);f[0]=0;}	//1:不定积分，常数项为0;2:范围
    	void diff(int l){for(int i=0;i<(1<<l)-1;++i)f[i]=mul(f[i+1],i+1);f[(1<<l)-1]=0;}
	}A,B,C,D,E;
	void Padd(const poly &x,const poly &y,poly &z,int l){for(int i=0;i<(1<<l);++i)z.f[i]=add(x.f[i],y.f[i]);}
	void Pdec(const poly &x,const poly &y,poly &z,int l){for(int i=0;i<(1<<l);++i)z.f[i]=dec(x.f[i],y.f[i]);}
	void Pmul(poly &x,poly &y,poly &z,int l)	//引入的时候，大概率l要加1
	{
    	for(int i=0;i<(1<<l-1);++i)A.f[i]=x.f[i],B.f[i]=y.f[i];for(int i=(1<<l-1);i<(1<<l);++i)A.f[i]=B.f[i]=0;
    	A.NTT(0,l);B.NTT(0,l);for(int i=0;i<(1<<l);++i)z.f[i]=mul(A.f[i],B.f[i]);
    	z.NTT(1,l);
	}
	void Pinv(poly &x,poly &y,int l)
	{
    	assert(l<L&&(&x!=&y)&&x.f[0]);
    	memset(y.f,0,sizeof(int)*(1<<l));y.f[0]=ksm(x.f[0],mo-2);
    	for(int k=1;k<=l;++k)
		{
	    	Pmul(x,y,C,k+1);
	    	C.opp(k);C.f[0]=add(C.f[0],2);Pmul(C,y,y,k+1);	//x可能为k次多项式,要+1
		}
	}
	void ln(poly &x,poly &y,int l)
	{
    	assert(l<L&&(&x!=&y)&&x.f[0]==1);
    	Pinv(x,y,l);C=x;C.diff(l);Pmul(C,y,y,l+1);y.inte(l);	//若x是(1<<l)次的，不可把x^(1<<l)模掉，因为导完第(1<<l)次会下来
	}	//ln完常数项必是0
	void exp(poly &x,poly &y,int l)
	{
    	assert(l<L&&(&x!=&y)&&!x.f[0]);
    	memset(y.f,0,sizeof(int)*(1<<l));y.f[0]=1;
    	for(int k=1;k<=l;++k)
		{
	    	ln(y,D,k);Pdec(x,D,D,k);D.f[0]=add(D.f[0],1);Pmul(y,D,y,k+1);	//注意不要重名
		}
	}
	void Ppow(poly &x,int k,poly &y,int l)
	{
    	ln(x,y,l);memset(C.f,0,(1<<l)*sizeof(int));C.f[0]=k;Pmul(C,y,E,l+1);exp(E,y,l);
	}
}
MATH::poly x,res;
int read()
{
	int x=0,t=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')t=-t;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*t;
}
char getdig(){char ch;while(ch<'0'||ch>'9')ch=getchar();return ch;}
int main()
{
	MATH::startUp();
	int n=read(),k=0;
	char ch=getdig();while(ch>='0'&&ch<='9')k=MATH::add(MATH::mul(k,10),ch^48),ch=getchar();
	for(int i=0;i<n;++i)x.f[i]=read();
	MATH::Ppow(x,k,res,MATH::L-1);
	res.show(n);
}
