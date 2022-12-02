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
	    // a == rock/1, b = paper/2, c = scissors/3
	    // x == lose, y = draw, z = win
	    a -= 'A';
	    x -= 'X';
	    t += 
		a == 0 ? (x == 1 ? 3 + 1 : x == 2 ? 6 + 2 : 0 + 3) :
		a == 1 ? (x == 1 ? 3 + 2 : x == 2 ? 6 + 3 : 0 + 1) :
		a == 2 ? (x == 1 ? 3 + 3 : x == 2 ? 6 + 1 : 0 + 2) :
		0;
	}
	cout << t << endl;
	return 0;
}
