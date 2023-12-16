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
#define DEBUG 0
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
    vector<uint8_t> visited(mn);
    queue<tuple<int, int, dir>> q;
    static const array<pair<int, int>, 4> delta {{{0, +1}, {-1, 0}, {0, -1}, {+1, 0}}};
    static const array<dir, 4>  fslashmap { d_up, d_right, d_down, d_left };
    static const array<dir, 4>  bslashmap { d_down, d_left, d_up, d_right };
    auto check = [&](int r0, int c0, dir d0) {
	visited.clear();
	visited.resize(mn);
    q.emplace(r0, c0, d0);
    visited[r0*n+c0] |= 1<<d0;
#define ENQ(R, C, D) do { \
    if (R >= 0 && C >= 0 && R < m && C < n && !(visited[(R)*n+(C)] & (1u<<(D)))) { \
	debug(clog << '>' << (R) << ',' << (C) << ';' << (D)); \
	visited[(R)*n+(C)] |= 1u<<(D); \
	q.emplace((R), (C), (D)); \
    } \
} while(0)
    while(!q.empty()) {
	auto [r, c, d] = q.front();
	q.pop();
	debug(clog << r << ',' << c << ';' << d);
	switch(grid[r][c]) {
	    case '.':
		ENQ(r + delta[d].first, c + delta[d].second, d);
		break;
	    case '/':
		// 0, 1 -> -1, 0 // right -> up [+1]
		// 1, 0 -> 0, -1 // down -> left [-1]
		// 0, -1 -> 1, 0 // left -> down [+1]
		// -1, 0 -> 0, 1 // up -> right [-1]
		ENQ(r - delta[d].second, c - delta[d].first, fslashmap[d]);
		break;
	    case '\\':
		// 0, 1 -> 1, 0 // right -> down
		// 1, 0 -> 0, 1 // down -> right
		// 0, -1 -> -1, 0 // left -> up
		// -1, 0 -> 0, 1 // up -> left
		ENQ(r + delta[d].second, c + delta[d].first, bslashmap[d]);
		break;
	    case '-':
		if (delta[d].second)
		    ENQ(r + delta[d].first, c + delta[d].second, d);
		else {
		    ENQ(r, c - 1, d_left);
		    ENQ(r, c + 1, d_right);
		}
		break;
	    case '|':
		if (delta[d].first)
		    ENQ(r + delta[d].first, c + delta[d].second, d);
		else {
		    ENQ(r - 1, c, d_up);
		    ENQ(r + 1, c, d_down);
		}
		break;
	    default:
		assert(0);
	}
	debug(clog << '\n');
    }
    unsigned res = 0;
    for (int i = 0; i < m; ++i) {
    	for (int j = 0; j < n; ++j) {
	    res += 0 != (visited[i*n+j]);
	    debug(clog << (visited[i*n+j] ? '#' : '.'));
	}
	debug(clog << '\n');
    }
    return res;
};
    unsigned maxr = 0;
    for (int i = 0; i < m; ++i) {
	maxr = max(maxr, check(i, 0, d_right));
	maxr = max(maxr, check(i, n - 1, d_left));
    }
    for (int j = 0; j < n; ++j) {
	maxr = max(maxr, check(0, j, d_down));
	maxr = max(maxr, check(m - 1, j, d_up));
    }
    cout << maxr << endl;
    return 0;
}
