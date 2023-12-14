#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    vector<string> vgrid;
#define DEBUG 1
#if DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
    while(cin >> s)
	vgrid.push_back(s);
    constexpr uint64_t cycles = 1'000'000'000u;
    const unsigned m = vgrid.size();
    const unsigned n = vgrid[0].size();
    vector<unsigned> vlimit(n);
    vector<unsigned> hlimit(m);
    unsigned res = 0;
    vector<string> hgrid(n, string(m, '.'));
    static constexpr size_t hpow = 10007;
    unordered_map<size_t, unsigned> memo; // hash -> cycle
    for (unsigned cycle = 0; cycle < cycles; ++cycle) {
	// north
	fill_n(vlimit.begin(), n, 0);
	for (auto &hrow: hgrid)
	    fill_n(hrow.begin(), m, '.');
	size_t hash = 1;
	for (unsigned r = 0; r < m; ++r) {
	    auto &row = vgrid[r];
	    for (unsigned c = 0; c < n; ++c) {
		auto g = row[c];
		if (g == '#') {
		    hgrid[c][r] = g;
		    vlimit[c] = r + 1;
		    continue;
		} else if (g == '.') {
		    continue;
		}
		hash = hash*hpow + vlimit[c]*n + c;
		hgrid[c][vlimit[c]] = g;
		++vlimit[c];
	    }
	}
	auto x = memo.try_emplace(hash, cycle);
	if (!x.second) {
	    uint64_t loop_length = cycle - x.first->second;
	    if (cycles - cycle > loop_length) {
		debug(clog << "cycle " << x.first->second << ' ' << cycle << '>');
		cycle += (cycles - cycle)/loop_length*loop_length;
		debug(clog << cycle << endl);
	    }
	}
	//debug(for (auto &r: hgrid) clog << r << endl);
	//debug(clog << endl);
	// west
	fill_n(hlimit.begin(), m, 0);
	for (auto &row: vgrid)
	    fill_n(row.begin(), n, '.');
	for (unsigned r = 0; r < n; ++r) {
	    auto &row = hgrid[r];
	    for (unsigned c = 0; c < m; ++c) {
		auto g = row[c];
		if (g == '#') {
		    vgrid[m - 1 - c][r] = g;
		    hlimit[c] = r + 1;
		    continue;
		} else if (g == '.') {
		    continue;
		}
		vgrid[m - 1 - c][hlimit[c]] = g;
		++hlimit[c];
	    }
	}
	//debug(for (auto &r: vgrid) clog << r << endl);
	//debug(clog << endl);
	// south
	fill_n(vlimit.begin(), m, 0);
	for (auto &hrow: hgrid)
	    fill_n(hrow.begin(), m, '.');
	for (unsigned r = 0; r < m; ++r) {
	    auto &row = vgrid[r];
	    for (unsigned c = 0; c < n; ++c) {
		auto g = row[c];
		if (g == '#') {
		    hgrid[n - 1 - c][m - 1 - r] = g;
		    vlimit[c] = r + 1;
		    continue;
		} else if (g == '.') {
		    continue;
		}
		hgrid[n - 1 - c][m - 1 - vlimit[c]] = g;
		++vlimit[c];
	    }
	}
	//debug(for (auto &r: hgrid) clog << r << endl);
	//debug(clog << endl);
	// east
	fill_n(hlimit.begin(), m, 0);
	for (auto &row: vgrid)
	    fill_n(row.begin(), m, '.');
	for (unsigned r = 0; r < n; ++r) {
	    auto &row = hgrid[r];
	    for (unsigned c = 0; c < m; ++c) {
		auto g = row[c];
		if (g == '#') {
		    vgrid[c][n - 1 - r] = g;
		    hlimit[c] = r + 1;
		    continue;
		} else if (g == '.') {
		    continue;
		}
		vgrid[c][n - 1 - hlimit[c]] = g;
		++hlimit[c];
	    }
	}
	//debug(for (auto &r: vgrid) clog << r << endl);
	//debug(clog << '!' << endl);
    }
    for (unsigned r = 0; r < m; ++r) {
	auto &row = vgrid[r];
	for (unsigned c = 0; c < n; ++c) {
	    auto g = row[c];
	    if (g == '#') {
		continue;
	    } else if (g == '.') {
		continue;
	    }
	    res += m - r;
	}
    }
    cout << res << endl;
    return 0;
}
