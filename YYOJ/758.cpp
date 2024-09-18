#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef pair<int,int> PII;

const int N=20, M=400;

struct node{
	int to,next,w;
}e[M];
int head[M],tot;
void add(int u,int v,int w){e[tot].to=v;e[tot].w=w;e[tot].next=head[u];head[u]=tot++;}

int g[N][N];
set<PII> edges;
int key[M];

int n,m,p,s;

int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

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

void build(){
	int k;
    read(k);
    while(k--){
    	int x1,y1,x2,y2; read(x1);read(y1);read(x2);read(y2); 
    	int c; read(c);
    	int u=g[x1][y1], v=g[x2][y2];
    	if(c) add(u,v,c), add(v,u,c);
    	edges.insert({u,v}); edges.insert({v,u});
    }
    
    read(s);
    while(s--){
    	int x,y,w; read(x);read(y);read(w);
    	key[g[x][y]]|=1<<(w-1);
    }
    
    for(int x=1;x<=n;x++)
    	for(int y=1;y<=m;y++)
    		for(int op=0;op<4;op++){
    			int kx=x+dx[op], ky=y+dy[op];
    			if(!kx || kx>n || !ky || ky>m) continue;
    			int p1=g[x][y], p2=g[kx][ky];
    			if(!edges.count({p1,p2})) add(p1,p2,0), add(p2,p1,0);
    		}
}

int d[M][1<<12];
bool vis[M][1<<12];
int bfs(){
	memset(d,0x3f,sizeof d);
    deque<PII> q;
    q.push_front({1,0});
    d[1][0]=0;
    
    while(q.size()){
    	auto hd=q.front(); q.pop_front();
    	int ver=hd.x;
    	
    	if(vis[ver][hd.y]) continue;
    	vis[ver][hd.y]=true;
    	
    	if(ver==n*m) return d[ver][hd.y];
    	
    	int st=hd.y;
    	if(key[ver]){
    		st|=key[ver];
    		if(d[ver][st]>d[ver][hd.y]){
    			d[ver][st]=d[ver][hd.y];
    			q.push_front({ver,st});
    		}
    	}
    	
    	for(int i=head[ver];~i;i=e[i].next){
    		int go=e[i].to;
    		if(e[i].w && !(st>>(e[i].w-1)&1))
    			continue;
    		
    		if(d[go][st]>d[ver][hd.y]+1){
    			d[go][st]=d[ver][st]+1;
    			q.push_back({go,st});
    		}
    	}
    }
    
    return -1;
}

int main(){
	memset(head,-1,sizeof head);
    read(n);read(m);read(p);
    
    for(int i=1,t=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            g[i][j]=t++;
    
    build();
    
    cout<<bfs()<<endl;
    
    return 0;
}
