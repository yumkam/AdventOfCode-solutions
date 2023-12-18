#include <bits/stdc++.h>
using namespace std;
enum dir { d_right, d_up, d_left, d_down, d_dirs };
array<string, 4> dirmap {"right", "up", "left", "down" };
ostream &operator << (ostream &os, dir d) {
    return os << dirmap[d];
}
int main() {
#define DEBUG 1
#if DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
    int r = 0, c = 0;
    int rmin = 0, cmin = 0, rmax = 0, cmax = 0;
    vector<tuple<dir,int,uint32_t>> ins;
    char ch;
    static const array<pair<int, int>, d_dirs> delta {{{0, +1}, {-1, 0}, {0, -1}, {+1, 0}}};
    while(cin >> ch) {
	dir d;
	switch(ch) {
	    case 'R': d = d_right; break;
	    case 'L': d = d_left; break;
	    case 'U': d = d_up; break;
	    case 'D': d = d_down; break;
	    default: assert(0);
	}
	int dist;
	uint32_t color;
	cin >> dist;
	cin >> ch; assert(ch == '(');
	cin >> ch; assert(ch == '#');
	cin >> hex >> color >> dec;
	cin >> ch; assert(ch == ')');
	ins.emplace_back(d, dist, color);
	auto [dr, dc] = delta[d];
	r += dist*dr; c += dist*dc;
	rmin = min(r, rmin); cmin = min(c, cmin);
	rmax = max(r, rmax); cmax = max(c, cmax);
    }
    vector<string> grid(rmax - rmin + 1, string(cmax - cmin + 1, ' ' ));
    const int m = grid.size();
    const int n = grid[0].size();
    const auto mn = m*n;
    r = 0; c = 0;
    unsigned last = ins.size();
    int last_dr = 0;
    while(last-- > 0) {
	auto [dr,dc] = delta[get<0>(ins[last])];
	if (dr) {
	    last_dr = dr;
	    break;
	}
    }
    for (auto [d, dist, color]: ins) {
	auto [dr, dc] = delta[d];
	char fillc = '#';
	if (dr) {
	    if (last_dr != dr)
		grid[r - rmin][c - cmin] = '!';
	    last_dr = dr;
	    fillc = '!';
	}
	while(dist--) {
	    r += dr; c += dc;
	    grid[r - rmin][c - cmin] = fillc;
	}
    }
    // grid[-rmin][-cmin] = '!';
    debug(for (auto &row: grid) clog << row << '\n');
    debug(clog << rmin <<'x'<<cmin << ' ' << rmax <<'x'<<cmax << endl);
    int ret = 0;
    for (auto &row: grid) {
	int eo = 0;
	for (auto ch: row) {
	    if (ch == ' ') {
		ret += eo;
		debug(clog << (eo ? '.' : ' '));
	    } else {
		if (ch == '!') eo ^= 1;
		debug(clog << ch);
		++ret;
	    }
	}
	debug(clog << '\n');
    }
    cout << ret << endl;
    return 0;
}
