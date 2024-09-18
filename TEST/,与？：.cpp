#include<bits/stdc++.h>
using namespace std;

int main(){
	int a = 0, b = 0;
	(0, 1)? a = 1: b = 1;
	cout << a << " " << b <<'\n';
	1? a = 0: a = 2, b = 3;
	cout << a << " " << b <<'\n';
	1? a = 0: (a = 2, b = 0);
	cout << a << " " << b <<'\n';
	1? a = 3, b = 0: (a = 2, b = 0);
	cout << a << " " << b <<'\n';
	// 说明","分隔号返回值为最右边的表达式
	// 说明"?"后是至":"的所有表达式 
	// 说明":"后只能是无分隔的第一个表达式 
    return 0;
}
