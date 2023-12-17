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
    vector<uint8_t> visited(mn);
    visited[0*n+0] |= 1<<d_right;
    queue<tuple<int, int, dir>> q;
    q.emplace(0, 0, d_right);
    static const array<pair<int, int>, 4> delta {{{0, +1}, {-1, 0}, {0, -1}, {+1, 0}}};
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
		static_assert((d_right ^ 1) == d_up);  // 0, +1 -> -1, 0 // right -> up
		static_assert((d_up ^ 1) == d_right);  // -1, 0 -> 0, +1 // up -> right
		static_assert((d_left ^ 1) == d_down); // 0, -1 -> +1, 0 // left -> down
		static_assert((d_down ^ 1) == d_left); // +1, 0 -> 0, -1 // down -> left
		ENQ(r - delta[d].second, c - delta[d].first, (dir)(d^1));
		break;
	    case '\\':
		static_assert((d_right ^ 3) == d_down); // 0, +1 -> +1, 0 // right -> down
		static_assert((d_up ^ 3) == d_left);    // -1, 0 -> 0, +1 // up -> left
		static_assert((d_left ^ 3) == d_up);    // 0, -1 -> -1, 0 // left -> up
		static_assert((d_down ^ 3) == d_right); // +1, 0 -> 0, +1 // down -> right
		ENQ(r + delta[d].second, c + delta[d].first, (dir)(d^3));
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
    cout << res << endl;
    return 0;
}
