#include <bits/stdc++.h>
using namespace std;
#define debug(...)
//#define debug(...) __VA_ARGS__
int main() {
    string s;
    //vector<pair<uint64_t, uint64_t>> gal;
    //vector<string> grid;
    //constexpr uint64_t multiplier = 10; // for test
    constexpr uint64_t multiplier = 1'000'000; // for test
    map<uint64_t,vector<uint64_t>> gals; // column->galaxy rows
    size_t gsize = 0;
    for(uint64_t row = 0; cin >> s; ++row) {
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
	gsize += cnt;
	if (cnt == 0) {
	    row += multiplier - 1; // double empty rows
	    debug(clog << 'E' << row);
	}
	debug(clog << endl);
    }
    vector<pair<int64_t, int64_t>> garr;
    garr.reserve(gsize);
    uint64_t prev = 0; --prev;
    uint64_t add = 0;
    for (auto &[col,rows]: gals) {
	add += (col - prev - 1)*(multiplier - 1);
	debug(cout << col << '+' << add << endl);
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
