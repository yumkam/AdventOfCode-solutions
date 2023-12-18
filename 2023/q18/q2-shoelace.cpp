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
    int64_t area = 0;
    int64_t maxa = 0;
    int64_t maxb = 0;
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
	//ins.emplace_back(d, dist);
	auto [dr, dc] = delta[d];
	auto prevr = r; auto prevc = c;
	r += dist*dr; c += dist*dc;
	//area += static_cast<int64_t>(r + prevr)*(prevc - c);
	area += static_cast<int64_t>(c + prevc)*(r - prevr);
	//area += static_cast<int64_t>(prevc)*r - static_cast<int64_t>(c)*prevr;
	maxa = max(maxa, abs(static_cast<int64_t>(r + prevr)*(prevc - c)));
	maxb = max(maxb, abs(static_cast<int64_t>(c + prevc)*(r - prevr)));
	//maxb = max(maxb, abs(static_cast<int64_t>(prevc)*r - static_cast<int64_t>(c)*prevr));
	area += dist;
    }
    //clog << maxa << endl << maxb << endl;
    assert(area >= 0);
    assert(area%2 == 0);
    area /= 2;
    ++area;
    cout << area << endl;
    return 0;
}
