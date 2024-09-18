#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=505;
int a[N][N],l[N],r[N],used[N];
bool vis[N][N];
int n,m;
queue<pair<int,int> > q;
void bfs(int x){
	q.push(make_pair(1,x));
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		auto tmp=q.front();
		q.pop();
		if(vis[tmp.first][tmp.second]) continue;
		vis[tmp.first][tmp.second]=1;
		if(tmp.first==n) l[x]=min(l[x],tmp.second),r[x]=max(r[x],tmp.second),used[tmp.second]=1;
		if(tmp.second>1&&a[tmp.first][tmp.second]>a[tmp.first][tmp.second-1]) q.push(make_pair(tmp.first,tmp.second-1));
		if(tmp.second<m&&a[tmp.first][tmp.second]>a[tmp.first][tmp.second+1]) q.push(make_pair(tmp.first,tmp.second+1));
		if(tmp.first>1&&a[tmp.first][tmp.second]>a[tmp.first-1][tmp.second]) q.push(make_pair(tmp.first-1,tmp.second));
		if(tmp.first<n&&a[tmp.first][tmp.second]>a[tmp.first+1][tmp.second]) q.push(make_pair(tmp.first+1,tmp.second));
	}
	return ;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
		}
	}
	memset(l,0x3f,sizeof(l));
	memset(r,0x80,sizeof(r));
	for(int i=1;i<=m;++i) bfs(i);
	int cnt=0;
	for(int i=1;i<=m;++i){
		if(!used[i]) ++cnt;
	}if(cnt){
		cout<<0<<endl<<cnt<<endl;
		return 0;
	}
	int cover=0;
	cnt=0;
	while(cover<m){
		int id=0;
		for(int i=1;i<=m;++i){
			if(l[i]<=cover+1&&r[i]>r[id]) id=i;
		}
		cover=r[id];
		++cnt;
	}
	cout<<1<<endl<<cnt<<endl;
	return 0;
}