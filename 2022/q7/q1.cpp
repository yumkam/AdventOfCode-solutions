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
	const size_t limit = 100000;
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
		    if (csize <= limit)
			ret += csize;
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
	    if (csize <= limit)
		ret += csize;
	    csize = paths.back() += csize;
	    paths.pop_back();
	}
	cout << ret << endl;
	return 0;
}
