#include <bits/stdc++.h>
using namespace std;
enum dir { d_right, d_up, d_left, d_down, d_dirs };
static array<string, d_dirs> dirmap {"right", "up", "left", "down" };
ostream &operator << (ostream &os, dir d) {
    return os << dirmap[d];
}
array<char, d_dirs> dircmap { '>','^','<','v' };
int main() {
#define DEBUG 1
#if DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
    int r = 0, c = 0;
    vector<pair<dir,int>> ins;
    char ch;
    static const array<pair<int, int>, d_dirs> delta {{{0, +1}, {-1, 0}, {0, -1}, {+1, 0}}};
    vector<int> rarr {0};
    vector<int> carr {0};
    while(cin >> ch) {
	dir d;
	int dist;
	uint32_t color;
	cin >> dist;
	cin >> ch; assert(ch == '(');
	cin >> ch; assert(ch == '#');
	cin >> hex >> color >> dec;
	cin >> ch; assert(ch == ')');
	switch(color & 15) {
	    case 0: d = d_right; break;
	    case 2: d = d_left; break;
	    case 3: d = d_up; break;
	    case 1: d = d_down; break;
	    default: assert(0);
	}
	dist = color >> 4;
	assert(dist > 0);
	ins.emplace_back(d, dist);
	auto [dr, dc] = delta[d];
	r += dist*dr; c += dist*dc;
	rarr.push_back(r);
	carr.push_back(c);
	//debug(clog << r <<','<< c << ' ' << color << endl);
	//rmin = min(r, rmin); cmin = min(c, cmin);
	//rmax = max(r, rmax); cmax = max(c, cmax);
    }
    debug(clog<<r<<','<<c<<endl);
    sort(rarr.begin(), rarr.end()); rarr.erase(unique(rarr.begin(), rarr.end()), rarr.end());
    sort(carr.begin(), carr.end()); carr.erase(unique(carr.begin(), carr.end()), carr.end());
    debug(for (unsigned i = 1; i < rarr.size(); ++i) { clog << rarr[i] - rarr[i - 1] << ' '; } clog << endl); 
    debug(for (unsigned i = 1; i < carr.size(); ++i) { clog << carr[i] - carr[i - 1] << ' '; } clog << endl); 
    const auto m = rarr.size();
    const auto n = carr.size();
    const auto m3 = 3*m;
    const auto n3 = 3*n;
    vector<string> grid(m3, string(n3, ' ' ));
    int rs = lower_bound(rarr.cbegin(), rarr.cend(), 0) - rarr.cbegin();
    int cs = lower_bound(carr.cbegin(), carr.cend(), 0) - carr.cbegin();
    grid[rs*3][cs*3] = '@';
    int ri = 3*rs + 1;
    int ci = 3*cs + 1;
    r = 0; c = 0;
    int64_t ret = 0;
    unsigned last = ins.size();
    int last_dr = 0;
    while(last-- > 0) {
	auto [dr,dc] = delta[get<0>(ins[last])];
	if (dr) {
	    last_dr = dr;
	    break;
	}
    }
    debug(int64_t drp = 0, drm = 0, dcp = 0, dcm = 0);
    for (auto [d, dist]: ins) {
	auto [dr, dc] = delta[d];
	int rdest = r + dist*dr;
	int cdest = c + dist*dc;
	if (dr > 0 || dc > 0)
	    ret += dist;
	char fillc = dircmap[d];
	if (dr) {
	    if (last_dr != dr)
		grid[ri][ci] = '!';
	    last_dr = dr;
	    fillc = '!';
	}
	debug(if (dr > 0) drp += dist; else if (dr < 0) drm += dist);
	debug(if (dc > 0) dcp += dist; else if (dc < 0) dcm += dist);
	debug(clog << r << ',' << c << '>' << rdest << ',' << cdest << '@' << ri <<',' << ci);
	while(r != rdest || c != cdest) {
	    ri += dr;
	    ci += dc;
	    assert(grid[ri][ci] == ' ');
	    grid[ri][ci] = fillc;
	    r = rarr[ri/3];
	    c = carr[ci/3];
	};
	ri += dr;
	ci += dc;
	assert(grid[ri][ci] == ' ');
	grid[ri][ci] = fillc;
	r = rarr[ri/3];
	c = carr[ci/3];
	debug(clog << '>' << ri << ',' << ci << endl);
    }
    debug(clog << drp << ' ' << drm << ' ' << dcp << ' ' << dcm << endl);
    debug(clog << ret << endl);
    debug(for (auto &row: grid) clog << row << '\n');
    // grid[-rmin][-cmin] = '!';
    //debug(clog << rmin <<'x'<<cmin << ' ' << rmax <<'x'<<cmax << endl);
    ri = 0;
    auto rimod = 0u;
    auto ridiv = 0u;
    //ret = 0;
    for (auto &row: grid) {
	ci = 0;
	auto cimod = 0u;
	auto cidiv = 0u;
	int eo = 0;
	for (auto &ch: row) {
	    if (ch == ' ') {
		if (eo) {
		    if (rimod == 0 && cimod == 0) {
			ret += static_cast<int64_t>(rarr[ridiv] - rarr[ridiv - 1])*(carr[cidiv] - carr[cidiv - 1]);
#if 0
			if (ri < 3 || grid[ri - 3][ci - 0] == ' ')
			    ret += (carr[ci] - carr[ci - 1]);
			if (ci < 3 || grid[ri - 0][ci - 3] == ' ')
			    ret += (rarr[ri] - rarr[ri - 1]);
#endif
			ch = '+';
		    } else {
			ch = '.';
		    }
		}
		debug(clog << ch);
		//debug(clog << (char)(eo ? (rarr[ri] - rarr[ri - 1] && carr[ci] - carr[ci - 1] ? '+' : '0') : ' '));
	    } else {
		if (ch == '!') eo ^= 1;
		debug(clog << ch);
		//++ret;
	    }
	    ++ci;
	    if (++cimod == 3) { cimod = 0; ++cidiv; }
	}
	debug(clog << '\n');
	++ri;
	if (++rimod == 3) { rimod = 0; ++ ridiv; }
    }
    ++ret;
    cout << ret << endl;
    return 0;
}
