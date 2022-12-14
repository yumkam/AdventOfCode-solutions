#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    //if (ac > 1 && av[1][0])
    //	maxs = atoi(av[1]);
    int x, y;
    char c;
    int ox = -1, oy = -1;
    set<pair<int,int>> grid;
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
#if DEBUG
    auto ogrid = grid;
#endif
    for (;;) {
	pair<int,int> pos {500, 0};
#if DEBUG
	{
	    pair<int,int> p;
	    for (p.second = 0; p.second <= bottom; p.second++, clog << endl)
		for (p.first = left; p.first <= right; p.first++)
		    clog << (grid.count(p) ? (ogrid.count(p) ? '#' : 'o') : '.');
	}
#endif
	assert(0 == grid.count(pos));
	for (;;) {
	    pos.second++;
	    if (pos.second > bottom + 1)
		goto leave;
	    {
		auto z = grid.count(pos);
#if DEBUG
		clog << pos.first << 'x' << pos.second;
		clog << 'z' << z << endl;
#endif
		if (!z)
		    continue;
	    }
	    pos.first--;
	    {
		auto m1 = grid.count(pos);
#if DEBUG
		clog << '-' << m1 << endl;
#endif
		if (!m1)
		    continue;
	    }
	    pos.first += 2;
	    {
		auto p1 = grid.count(pos);
#if DEBUG
		clog << '+' << p1 << endl;
#endif
		if (!p1)
		    continue;
	    }
	    pos.first--;
	    pos.second--;
#if DEBUG
	    clog << '!' << endl;
#endif
	    grid.insert(pos);
	    break;
	}
	ret++;
    }
    {
	pair<int,int> p;
	for (p.second = 0; p.second <= bottom; p.second++, clog << endl)
	    for (p.first = left; p.first <= right; p.first++)
		clog << (grid.count(p) ? '#' : '.');
    }
leave:
    cout << ret << endl;
    return 0;
}
