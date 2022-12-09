#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	set<pair<int,int>> s;
	auto hx = 0;
	auto hy = 0;
	auto tx = 0;
	auto ty = 0;
	char c;
	int steps;
	s.emplace(tx, ty);
	while(cin >> c >> steps) {
	    int dx = c == 'L' ? -1 : c == 'R' ? +1 : 0;
	    int dy = c == 'U' ? +1 : c == 'D' ? -1 : 0;
	    while(steps--) {
		hx += dx;
		hy += dy;
		if (hx - tx > 1) {
		    assert(hx - tx == 2);
		    tx = hx - 1;
		    assert(abs(hy - ty) < 2);
		    ty = hy;
		} else if (tx - hx > 1) {
		    assert(tx - hx == 2);
		    tx = hx + 1;
		    assert(abs(hy - ty) < 2);
		    ty = hy;
		} else if (hy - ty > 1) {
		    assert(hy - ty == 2);
		    ty = hy - 1;
		    assert(abs(hx - tx) < 2);
		    tx = hx;
		} else if (ty - hy > 1) {
		    assert(ty - hy == 2);
		    ty = hy + 1;
		    assert(abs(hx - tx) < 2);
		    tx = hx;
		}
		s.emplace(tx, ty);
	    }
	}
	cout << s.size() << endl;
	return 0;
}
