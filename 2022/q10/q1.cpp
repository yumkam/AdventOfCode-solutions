#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	unsigned cyc = 1;
	int x = 1;
	string s;
	int ret = 0;
	unsigned prev = 20;
	while(cin >> s) {
	    int ox = x;
	    if (s[0] == 'a') {
		int arg;
		cin >> arg;
		x += arg;
		cyc += 2;
	    } else {
		cyc += 1;
	    }
	    if (cyc >= prev) {
		clog << cyc << ' ' << prev << ' ' << ox << ' ' << x <<endl;
		ret += (cyc > prev ? ox : x)*prev;
		prev += 40;
	    }
	}
	cout << ret << endl;
	return 0;
}
