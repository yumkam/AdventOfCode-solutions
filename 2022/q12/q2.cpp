#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	vector<string> grid;
	string s;
	while(getline(cin, s) && s.length())
	    grid.push_back(s);
	const auto m = grid.size();
	const auto n = grid[0].length();
	unsigned sr, sc, er, ec;
	for (unsigned i = 0; i < m; i++) {
	    for (unsigned j = 0; j < n; j++) {
		if (grid[i][j] == 'S') {
		    grid[i][j] = 'a';
		    sr = i; sc = j;
		}
		if (grid[i][j] == 'E') {
		    grid[i][j] = 'Z';
		    er = i; ec = j;
		}
	    }
	}
	queue<pair<unsigned,unsigned>> q;
	q.emplace(er, ec);
	unsigned depth = 0;
	for (;;) {
	    auto l = q.size();
	    if (l == 0)
		break;
	    while(l--) {
		auto [r, c] = q.front();
		q.pop();
		if (grid[r][c] == 'A') {
		    cout << depth << endl;
		    return 0;
		}
		auto minheight = grid[r][c] - 'A';
#define ENQ(CHECK, R, C) \
		if (CHECK && islower(grid[R][C]) && grid[R][C] - 'a' + 1 >= minheight) { \
		    grid[R][C] ^= 'a' ^ 'A'; \
		    q.emplace(R, C); \
		}
		ENQ(r > 0, r - 1, c);
		ENQ(c > 0, r, c - 1);
		ENQ(r + 1 < m, r + 1, c);
		ENQ(c + 1 < n, r, c + 1);
	    }
	    ++depth;
	}
	return 1;
}
