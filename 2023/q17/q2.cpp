#include <bits/stdc++.h>
using namespace std;
enum dir { d_right, d_up, d_left, d_down, d_dirs };
array<string, 4> dirmap {"right", "up", "left", "down" };
ostream &operator << (ostream &os, dir d) {
    return os << dirmap[d];
}
int main() {
    string s;
    vector<string> grid;
#define DEBUG 1
#if DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
    while(cin >> s)
	grid.push_back(s);
    const int m = grid.size();
    const int n = grid[0].size();
    const auto mn = m*n;
    constexpr int minmoves = 4;
    constexpr int maxmoves = 10 - 4 + 1;
    vector<unsigned> mincost(mn*d_dirs*maxmoves, UINT_MAX);
    // ((r*n+c)*d_dirs + d)*maxmoves+steps
    static const array<pair<int, int>, d_dirs> delta {{{0, +1}, {-1, 0}, {0, -1}, {+1, 0}}};
    vector<tuple<unsigned, int, int, dir, unsigned>> q; // cost, r, c, dir, remaining steps
    auto cmp = [](const auto &a, const auto &b) {
	return get<0>(a) > get<0>(b);
    };
    auto movesum = [&](int r, int c, dir d) {
	auto [dr, dc] = delta[d];
	unsigned cost = 0;
	unsigned t = minmoves;
	while(t--) {
	    r += dr;
	    c += dc;
	    cost += grid[r][c] - '0';
	};
	return cost;
    };
    {
	auto cr = mincost[((0*n+minmoves)*d_dirs+d_right)*maxmoves + maxmoves - 1] = movesum(0, 0, d_right);
	auto cd = mincost[(((minmoves)*n+0)*d_dirs+d_down)*maxmoves + maxmoves - 1] = movesum(0, 0, d_down);
	q.emplace_back(cr, 0, minmoves, d_right, maxmoves - 1);
	q.emplace_back(cd, minmoves, 0, d_down, maxmoves - 1);
    }
    make_heap(q.begin(), q.end(), cmp);
    vector<unsigned> pathback(m*n*d_dirs*maxmoves, UINT_MAX);
    while(!q.empty()) {
	auto [cost, r, c, d, steps] = q.front();
	pop_heap(q.begin(), q.end(), cmp);
	q.pop_back();
	auto idx = ((r*n+c)*d_dirs+d)*maxmoves+steps;
	if (mincost[idx] < cost)
	    continue;
	debug(clog << r << ',' << c << ';' << d << '/' << steps << '@' << cost);
	auto [odr, odc] = delta[d];
	for (int newdir = d_right; newdir < d_dirs; ++newdir) {
	    if (newdir == d && steps == 0) // too many steps
		continue;
	    auto [dr, dc] = delta[newdir];
	    if ((dr ? dr == -odr : dc == -odc)) // reverse direction
		continue;
	    auto nr = r + (newdir == d ? dr : minmoves*dr);
	    auto nc = c + (newdir == d ? dc : minmoves*dc);
	    if (nr < 0 || nc < 0 || nr >= m || nc >= n)
		continue;
	    auto nsteps = (newdir == d ? steps : maxmoves) - 1;
	    auto newidx = ((nr*n+nc)*d_dirs+newdir)*maxmoves+nsteps;
	    auto &curcost = mincost[newidx];
	    auto newcost = cost + (newdir == d ? grid[nr][nc] - '0' : movesum(r, c, (dir)newdir));
	    if (newcost >= curcost)
		continue;
	    debug(clog << '>' << nr << ',' << nc << '@' << newcost);
	    curcost = newcost;
	    pathback[((nr*n+nc)*d_dirs+newdir)*maxmoves+nsteps] = idx;
	    q.emplace_back(newcost, nr, nc, (dir)newdir, nsteps);
	    push_heap(q.begin(), q.end(), cmp);
	}
	debug(clog << '\n');
    }
    unsigned cost = UINT_MAX;
    unsigned minidx = UINT_MAX;
    for (int d = d_right; d < d_dirs; ++d) {
	for (unsigned steps = 0; steps < maxmoves; ++steps) {
	    auto idx = (((m-1)*n+n-1)*d_dirs+d)*maxmoves+steps;
	    if (mincost[idx] < cost) {
		cost = mincost[idx];
		minidx = idx;
	    }
	}
    }
    //clog << q.capacity() << endl;
    cout << cost << endl;
#if DEBUG
    array<char, d_dirs> dmap { '>' , '^', '<', 'v' };
    for(unsigned r = m - 1, c = n - 1; minidx != UINT_MAX; ) {
	auto next = pathback[minidx];
	auto steps = minidx % maxmoves;
	minidx /= maxmoves;
	dir d = (dir)(minidx % d_dirs);
	minidx /= d_dirs;
	auto nc = minidx % n;
	auto nr = minidx / n;
	grid[nr][nc] = dmap[d];
	if (steps == maxmoves - 1) {
	    auto [dr, dc] = delta[d]; 
	    for (auto t = minmoves - 1; t--; ) {
		nr -= dr;
		nc -= dc;
		grid[nr][nc] = dmap[d];
	    }
	}
	minidx = next;
	r = nr;
	c = nc;
    }
    for (auto &row: grid)
    	clog << row << '\n';
    clog << endl;
#endif
    return 0;
}
