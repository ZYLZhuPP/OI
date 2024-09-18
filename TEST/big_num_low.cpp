#include<bits/stdc++.h>
using namespace std;

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

template<class C> inline void clear(C &a) {C().swap(a);}

struct Big {
    const int Base = 10000, Bit = 4;
    vector<int > a;

    Big() {
        a.push_back(0);
    }

    Big(const int &x) {
        clear(a);
        int o = x;
        while (o > Base) {
            a.push_back(o % Base);
            o /= Base;
        }
        a.push_back(o);
    }

    Big(const char *s) {
        clear(a);
        int len = strlen(s);
        for (int i = len - 1; i >= 0; i -= Bit) {
            int x = 0, l = max(0, i - Bit + 1);
            for (int j = i; j >= l; j--) x = (x << 3) + (x << 1) + (s[j] ^ 48);
            a.push_back(x);
        }
    }

    Big(const string &st) {
        Big(st.c_str());
    }

    Big(const Big &x) {
        a = x.a;
    }

    template<class C>
    Big& operator = (const C &X) {
        a = Big(X).a;
        return *this;
    }

    template<class C>
    bool operator < (const C &x) const {
        Big X(x);
        if (a.size() < X.a.size()) return 1;
        if (a.size() == X.a.size()) {
            int i = a.size() - 1;
            while (i && a[i] == X.a[i]) --i;
            return a[i] < X.a[i];
        }
        return 0;
    }

    template<class C>
    bool operator == (const C &x) const {
        Big X(x);
        if (a.size() ^ X.a.size()) return 0;
        int len = a.size();
        for (int i = 0; i < len; ++i) if (a[i] ^ X.a[i]) return 0;
        return 1;
    }

    template<class C>
    bool operator > (const C &x) const {
        Big X(x);
        if (a.size() > X.a.size()) return 1;
        if (a.size() == X.a.size()) {
            int i = a.size() - 1;
            while (i && a[i] == X.a[i]) --i;
            return a[i] > X.a[i];
        }
        return 0;
    }

    template<class C>
    Big operator + (const C &x) const {
        Big X(x), Y(*this);
        int lx = X.a.size(), ly = Y.a.size();
        int len = max(lx, ly); X.a.resize(len, 0);
        bool up = 0;
        for (int i = 0; i < len; ++i) {
            if (up) X.a[i]++;
            X.a[i] += Y.a[i];
            up = X.a[i] >= Base;
            X.a[i] -= Base * up;
        }
        if (up) X.a.push_back(1);
        return X;
    }

    template<class C>
    Big operator - (const C &x) const {
        Big X(x), Y(*this);
        int lx = X.a.size(), ly = Y.a.size();
        int len = lx; Y.a.resize(len, 0);
        bool dw = 0;
        for (int i = 0; i < len; ++i) {
            if (dw) X.a[i]--;
            X.a[i] -= Y.a[i];
            dw = X.a[i] < 0;
            X.a[i] += Base * dw;
        }
        while (len - 1 && !X.a[len - 1]) X.a.pop_back();
        return X;
    }

    Big operator * (const int &x) const {
        Big res(*this);
        int len = a.size();
        int up = 0;
        for (int i = 0; i < len; ++i) {
            res.a[i] = a[i] * x + up;
            up = res.a[i] / Base;
            res.a[i] %= Base;
        }
        while (up) {
            res.a.push_back(up % Base);
            up /= Base;
        }
        return res;
    }

    Big operator / (const int &x) const {
        Big res(*this);
        int len = a.size();
        int dw = 0;
        for (int i = len - 1; i >= 0; --i) {
            res.a[i] = (a[i] + dw * Base) / x;
            dw = (a[i] + dw * Base) % x;
        }
        while (len - 1 && !res.a[len - 1]) res.a.pop_back();
        return res;
    }

    int operator % (const int &x) const {
        int res = 0, len = a.size();
        for (int i = len - 1; i >= 0; --i) res = (a[i] + res * Base) % x;
        return res;
    }

    Big operator << (const int &x) const {
        Big res(*this);
        int o = x;
        while (o > 30) res = res * (1 << 30), o -= 30;
        res = res * (1 << o);
        return res;
    }

    Big operator >> (const int &x) const {
        Big res(*this);
        int o = x;
        while (o > 30) res = res / (1 << 30), o -= 30;
        res = res / (1 << o);
        return res;
    }
};

int main() {

    return 0;
}
