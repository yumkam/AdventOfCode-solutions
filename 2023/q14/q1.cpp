#include <bits/stdc++.h>
using namespace std;
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
    const unsigned m = grid.size();
    const unsigned n = grid[0].size();
    vector<unsigned> limit(n);
    unsigned res = 0;
    vector<string> out(m, string(n, '.'));
    for (unsigned r = 0; r < m; ++r) {
	auto &row = grid[r];
	for (unsigned c = 0; c < n; ++c) {
	    auto g = row[c];
	    if (g == '#') {
		out[r][c] = g;
		limit[c] = r + 1;
		continue;
	    } else if (g == '.') {
		continue;
	    }
	    out[limit[c]][c] = g;
	    res += m - limit[c];
	    ++limit[c];
	}
    }
#if DEBUG
    for (auto &r: out) clog << r << endl;
#endif
    cout << res << endl;
    return 0;
}
