#include <bits/stdc++.h>
#define fo(a,b,c) for (a=b; a<=c; a++)
#define fd(a,b,c) for (a=b; a>=c; a--)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define inf 2147483647
#define ll long long
#define file
using namespace std;

struct type{int X1,Y1,X2,Y2;} b[250001];
const int fx[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int d[90001][2],c[301][301],C[301],N,n,m,i,j,k,l,T,X1,Y1,X2,Y2,tot,h,t,s;
ll sum[4][301][301],Sum[4][301][301],f[800001],ans;
bool a[301][301],bz[301][301];
char ch;

bool cmp(type a,type b) {return a.X1>b.X1;}
void init()
{
	scanf("%d%d",&n,&m),N=(n+1)*(m+1)*2;
	fo(i,1,n)
	{
		fo(j,1,m)
		{
			ch=getchar();
			while (ch!='0' && ch!='1') ch=getchar();
			a[i][j]=ch=='1';
		}
	}
	fo(i,1,n)
	{
		fo(j,1,m)
		if (a[i][j])
		{
			sum[0][i][j]=1;
			sum[1][i][j]=j<m && a[i][j+1];
			sum[2][i][j]=i<n && a[i+1][j];
			sum[3][i][j]=i<n && j<m && a[i+1][j] && a[i][j+1] && a[i+1][j+1];
		}
	}
	fo(i,1,n) fo(j,1,m) fo(k,0,3) sum[k][i][j]+=sum[k][i][j-1];
}

void bfs(int x,int y)
{
	int i,j,k,l,mx=x,my=y,Mx=x,My=y;
	h=0,t=1;
	d[1][0]=x,d[1][1]=y,bz[x][y]=1;
	while (h<t)
	{
		++h;
		fo(i,0,3)
		{
			x=d[h][0]+fx[i][0];
			y=d[h][1]+fx[i][1];
			if (x>=1 && x<=n && y>=1 && y<=m && !bz[x][y] && !a[x][y])
			{
				++t;
				d[t][0]=x,d[t][1]=y;
				bz[x][y]=1;
				mx=min(mx,x),my=min(my,y);
				Mx=max(Mx,x),My=max(My,y);
			}
		}
	}
	
	--mx,--my,++Mx,++My;
	if (mx>=1 && Mx<=n && my>=1 && My<=m) b[++tot]={mx,my,Mx,My};
}
void init2()
{
	fo(i,1,n)
	{
		fo(j,1,m)
		if (!a[i][j] && !bz[i][j])
		bfs(i,j);
	}
	if (tot) sort(b+1,b+tot+1,cmp);
}

void work()
{
	l=1;
	fd(X1,n,1)
	{
		while (l<=tot && X1<=b[l].X1) c[b[l].X2][b[l].Y2]=max(c[b[l].X2][b[l].Y2],b[l].Y1),++l;
		
		fo(j,1,m) fo(k,0,3) Sum[k][X1-1][j]=0;
		memset(C,0,sizeof(C)),T=0;
		fo(X2,X1,n)
		{
			fo(j,1,m) fo(k,0,3) Sum[k][X2][j]=Sum[k][X2-1][j]+sum[k][X2][j];
			T=k=0;
			fo(j,1,m)
			{
				C[j]=max(C[j],c[X2][j]),T=max(T,C[j]);
				while (k<T) ++k,s=Sum[0][X2][k-1]-(Sum[1][X2][k-1]+Sum[2][X2-1][k-1])+Sum[3][X2-1][k-1],--f[s+N];
				
				s=Sum[0][X2][j-1]-(Sum[1][X2][j-1]+Sum[2][X2-1][j-1])+Sum[3][X2-1][j-1];
				++f[s+N];
				s=Sum[0][X2][j]-(Sum[1][X2][j-1]+Sum[2][X2-1][j])+Sum[3][X2-1][j-1];
				ans+=f[s-1+N];
			}
			while (k<m) ++k,s=Sum[0][X2][k-1]-(Sum[1][X2][k-1]+Sum[2][X2-1][k-1])+Sum[3][X2-1][k-1],--f[s+N];
		}
	}
}

int main()
{
	freopen("village.in","r",stdin);
	#ifdef file
	freopen("village.out","w",stdout);
	#endif
	
	init();
	init2();
	work();
	printf("%lld\n",ans);
}