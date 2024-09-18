#include<bits/stdc++.h>
using namespace std;

const int N = 305;

int T;
char rev[N];
string a, b;

#define gc() getchar()

template<class C>
inline bool read(C &x) {
	x=0;
	int f=1;
	char c=gc();
	for(; !isdigit(c); c=gc()) 
		if(!(c^EOF)) return 0;
		else if(!(c^45)) f=-1;
	for(; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48);
	x*=f;
	return 1;
}

int main() {
	read(T);
	cin.tie(0);
	
	while (T--) {
		memset(rev, 0, sizeof(rev));
		
		getline(cin, a); getline(cin, b);
		int len = a.length();
		if (len ^ b.length()) {
			puts("0");
			continue;
		}
		
		bool flag = 1;
		for (int i = 0; i < len; i++) {
			char c1 = a[i], c2 = b[i];
			if (!isalpha(c1)) {
				if (c1 ^ c2) {
					flag = 0;
					break;
				}
			} else {
				if (!rev[c1]) rev[c1] = c2;
				else {
					if (rev[c1] ^ c2) {
						flag = 0;
						break;
					}
				}
			}
		}
		
		puts(flag? "1": "0");
	}
	
	
	return 0;
}

