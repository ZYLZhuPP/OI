#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef vector<lf > vec;
typedef vector<vec > vvec;

struct mat : vvec {
    static constexpr lf eps = 1e-9;
    using vvec::vvec;
    mat() { }
    mat(const int &n, const int &m, const lf &x = 0) { resize(n, vec(m, x)); }
    inline int N() const { return this->size(); }
    inline int M() const { return (*this)[0].size(); }
    inline mat operator ~ () const {
        int n = N(), m = M();
        mat r(m, n); For (i, 0, n - 1) For (j, 0, m - 1) r[j][i] = (*this)[i][j];
        return r;
    }
    inline mat operator - () const {
        int n = N(), m = M();
        mat r(*this); For (i, 0, n - 1) For (j, 0, m - 1) r[i][j] = -r[i][j];
        return r;
    }
    inline mat operator + (const mat &a) const {
        int n = N(), m = M();
        mat r(*this); For (i, 0, n - 1) For (j, 0, m - 1) r[i][j] += a[i][j];
        return r;
    }
    inline mat& operator += (const mat &a) {
        int n = N(), m = M();
        For (i, 0, n - 1) For (j, 0, m - 1) (*this)[i][j] += a[i][j];
        return *this;
    }
    inline mat operator - (const mat &a) const {
        int n = N(), m = M();
        mat r(*this); For (i, 0, n - 1) For (j, 0, m - 1) r[i][j] -= a[i][j];
        return r;
    }
    inline mat& operator -= (const mat &a) {
        int n = N(), m = M();
        For (i, 0, n - 1) For (j, 0, m - 1) (*this)[i][j] -= a[i][j];
        return *this;
    }
    inline mat operator * (const lf &x) const {
        int n = N(), m = M();
        mat r(*this); For (i, 0, n - 1) For (j, 0, m - 1) r[i][j] *= x;
        return r;
    }
    inline mat& operator *= (const lf &x) {
        int n = N(), m = M();
        For (i, 0, n - 1) For (j, 0, m - 1) (*this)[i][j] *= x;
        return *this;
    }
    inline mat operator * (const mat &a) const {
        int n = N(), o = M(), m = a.M();
        mat r(n, m); For (k, 0, o - 1) For (i, 0, n - 1) For (j, 0, m - 1) r[i][j] += (*this)[i][k] * a[k][j];
        return r;
    }
    inline mat& operator *= (const mat &a) {
        int n = N(), o = M(), m = a.M();
        mat r(n, m); For (k, 0, o - 1) For (i, 0, n - 1) For (j, 0, m - 1) r[i][j] += (*this)[i][k] * a[k][j];
        swap(r);
        return *this;
    }
    inline mat operator & (const mat &a) const {
        int n = N();
        mat r(*this); For (i, 0, n - 1) for (auto &x : a[i]) r[i].pb(x);
        return r;
    }
    inline mat& operator &= (const mat &a) {
        int n = N();
        For (i, 0, n - 1) for (auto &x : a[i]) (*this)[i].pb(x);
        return *this;
    }
    inline mat& gauss() {
        vvec &a = *this;
        int n = N(), m = M();
        For (i, 0, n - 1) {
            int r = i; For (j, i + 1, n - 1) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
            if (fabs(a[r][i]) < eps) continue;
            a[i].swap(a[r]);
            lf x = a[i][i]; For (j, i, m - 1) a[i][j] /= x;
            For (j, 0, n - 1) if (i ^ j) {
                x = a[j][i];
                For (k, i, m - 1) a[j][k] -= x * a[i][k];
            }
        }
        return *this;
    }
};

int main() {

    return 0;
}
