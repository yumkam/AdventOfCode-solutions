#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	int cyc = 1;
	int x = 1;
	string s;
	string c(40, '.');
	unsigned prev = 40;
	while(cin >> s) {
	    int ox = x;
	    if (s[0] == 'a') {
		int arg;
		cin >> arg;
		if (x - 1 <= cyc-1 && cyc-1 <= x + 1) { c[cyc - 1] = '#'; } if (cyc == 41) { cout << c << endl; fill(c.begin(), c.end(), '.'); cyc = 1; if (x - 1 <= cyc-1 && cyc-1 <= x + 1) { c[cyc - 1] = '#'; }}
		cyc += 1;
		if (x - 1 <= cyc-1 && cyc-1 <= x + 1) { c[cyc - 1] = '#'; } if (cyc == 41) { cout << c << endl; fill(c.begin(), c.end(), '.'); cyc = 1; if (x - 1 <= cyc-1 && cyc-1 <= x + 1) { c[cyc - 1] = '#'; }}
		x += arg;
		cyc += 1;
	    } else {
		if (x - 1 <= cyc-1 && cyc-1 <= x + 1) { c[cyc - 1] = '#'; } if (cyc == 41) { cout << c << endl; fill(c.begin(), c.end(), '.'); cyc = 1; if (x - 1 <= cyc-1 && cyc-1 <= x + 1) { c[cyc - 1] = '#'; }}
		cyc += 1;
	    }
	}
	cout << c << endl;
	return 0;
}
