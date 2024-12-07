#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

struct Node {
    int x, id;
    bool operator < (const Node &a) const { return a.x < x; }
};

int n, flag, cnt;
ll ans;
char s[N];
priority_queue<Node > q;

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    For (i, 1, n) {
        if (s[i] == '(') cnt++;
        else if (s[i] == ')') cnt--;
        else if (s[i] == '?') {
            s[i] = ')'; cnt--;
            int x, y;
            io >> x >> y;
            ans += y;
            q.push({x - y, i});
        }
        if (cnt < 0) {
            if (q.empty()) { flag = 1; break; }
            else ans += q.top().x, s[q.top().id] = '(', q.pop(), cnt += 2;
        }
    }
    if (cnt) flag = 1;
    if (flag) puts("-1");
    else {
        printf("%lld\n", ans);
        printf("%s", s + 1);
    }

    return 0;
}