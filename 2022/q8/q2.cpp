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
	unsigned ret = 0;
	unsigned m = grid.size();
	unsigned n = grid[0].size();
	clog << m << '*' << n << endl;
	string maxv(m, ' ');
	string maxh(n, ' ');
	vector<vector<unsigned>> score(m, vector<unsigned>(n, 1));
	vector<unsigned> stack;
	for (unsigned i = 0; i < m; i++) {
	    stack.clear();
	    for (unsigned j = 0; j < n; j++) {
		while(!stack.empty() && grid[i][stack.back()] < grid[i][j])
		    stack.pop_back();
		if (stack.empty())
		    score[i][j] *= j;
		else
		    score[i][j] *= j - stack.back();
		stack.push_back(j);
	    }
	}
	for (unsigned j = 0; j < n; j++) {
	    stack.clear();
	    for (unsigned i = 0; i < m; i++) {
		while(!stack.empty() && grid[stack.back()][j] < grid[i][j])
		    stack.pop_back();
		if (stack.empty())
		    score[i][j] *= i;
		else
		    score[i][j] *= i - stack.back();
		stack.push_back(i);
	    }
	}
	for (unsigned i = m; i--; ) {
	    stack.clear();
	    for (unsigned j = n; j--; ) {
		while(!stack.empty() && grid[i][stack.back()] < grid[i][j])
		    stack.pop_back();
		if (stack.empty())
		    score[i][j] *= n - 1 - j;
		else
		    score[i][j] *= stack.back() - j;
		stack.push_back(j);
	    }
	}
	for (unsigned j = n; j--; ) {
	    stack.clear();
	    for (unsigned i = m; i--; ) {
		while(!stack.empty() && grid[stack.back()][j] < grid[i][j])
		    stack.pop_back();
		if (stack.empty())
		    score[i][j] *= m - 1 - i;
		else
		    score[i][j] *= stack.back() - i;
		stack.push_back(i);
	    }
	}
	#if 0
	vector<unsigned> maxr(m);
	vector<unsigned> maxc(n);
	for (unsigned i = 0; i < m; i++) {
	    for (unsigned j = 0; j < n; j++) {
		if (grid[i][j] > maxv[i])
		    score[i][j] *= j;
		else
		    score[i][j] *= j - maxr[i];
		clog << maxr[i] << 'r';
		if (grid[i][j] >= maxv[i]) {
		    maxv[i] = grid[i][j];
		    maxr[i] = j;
		}
		if (grid[i][j] > maxh[j])
		    score[i][j] *= i;
		else
		    score[i][j] *= i - maxc[j];
		clog << maxc[j] << 'c';
		if (grid[i][j] >= maxh[j]) {
		    maxh[j] = grid[i][j];
		    maxc[j] = i;
		}
		clog << grid[i][j] << '/' << score[i][j] << ' ';
	    }
	    clog << endl;
	}
	fill(maxv.begin(), maxv.end(), ' ');
	fill(maxh.begin(), maxh.end(), ' ');
	fill(maxr.begin(), maxr.end(), n);
	fill(maxc.begin(), maxc.end(), m);
	for (unsigned i = m; i--; )
	    for (unsigned j = n; j--; ) {
		if (grid[i][j] > maxv[i])
		    score[i][j] *= n - j - 1;
		else
		    score[i][j] *= maxr[i] - j;
		if (grid[i][j] >= maxv[i]) {
		    maxv[i] = grid[i][j];
		    maxr[i] = j;
		}
		if (grid[i][j] > maxh[j])
		    score[i][j] *= m - i - 1;
		else
		    score[i][j] *= maxc[j] - i;
		if (grid[i][j] >= maxh[j]) {
		    maxh[j] = grid[i][j];
		    maxc[j] = i;
		}
	    }
	#endif
	unsigned maxscore = 0;
	for (unsigned i = 0; i < m; i++) {
	    for (unsigned j = 0; j < n; j++) {
		clog << score[i][j] << ' ';
		maxscore = max(maxscore, score[i][j]);
	    }
	    clog << endl;
	}
	cout << maxscore << endl;
	return 0;
}
