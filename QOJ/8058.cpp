#include <bits/stdc++.h>
using namespace std;

const int N=200;
int T,lns,lnt;
vector<pair<int,int> > ans;
char s[N],t[N];

int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%s%s",s+1,t+1);
		lns=strlen(s+1),lnt=strlen(t+1);
		if(lns<2) {
			if(lnt<2) printf("0\n");
			else printf("-1\n");
			continue ;
		}
		else if(lnt<2) {
			printf("-1\n");
			continue ;
		}
		if(s[lns]&1) {
			int p=lns-1;
			while(49-s[p]) p--;
			if(p+1<lns) ans.emplace_back(p+1,lns);
			s[lns=p+1]='1';
			ans.emplace_back(lns-1,lns);
			ans.emplace_back(lns,lns+1);
			s[lns]='0';
		}
		else {
			int p=lns;
			while(49-s[p]) p--;
			ans.emplace_back(p+1,lns);
			lns=p+1;
		}
		while(lns>2) {
			if(49-s[lns-2]) {
				int p=lns-2;
				while(p>0&&49-s[p]) p--;
				ans.emplace_back(p+1,lns-1);
				s[lns=p+2]='0',s[lns-1]='1';
			}
			if(lns>2) {
				ans.emplace_back(lns-2,lns-1);
				ans.emplace_back(lns-1,lns+1);
				s[--lns]='0';
			}
		}
		for(int i=lnt;i>2;i--) {
			ans.emplace_back(1,2);
			ans.emplace_back(1,2);
			if(t[i]&1) {
				ans.emplace_back(1,3);
				ans.emplace_back(2,3);
			}
		}
		if(t[2]&1) ans.emplace_back(1,2);
		printf("%d\n",ans.size());
		for(auto [l,r]:ans) printf("%d %d\n",l,r);
		ans.clear();
	}
	return 0;
} 
