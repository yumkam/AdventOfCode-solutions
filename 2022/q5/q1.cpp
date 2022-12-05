#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	int ret = 0;
	vector<vector<char>> stacks;
	for (;;) {
	    string s;
	    getline(cin, s);
	    if (s.length() == 0)
		break;
	    if (s[1] == '1')
		continue;
	    for (unsigned i = 1, j = 0; i < s.length(); i += 4, j++) {
		if (s[i] == ' ')
		    continue;
		if (j >= stacks.size())
		    stacks.resize(j + 1);
		stacks[j].push_back(s[i]);
	    }
	}
	for (auto &s: stacks)
	    reverse(s.begin(), s.end());
	string s;
	unsigned n, from, to;
	for (auto &s: stacks) {
	    for (auto c: s) clog << c;
	    clog << endl;
	}
	while((cin >> s >> n >> s >> from >> s >> to)) {
	    from--;
	    to--;
	    while(n--) {
		stacks[to].push_back(stacks[from].back());
		stacks[from].pop_back();
	    }
	}
	for (auto &s: stacks)
	    cout << s.back();
	cout << endl;
	return 0;
}
