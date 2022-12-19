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
	//deque<array<array<uint8_t,4>, 2>> state, next;
	vector<array<array<uint8_t,4>, 2>> state, next;
	state.emplace_back();
	state.front()[1][0] = 1;
	const unsigned maxday = 24;
	for (unsigned day = 1; day <= maxday; day++) {
	    next.clear();
	    next.reserve(state.size()*2);
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
			next.push_back(s);
			ins++;

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
	    auto minmaxg = 0;
	    for (auto &s: next) {
		auto curf = s[0][0];
		auto curF = s[1][0];
		auto curc = s[0][0];
		auto curC = s[1][0];
		auto curo = s[0][2];
		auto curO = s[1][2];
		auto curg = s[0][3];
		auto curG = s[1][3];
		// pessimistic scenario: we produce same amount of obsidan every day
		// and build new geode robot once we collected enough obsidan
		for (unsigned nday = day + 1; nday <= maxday; nday++) {
		    curg += curG;
		    if (curo >= costs[3][2] && curf >= costs[3][0]) {
		    	curo -= costs[3][2];
			curf -= costs[3][0];
		    	curG++;
		    } else {
			// we are not producing anything today, try something...
			if ((curF < costs[3][0] || curf < costs[2][0]) && curf >= costs[0][0] && curf - costs[0][0] + curF >= costs[3][0]) {
			    // we are not producing enough ore for making geode robot daily,
			    // we have enough ore to produce ore robot,
			    // and after that we will have enough ore to produce geoge robot
			    curf -= costs[0][0];
			    curF++;
			    curf--; // compensate early curF change
			} else if (curO < costs[3][2] && curf >= costs[2][0] && curf - costs[2][0] + curF >= costs[3][0] && curc >= costs[2][1]) {
			    // we are not producing enough obsidan for making geode robot daily,
			    // we have enough ore to produce obsidan robot,
			    // we have enough clay to produce obsidan robot,
			    // and after that we will have enough ore to produce geoge robot
			    curf -= costs[2][0];
			    curc -= costs[2][1];
			    curO++;
			    curo--; // compensate early curO change
			} else if (curf >= costs[1][0] && curf - costs[1][0] + curF >= costs[3][0]) {
			    curf -= costs[1][0];
			    curC++;
			    curc--;
			}
		    }
		    curo += curO;
		    curc += curC;
		    curf += curF;
		}
		minmaxg = max<unsigned>(minmaxg, curg);
	    }
	    auto end = next.begin();
	    for (auto &s: next) {
		auto curf = s[0][0];
		auto curF = s[1][0];
		auto curo = s[0][2];
		auto curO = s[1][2];
		auto curg = s[0][3];
		auto curG = s[1][3];
		// (overly) optimistic scenario: we take new obsidan and ore robot every day out of thin air
		// and (impossibly) at the same time build new geode robot once we collected obsidan and ore
		for (unsigned nday = day + 1; nday <= maxday; nday++) {
		    curg += curG;
		    if (curg >= minmaxg)
			break;
		    if (curo >= costs[3][2] && curf >= costs[3][0]) {
		    	curo -= costs[3][2];
			curf -= costs[3][0];
		    	curG++;
		    }
		    curo += curO;
		    curO++;
		    curf += curF;
		    curF++;
		}
		// in this overly optimistic scenario, can we beat pessimistic scenario?
		if (curg >= minmaxg)
		    // yes
		    *end++ = s;
		// otherwise, skip this state
	    }
	    //clog << next.end() - end << endl;
	    next.erase(end, next.end());
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
