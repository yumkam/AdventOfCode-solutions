#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	string s;
	vector<int> maxacc;
	int acc = 0;
	size_t maxs = 3;
	if (ac > 1 && av[1][0])
		maxs = atoi(av[1]);
	for(;;) {
		bool eof = !getline(cin, s);
		if (eof || s.empty()) {
			if (maxacc.size() < maxs) {
				maxacc.push_back(acc);
				if (maxacc.size() == maxs)
					make_heap(maxacc.begin(), maxacc.end(), greater<int>());
			} else {
				if (acc > maxacc.front()) {
					pop_heap(maxacc.begin(), maxacc.end(), greater<int>());
					maxacc.back() = acc;
					push_heap(maxacc.begin(), maxacc.end(), greater<int>());
				}
			}
			acc = 0;
			if (eof)
				break;
		} else {
			acc += stoi(s);
		}
	}
	cout << accumulate(maxacc.begin(), maxacc.end(), 0) << endl;
	return 0;
}
