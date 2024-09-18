#include<bits/stdc++.h>
using namespace std;
int main(){
	set<int > tr;
	tr.insert(0);
	tr.insert(1);
	tr.insert(3);
	cout<<(*lower_bound(tr.begin(), tr.end(), 2));
	return 0;
} 
