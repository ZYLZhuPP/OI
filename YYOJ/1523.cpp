#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

int S, T, ans;
string s, t;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> s >> t;
    S = s.length(); T = t.length();

    if (T == 1) {
        if (count(all(s), t[0]) == 0) cout << "0";
        else cout << "-1";
    } else if (T == 2) {
        if (t[0] ^ t[1]) {
            for (int i = 0; i < S - 1; ++i) ans += s.substr(i, 2) == t;
            cout << ans;
        } else {
            int cnt = count(all(s), t[0]);
            if (2*cnt - 1 > S) cout << "-1";
            else {
                for (int i = 0; i < S - 1; ++i) ans += s.substr(i, 2) == t;
                cout << ans;
            }
        }
    } else {
        if (t[0] == '1') {
            for (auto &c : s) c ^= 1;
            for (auto &c : t) c ^= 1;
        }
        if (t[2] == '1') {
            for (int i = 0; i < S - 2; ++i) ans += (s.substr(i, 3) == t);
            cout << ans;
        } else if (t[1] == '1') {
            for (int i = 0; i < S - 2; ++i) ans += s.substr(i, 3) == t;
            cout << (ans + 1) / 2;
        } else {
            int cnt = count(all(s), t[0]);
            if (3 * cnt > (S + 1) * 2) cout << "-1";
            else {
                int two = (s[0] == '1') + (s.back() == '1'), need = 0;
                for (int i = 0; i < S - 1; ++i) two += s.substr(i, 2) == "11";
                for (int i = 0; i < S; ++i) {
                    if (s[i] == '1') continue;
                    int j = i;
                    while (s[j] == '0' && j < S) ++j;
                    int d = j - i;
                    if (d > 2) {
                        if (d & 1) ans++, d--;
                        need += d / 2 - 1;
                    }
                    i = j;
                }

                if (need <= two) ans += need;
                else ans += 2 * need - two;

                cout << ans;
            }
        }
    }

    return 0;
}
