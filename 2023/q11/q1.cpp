#include <bits/stdc++.h>
using namespace std;
#define debug(...)
//#define debug(...) __VA_ARGS__
int main() {
    string s;
    //vector<pair<unsigned, unsigned>> gal;
    //vector<string> grid;
    map<unsigned,vector<unsigned>> gals; // column->galaxy rows
    for(unsigned row = 0; cin >> s; ++row) {
	//grid.emplace_back(s);
	size_t cnt = 0;
	debug(clog << '@' << row);
	for (size_t pos = 0;; ) {
	    auto next = s.find('#', pos);
	    if (next == string::npos)
		break;
	    debug(clog << ' ' << next);
	    gals[next].push_back(row);
	    ++cnt;
	    pos = next + 1;
	}
	if (cnt == 0) {
	    ++row; // double empty rows
	    debug(clog << 'E' << row);
	}
	debug(clog << endl);
    }
    vector<pair<int, int>> garr;
    unsigned prev = -1;
    unsigned add = 0;
    for (auto &[col,rows]: gals) {
	add += col - prev - 1;
	debug(clog << col << '+' << add << endl);
	for (auto r: rows)
	    garr.emplace_back(r, col + add);
	prev = col;
    }
    debug(for (auto [i, j]: garr) clog << i <<','<<j<<' '; clog << endl);
    uint64_t res = 0;
    for (unsigned i = 0; i < garr.size(); ++i) {
	auto [ir,ic] = garr[i];
	for (unsigned j = 0; j < i; ++j) {
	    auto [jr,jc] = garr[j];
	    res += abs(jr - ir) + abs(ic - jc);
	}
    }
    cout << res << endl;
    //const auto n = grid.back().size();
    //const auto m = grid.size();
    return 0;
}
