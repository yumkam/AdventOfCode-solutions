#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	unsigned maxscore[3][3][3] = {{{0}}};
	unsigned t = 0;
	for(;;) {
	    char a, x;
	    if (!(cin >> a >> x)) break;
	    //cout << a << x << endl;
	    a -= 'A';
	    x -= 'X';

	    for (unsigned i = 0; i < 3; ++i) // rock
		for (unsigned j = 0; j < 3; j++) { // paper
		    if (i == j)
			continue;
		    for (unsigned k = 0; k < 3; k++) { // scissors
			if (i == k || j == k)
			    continue;
			//cout << i << j << k << endl;
			assert((x == i) + (x == j) + (x == k) == 1);
			maxscore[i][j][k] += a == 0 ? (x == i ? 3 + 1 : x == j ? 6 + 2 : 0 + 3) :
			    a == 1 ? (x == j ? 3 + 2 : x == i ? 0 + 1 : 6 + 3) :
			    a == 2 ? (x == k ? 3 + 3 : x == i ? 6 + 1 : 0 + 2) : 0;
		    }
		}
#if 1
	    t += (x + 1) +
		(a == 0 ? (x == 0 ? 3 : x == 2 ? 0 : 6) :
		 a == 1 ? (x == 1 ? 3 : x == 2 ? 6 : 0) :
		 a == 2 ? (x == 2 ? 3 : x == 1 ? 0 : 6) : 0);
#endif
	}
	cout << t << endl;
	#if 0
	unsigned ms = 0;
	for (unsigned i = 0; i < 3; i++)
	    for (unsigned j = 0; j < 3; j++)
		for (unsigned k = 0; k < 3; k++) {
		    if (maxscore[i][j][k])
			cout << i << j << k << ' ' << maxscore[i][j][k] << endl;
		    ms = max(ms, maxscore[i][j][k]);
		}
	cout << ms << endl;
	#else
	cout << maxscore[0][1][2] << endl;
	#endif
	return 0;
}
