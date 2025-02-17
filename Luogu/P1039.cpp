#include<bits/stdc++.h>
using namespace std;

const int N = 25;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

unordered_map<string, int> day, na;
int m, n, p, ans, me[N], to[N][N], da[N];
bool no[10];
string name, Name[N], a;

void init() {
    ans = 0;
    memset(me, -1, sizeof(me));
    memset(to, -1, sizeof(to));
    memset(da, 0, sizeof(da));
    day["Monday"] = 1;
    day["Tuesday"] = 2;
    day["Wednesday"] = 3;
    day["Thursday"] = 4;
    day["Friday"] = 5;
    day["Saturday"] = 6;
    day["Sunday"] = 7;
}

void make(string name, string sth) {
    int id = na[name];
    if (!id) return;
    int len = sth.length();

    int pos = sth.find("I am guilty.");
    if (pos == 0 && len == 12) {
        me[id] = 1;
        return;
    }

    pos = sth.find("I am not guilty.");
    if (pos == 0 && len == 16) {
        me[id] = 0;
        return;
    }

    pos = sth.find(" is guilty.");
    if (~pos && len == pos + 11) {
        string st = sth; st.erase(pos, 11);
        int i = na[st];
        if (i) to[id][i] = 1;
        return;
    }

    pos = sth.find(" is not guilty.");
    if (~pos && len == pos + 15) {
        string st = sth; st.erase(pos, 15);
        int i = na[st];
        if (i) to[id][i] = 0;
        return;
    }

    pos = sth.find("Today is ");
    if (pos == 0) {
        string st = sth; st.erase(0, 9); st.erase(st.length() - 1, 1);
        int d = day[st];
        if (d) {
            if (da[id] && d != da[id]) no[d] = no[da[id]] = 1;
            da[id] = d;
        }
        return;
    }
}

void Try(int g, int day) {
    int T = 0, F = 0;
    for (int i = 1; i <= m; ++i) {
        int flag = -1;
        if (~me[i]) {
            if (me[i] == (i == g)) flag = 1;
            else flag = 0;
        }
        for (int j = 1; j <= m; ++j) if (~to[i][j]) {
            if (to[i][j] == (j == g)) {
                if (flag == 0) return;
                flag = 1;
            } else {
                if (flag == 1) return;
                flag = 0;
            }
        }
        if (da[i]) {
            if (da[i] == day) {
                if (flag == 0) return;
                flag = 1;
            } else {
                if (flag == 1) return;
                flag = 0;
            }
        }

        if (flag == 1) T++;
        if (flag == 0) F++;
    }

    if (F > n || T > m - n) return;
    if (ans && ans != g) {
        puts("Cannot Determine");
        exit(0);
    }
    ans = g;
}

int main() {
    init();
    io >> m >> n >> p;
    for (int i = 1; i <= m; ++i) {
        cin >> Name[i];
        na[Name[i]] = i;
    }
    for (int i = 1; i <= p; ++i) {
        cin >> name;
        name.erase(name.length() - 1, 1);
        getline(cin, a);
        a.erase(0, 1);
        int len = a.length();
        if (a[len - 1] == '\n' || a[len - 1] == '\r') a.erase(len - 1, 1);
        make(name, a);
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= 7; ++j) if (!no[j]) Try(i, j);
    }

    if (!ans) puts("Impossible");
    else cout << Name[ans];

    return 0;
}
