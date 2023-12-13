#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    vector<string> grid;
    unsigned ret = 0;
#if DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
    for (;;) {
	grid.clear();
	while(getline(cin, s)) {
	    if (s.length() == 0)
		break;
	    grid.push_back(s);
	}
	if (grid.empty())
	    break;
	unsigned res = 0;
	const unsigned m = grid.size();
	const unsigned n = grid[0].size();
#if DEBUG
	clog << m << '*' << n << endl;
	for (unsigned j = 1; j <= n; ++j)
	    clog << (char)(j % 10 != 0 ? ' ' : '0'+j/10);
	clog << endl;
	for (unsigned j = 1; j <= n; ++j)
	    clog << j%10;
	clog << endl;
	for (unsigned i = 0; i < m; ++i) {
	    auto &r = grid[i];
	    clog << r << ' ' << i + 1 << endl;
	}
#endif
	for (unsigned j = 1; j < n; ++j) {
	    for (unsigned i = 0; i < m; ++i) {
		for (unsigned t = 0, l = min(n - j, j); t < l; ++t) {
		    if (grid[i][j - t - 1] != grid[i][j + t]) {
			debug(clog << j << 'r' << i << 'c' << j - t - 1 << '!' << j + t <<  grid[i][j - t - 1] << grid[i][j + t] << endl);
			goto not_v_mirror;
		    }
		}
	    }
	    assert(res == 0);
	    debug(clog << 'v'<< j<< endl);
	    res += j;
not_v_mirror:;
	}
	for (unsigned i = 1; i < m; ++i) {
	    for (unsigned j = 0; j < n; ++j) {
		for (unsigned t = 0, l = min(m - i, i); t < l; ++t) {
		    if (grid[i - t - 1][j] != grid[i + t][j]) {
			debug(clog << i << 'c' << j << 'r' << i - t - 1 << '!' << i + t <<  grid[i - t - 1][j] << grid[i + t][j] << endl);
			goto not_h_mirror;
		    }
		}
	    }
	    assert(res == 0);
	    debug(clog << 'h' << i << endl);
	    res += i*100;
not_h_mirror:;
	}
	res = 0;
	for (unsigned j = 1; j < n; ++j) {
	    unsigned smudges = 0;
	    for (unsigned i = 0; i < m; ++i) {
		for (unsigned t = 0, l = min(n - j, j); t < l; ++t) {
		    smudges += (grid[i][j - t - 1] != grid[i][j + t]);
		}
	    }
	    if (smudges == 1) {
		assert(res == 0);
		debug(clog << 'V'<< j<< endl);
		res += j;
	    }
	}
	for (unsigned i = 1; i < m; ++i) {
	    unsigned smudges = 0;
	    for (unsigned j = 0; j < n; ++j) {
		for (unsigned t = 0, l = min(m - i, i); t < l; ++t) {
		    smudges += (grid[i - t - 1][j] != grid[i + t][j]);
		}
	    }
	    if (smudges == 1) {
		assert(res == 0);
		debug(clog << 'H' << i << endl);
		res += i*100;
	    }
	    break;
	}
	assert(res != 0);
	ret += res;
	debug(clog << endl);
    }
    cout << ret << endl;
    return 0;
}
