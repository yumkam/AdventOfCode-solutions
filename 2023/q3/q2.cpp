#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<string> grid;
    string s;
    while(cin >> s)
	grid.push_back(s);
    const unsigned m = grid.size();
    const unsigned n = grid[0].size();
    uint64_t ret = 0;
    vector<vector<vector<unsigned>>> gnum(m, vector<vector<unsigned>>(n));
    for (unsigned i = 0; i < m; ++i) {
	unsigned num = 0;
	unsigned nlen = 0;
	auto &r = grid[i];
	auto check = [&](auto e) {
	    auto low = max<unsigned>(e - nlen, 1) - 1;
	    auto high = min(e + 1, n); 
	    {
		auto &grow = gnum[i];
		if (r[low] == '*')
		    grow[low].push_back(num);
		if (r[high - 1] == '*')
		    grow[high - 1].push_back(num);
	    }
	    if (i > 0) {
		auto &row = grid[i - 1];
		auto &grow = gnum[i - 1];
		for(auto j = low; j < high; ++j)
		    if (row[j] == '*') grow[j].push_back(num);
	    }
	    if (i + 1 < m) {
		auto &row = grid[i + 1];
		auto &grow = gnum[i + 1];
		for(auto j = low; j < high; ++j)
		    if (row[j] == '*') grow[j].push_back(num);
	    }
	};
	for (unsigned j = 0; j < n; ++j) {
	    if (isdigit(r[j])) {
		num = num*10 + (r[j] - '0');
		++nlen;
	    } else {
		if (nlen)
		    check(j);
		nlen = 0;
		num = 0;
	    }
	}
	if (nlen)
	    check(n);
    }
    for (auto &grow: gnum)
	for (auto &g: grow)
	    if (g.size() == 2)
		ret += g[0]*g[1];
    cout << ret << endl;
    return 0;
}
