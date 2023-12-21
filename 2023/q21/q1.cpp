#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    vector<string> grid;
    size_t sr = UINT_MAX; 
    size_t sc;
    while(cin >> s) {
	if (sr == UINT_MAX && (sc = s.find('S')) != string::npos)
	    sr = grid.size();
	grid.push_back(s);
    }
    assert(sr != UINT_MAX);
    const unsigned m = grid.size();
    const unsigned n = grid[0].size();
    //clog << m << 'x' << n << endl;
    const unsigned mn = m*n;
    vector<bool> visited;
    vector<pair<uint8_t, uint8_t>> cur, next;
    cur.emplace_back(sr, sc);
    for (unsigned steps = 0; steps < 64; ++steps) {
	visited.clear();
	visited.resize(mn);
	next.clear();
	for (auto [r, c]: cur) {
#define ENQ(CHECK, R, C) do { \
    if (!(CHECK)) break; \
    if (grid[R][C] == '#') break; \
    if (visited[(R)*n+(C)]) break; \
    visited[(R)*n+(C)] = true; \
    next.emplace_back(R, C); \
} while(0)
	    ENQ(r > 0, r - 1, c);
	    ENQ(c > 0, r, c - 1);
	    ENQ(r + 1 != m, r + 1, c);
	    ENQ(c + 1 != n, r, c + 1);
	}
	swap(next, cur);
    }
    cout << cur.size() << endl;
    return 0;
}
