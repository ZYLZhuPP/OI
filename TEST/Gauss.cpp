#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

void Gauss(vector<vector<double > > &a, int n, int m) {
    int r; double temp;
    for (int i = 0; i < n; i++) {
        r = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        swap(a[i], a[r]);
        if (fabs(a[i][i]) < eps) continue;
        temp = a[i][i];
        for (int j = i; j < n + m; j++) a[i][j] /= temp;
        for (int j = 0; j < n; j++) if (j ^ i){
            temp = a[j][i];
            for (int k = i; k < n + m; k++) 
                a[j][k] -= a[i][k] * temp;
        }
    }
}

int main() {
    vector<vector<double > > a = {
        {1, 2, 5},
        {2, 4, 10}
    };
    Gauss(a, 2, 1);
    int flag = 1;
    for (int i = 0; i < 2; i++) {
        if (fabs(a[i][i]) < eps) {
            if (fabs(a[i][2]) > eps) {
                flag = -1;
                cout << "No Solution!";
                break;
            }else flag = 0;
        }
    }
    if (!flag) cout << "Unlimited!";
    if (flag == 1) 
        for (int i = 0; i < 2; i++) cout << a[i][2] << endl;
    return 0;
}//O(n^2*(n+m))求解m个n元线性方程
