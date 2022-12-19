#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    // robot type: [ore clay obsidan geode]
    // resources: [ore, clay, obsidan]
    array<array<unsigned,3>,4> costs {{0}};
    string s;
    unsigned i;
    char c;
    unsigned ret = 0;
    while(cin >> s >> i >> c) { // <Blueprint> $num <:>
	int blueprint = i;
	// <Each> <ore> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >>  i >> s;
	clog << s;
	array<unsigned,3> limit;
	costs[0][0] = i;
	limit[0] = i;
	// <Each> <clay> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[1][0] = i;
	limit[0] = max(i, limit[0]);
	// <Each> <obsidan> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[2][0] = i;
	limit[0] = max(i, limit[0]);
	// and $num <clay>
	cin >> s >> i >> s;
	costs[2][1] = i;
	limit[1] = i;
	// <Each> <geode> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[3][0] = i;
	limit[0] = max(i, limit[0]);
	// and $num <obsidan>
	cin >> s >> i >> s;
	costs[3][2] = i;
	limit[2] = i;
	for (unsigned type = 0; type < 4; type++) {
	    for (auto c: costs[type])
		clog << c << ' ';
	    clog << endl;
	}
	// state: { collected: ore, clay, obsidan, geode; robots: ore, clay, obsidan, geode }
	deque<array<array<uint8_t,4>, 2>> state, next;
	state.emplace_back();
	state.front()[1][0] = 1;
	for (unsigned day = 1; day <= 24; day++) {
	    next.clear();
	    //next.reserve(state.size()*2);
	    clog << "day " << day;
	    unsigned ins = 0;
	    for (auto &s: state) {
		auto save = s[0];
		//clog << '<' << s[0][0] << ' ' << s[0][1] << ' ' << s[0][2] << ' ' << s[0][3] << '@'
		//    << s[1][0] << ' ' << s[1][1] << ' ' << s[1][2] << ' ' << s[1][3] << ' ' << endl;
		s[0][0] += s[1][0];
		s[0][1] += s[1][1];
		s[0][2] += s[1][2];
		s[0][3] += s[1][3];
		for (unsigned i = 0; i < 3; i++) {
		    if (save[i] <= limit[i]) {
			next.push_back(s);
			ins++;
			break;
		    }
		}

		//clog << '>'  << next.back()[0][0] << ' ' << next.back()[0][1] << ' ' << next.back()[0][2] << ' ' << next.back()[0][3] << '@'
		//    << next.back()[1][0] << ' ' << next.back()[1][1] << ' ' << next.back()[1][2] << ' ' << next.back()[1][3] << ' ' << endl;
		for (unsigned type = 0; type < 4; type++) {
		    if (save[0] >= costs[type][0] && save[1] >= costs[type][1] && save[2] >= costs[type][2]) {
			auto t = s;
			t[0][0] -= costs[type][0];
			t[0][1] -= costs[type][1];
			t[0][2] -= costs[type][2];
			t[1][type]++;
			next.push_back(t);
			ins++;
			//clog << '>'  << next.back()[0][0] << ' ' << next.back()[0][1] << ' ' << next.back()[0][2] << ' ' << next.back()[0][3] << '@'
			//    << next.back()[1][0] << ' ' << next.back()[1][1] << ' ' << next.back()[1][2] << ' ' << next.back()[1][3] << ' ' << endl;
		    }
		}
	    }
	    sort(next.begin(), next.end());
	    next.erase(unique(next.begin(), next.end()), next.end());
	    clog << ' ' << next.size() << ' ' << ins - next.size() << endl;
	    state.swap(next);
	}
	unsigned maxg = 0;
	for (auto &s: state)
	    maxg = max<unsigned>(maxg, s[0][3]);
	clog << blueprint << ' ' << maxg << endl;
	ret += blueprint*maxg;
    }
    cout << ret << endl;
    return 0;
}
