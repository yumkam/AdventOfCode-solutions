#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	// $ ls
	// 012345
	// $ cd /
	vector<string> grid;
	for(string s; getline(cin, s) && s.length(); )
	    grid.push_back(s);
	clog << "ok\n";
	unsigned ret = 0;
	unsigned m = grid.size();
	unsigned n = grid[0].size();
	string maxv(m, ' ');
	string maxh(n, ' ');
	vector<vector<bool>> visible(m, vector<bool>(n));
	for (unsigned i = 0; i < m; i++)
	    for (unsigned j = 0; j < n; j++) {
		if (grid[i][j] > maxv[i]) {
		    maxv[i] = grid[i][j];
		    ret += !visible[i][j];
		    visible[i][j] = true;
		}
		if (grid[i][j] > maxh[j]) {
		    maxh[j] = grid[i][j];
		    ret += !visible[i][j];
		    visible[i][j] = true;
		}
	    }
	fill(maxv.begin(), maxv.end(), ' ');
	fill(maxh.begin(), maxh.end(), ' ');
	for (unsigned i = m; i--; )
	    for (unsigned j = n; j--; ) {
		if (grid[i][j] > maxv[i]) {
		    maxv[i] = grid[i][j];
		    ret += !visible[i][j];
		    visible[i][j] = true;
		}
		if (grid[i][j] > maxh[j]) {
		    maxh[j] = grid[i][j];
		    ret += !visible[i][j];
		    visible[i][j] = true;
		}
	    }
	cout << ret << endl;
	return 0;
}
