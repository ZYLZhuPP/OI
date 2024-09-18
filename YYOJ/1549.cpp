#include<bits/stdc++.h>
using namespace std;

int ans;
string a, b;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> a;
	for (auto &c : a) {
		if (!b.empty() && b.back() == c) ans += 10, b.pop_back();
		else b += c;
	}
	
	cout << ans + b.size() / 2 * 5;
	
	return 0;
} 
