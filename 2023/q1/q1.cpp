#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    string s;
    int32_t res = 0;
    while(cin >> s) {
	int first = -1, last = -1;
	for (auto c: s)
	    if (isdigit(c)) {
		c -= '0';
		if (first == -1)
		    first = c;
		last = c;
	    }
	assert(first >= 0 && last >= 0);
	res += first*10 + last;
    }
    cout << res << endl;
}
