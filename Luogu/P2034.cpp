#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
const int N = 1e5 + 3;
int n , k;
ll a[N] , s[N] , f[N] , ds[N];
deque<ll> q;
ll query(int x){
	ds[x] = f[x - 1] - s[x];
	while(q.size() && ds[q.front()] < ds[x])	q.pop_front();
	while(q.size() && q.back() < x - k)	q.pop_back();
	q.push_front(x);
	return ds[q.back()];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++){
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	q.clear(); q.push_back(0);
	for(int i = 1 ; i <= n ; i++)	f[i] = query(i) + s[i];
	cout << f[n];
	return 0;
}
