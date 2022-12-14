#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    //if (ac > 1 && av[1][0])
    //	maxs = atoi(av[1]);
    int x, y;
    char c;
    int ox = -1, oy = -1;
#if 0
    set<pair<int,int>> grid;
#else
    auto hashop = [](auto x) {
	return (static_cast<size_t>(x.first) << (sizeof(size_t)*8/2)) ^ x.second;
    };
    unordered_set<pair<int,int>, decltype(hashop)> grid(1u, hashop);
#endif
    int bottom = 0;
    int left = INT_MAX;
    int right = INT_MIN;
    while(cin >> x >> c >> y) {
	if (ox == -1)
	    ox = x, oy = y;
	bottom = max(bottom, y);
	left = min(left, x);
	right = max(right, x);
	for(; ox < x; ox++)
	    grid.emplace(ox, oy);
	for(; ox > x; ox--)
	    grid.emplace(ox, oy);
	for(; oy < y; oy++)
	    grid.emplace(ox, oy);
	for(; oy > y; oy--)
	    grid.emplace(ox, oy);
	grid.emplace(ox, oy);
	int peek = cin.get(); // either '\n' or ' '
	if (peek == '\n')
	    ox = oy = -1;
	else
	    (int)cin.get(), (int)cin.get(); // skip '-' '>'
    }
    unsigned ret = 0;
#define DEBUG 1
#if DEBUG
    auto ogrid = grid;
#endif
    for (;;) {
	pair<int,int> pos {500, 0};
#if DEBUG
	if (DEBUG > 1 || grid.count(pos)) {
	    pair<int,int> p;
	    for (p.second = 0; p.second <= bottom + 2; p.second++, clog << endl)
		for (p.first = left; p.first <= right; p.first++)
		    clog << (grid.count(p) ? (ogrid.count(p) ? '#' : 'o') : '.');
	}
#endif
	if(grid.count(pos))
	    break;
	for (;;) {
	    pos.second++;
	    if (pos.second == bottom + 2)
		goto placeit;
	    {
		auto z = grid.count(pos);
#if DEBUG > 1
		clog << pos.first << 'x' << pos.second;
		clog << 'z' << z << endl;
#endif
		if (!z)
		    continue;
	    }
	    pos.first--;
	    {
		auto m1 = grid.count(pos);
#if DEBUG > 1
		clog << '-' << m1 << endl;
#endif
		if (!m1)
		    continue;
	    }
	    pos.first += 2;
	    {
		auto p1 = grid.count(pos);
#if DEBUG > 1
		clog << '+' << p1 << endl;
#endif
		if (!p1)
		    continue;
	    }
	    pos.first--;
placeit:
	    pos.second--;
	    left = min(left, pos.first);
	    right = max(right, pos.first);
#if DEBUG > 1
	    clog << '!' << endl;
#endif
	    grid.insert(pos);
	    break;
	}
	ret++;
    }
    cout << ret << endl;
    return 0;
}
