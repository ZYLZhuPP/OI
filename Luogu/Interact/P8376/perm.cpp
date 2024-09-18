#include "perm.h"
#include<bits/stdc++.h>
using namespace std;

vector<int > ans;
int n;

void work(long long x) {
    if (x <= 4) {
        while (--x) ans.insert(ans.begin(), n++);
        return;
    }
    if (x % 2 == 0) work(x >> 1), ans.push_back(n++);
    else if (x % 4 == 1) work(x - 1), ans.insert(ans.begin(), n++);
    else if (x % 4 == 3) work(x - 3), ans.insert(ans.begin() + 2, n++);
}

vector<int > construct_permutation(long long k) {
    ans.resize(n = 0);
    work(k);
	return ans;
}
