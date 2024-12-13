#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d, x;
    cin >> a >> b >> c >> d >> x;
    cout << (x >= a) * b + (x >= c) * d;

    return 0;
}
