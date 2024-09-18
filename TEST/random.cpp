#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0));
	int n=1000000;
	int a[n];
	for(int i=0; i<n; i++) a[i]=i;
	random_shuffle(a, a+n);
	return 0;
} 
