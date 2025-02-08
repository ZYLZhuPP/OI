#include<bits/stdc++.h>
using namespace std;

#define pi M_PI

typedef complex<double > com;

inline void reverse(com a[], int n) {
    vector<int > rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
}

inline void FFT(com a[], int n, int inv) {
    reverse(a, n);
    for (int m = 1; m < n; m <<= 1) {
        com o(cos(pi / m), inv * sin(pi / m));
        for (int i = 0; i < n; i += m << 1) {
            com p(1, 0);
            for (int j = i; j < i + m; j++, p *= o) {
                com x = a[j], y = p * a[j + m];
                a[j] = x + y; a[j + m] = x - y;
            }
        }
    }
}

int main() {
    int n = 8;
	int a[n] = {2, 0, 0, 0, 0, 0, 0, 0}, b[n] = {2, 3, 4, 5, 6, 0, 0, 0};
    com A[n];
    for (int i = 0; i < n; i++) A[i] = com(a[i], b[i]);
	int c[n];
	FFT(A, n, 1);
	for (int i = 0; i < n; i++) A[i] *= A[i];
	FFT(A, n, -1);//-1点值转系数
	for (int i = 0; i < n; i++) c[i]=(int)(A[i].imag()/2/n+0.5), cout << c[i] << " ";//注意精度

    return 0;
}
