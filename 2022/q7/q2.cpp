#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	//vector<pair<string, size_t>> paths;
	//string path;
	//unordered_map<string, size_t> dirsize;
	// $ ls
	// 012345
	// $ cd /
	vector<size_t> paths;
	size_t csize = 0;
	size_t ret = 0;
	const size_t disksize = 70000000;
	const size_t freemin = 30000000;
	vector<size_t> dirsizes;
	string s;
	while(getline(cin, s)) {
	    if (s[0] == '$') {
		if (s[2] == 'l')
		    continue;
		if (s[5] == '/') {
		    continue;
		}
		if (s.length() == 7 && s[5] == '.' && s[6] == '.') {
		    //path.resize(path.size() - paths.back().first.length() - 1, ' ');
		    //if (csize <= limit)
		    //	ret += csize;
		    dirsizes.push_back(csize);
		    csize = paths.back() += csize;
		    paths.pop_back();
		} else {
		    paths.push_back(csize);
		    csize = 0;
		}
		continue;
	    }
	    if (s[0] == 'd')
		continue;
	    csize += stol(s);
	}
	while(!paths.empty()) {
	    //if (csize <= limit)
	    //	ret += csize;
	    dirsizes.push_back(csize);
	    csize = paths.back() += csize;
	    paths.pop_back();
	}
	clog << csize << endl;
	ret = SIZE_MAX;
	for (auto ds: dirsizes) {
	    //clog << ds << endl;
	    if (disksize - (csize - ds) >= freemin && ds < ret)
		ret = ds;
	}
	cout << ret << endl;
	return 0;
}
