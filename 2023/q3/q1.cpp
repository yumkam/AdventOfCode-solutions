#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<string> grid;
    string s;
    while(cin >> s)
	grid.push_back(s);
    const unsigned m = grid.size();
    const unsigned n = grid[0].size();
    unsigned ret = 0;
    for (unsigned i = 0; i < m; ++i) {
	unsigned num = 0;
	bool part = false;
	auto &r = grid[i];
	for (unsigned j = 0; j < n; ++j) {
	    if (isdigit(r[j])) {
		num = num*10 + (r[j] - '0');
		if (!part) {
		    if (i > 0) {
			auto &row = grid[i - 1];
			if (j > 0) part |= row[j - 1] != '.' && !isdigit(row[j - 1]);
			part |= row[j] != '.' && !isdigit(row[j]);
			if (j + 1 < n) part |= row[j + 1] != '.' && !isdigit(row[j + 1]);
		    }
		    {
			auto &row = grid[i];
			if (j > 0) part |= row[j - 1] != '.' && !isdigit(row[j - 1]);
			part |= row[j] != '.' && !isdigit(row[j]);
			if (j + 1 < n) part |= row[j + 1] != '.' && !isdigit(row[j + 1]);
		    }
		    if (i + 1 < m) {
			auto &row = grid[i + 1];
			if (j > 0) part |= row[j - 1] != '.' && !isdigit(row[j - 1]);
			part |= row[j] != '.' && !isdigit(row[j]);
			if (j + 1 < n) part |= row[j + 1] != '.' && !isdigit(row[j + 1]);
		    }
		}
	    } else {
		if (part) ret += num;
		num = 0;
		part = r[j] != '.';
	    }
	}
	if (part) ret += num;
    }
    cout << ret << endl;
    return 0;
}
