#include <bits/stdc++.h>
//#include <boost/pool/singleton_pool.hpp>
//struct node_pool { };
//using singleton_node_pool = boost::singleton_pool<node_pool, sizeof(PatriciaNode)>;

using namespace std;
int main(int ac, const char *av[]) {
    // robot type: [ore, clay, obsidian, geode]
    // resources: [ore, clay, obsidian]
    array<array<unsigned,3>,4> costs {{0}};
    string s;
    unsigned i;
    char c;
    uint64_t ret = 1;
    const unsigned maxday = 32;
    const unsigned maxprint = 3;
    map<tuple<uint16_t, uint16_t, uint16_t>, array<uint16_t, 4>> m;
    while(cin >> s >> i >> c) { // <Blueprint> $num <:>
	auto blueprint = i;
	if (blueprint > maxprint) break;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >>  i >> s;
	array<unsigned,3> limits;
	costs[0][0] = i;
	limits[0] = i;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[1][0] = i;
	limits[0] = max(i, limits[0]);
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[2][0] = i;
	limits[0] = max(i, limits[0]);
	// <Each> <XXX> <robot> <costs> $num <ore>
	// <and> $num <clay>
	cin >> s >> i >> s;
	costs[2][1] = i;
	limits[1] = i;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[3][0] = i;
	limits[0] = max(i, limits[0]);
	// <Each> <XXX> <robot> <costs> $num <ore>
	// <and> $num <obsidian>
	cin >> s >> i >> s;
	costs[3][2] = i;
	limits[2] = i;

	for (unsigned type = 0; type < 4; type++) {
	    for (auto c: costs[type])
		clog << c << ' ';
	    clog << endl;
	}
	// state: { collected: ore, clay, obsidian, geode; robots: ore, clay, obsidian, geode }
	deque<array<array<uint16_t,4>, 2>> state, next;

	state.emplace_back();
	state.front()[1][0] = 1;
	for (unsigned day = 1; day <= maxday; day++) {
	    next.clear();
	    //next.reserve(state.size()*2);
	    clog << "day " << day;
	    unsigned ins = 0;
	    for (auto &s: state) {
		auto save = s[0];
		//clog << '<' << s[0][0] << ' ' << s[0][1] << ' ' << s[0][2] << ' ' << s[0][3] << '@'
		//    << s[1][0] << ' ' << s[1][1] << ' ' << s[1][2] << ' ' << s[1][3] << ' ' << endl;
		assert(s[0][0] <= UINT8_MAX - s[1][0]);
		assert(s[0][1] <= UINT8_MAX - s[1][1]);
		assert(s[0][2] <= UINT8_MAX - s[1][2]);
		assert(s[0][3] <= UINT8_MAX - s[1][3]);
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
	    state.clear();
	    sort(next.begin(), next.end());
	    next.erase(unique(next.begin(), next.end()), next.end());
	    clog << ' ' << ins - next.size() << ' ' << next.size() << ' ' << next.size()*(1.0*sizeof(next[0])/1024/1024)<< endl;
	    auto minmaxg = 0;
	    for (auto &s: next) {
		auto t = s;
		// pessimistic scenario: we produce same amount of obsidian every day
		// and build new geode robot once we collected enough obsidian and ore
		for (unsigned nday = day + 1; nday <= maxday; nday++) {
		    t[0][3] += t[1][3];
		    if (t[0][2] >= costs[3][2]  && t[0][0] >= costs[3][0]) {
		    	t[0][2] -= costs[3][2];
		    	t[0][0] -= costs[3][0];
		    	t[1][3]++;
		    }
		    t[0][2] += t[1][2];
		    //t[1][2]++;
		    t[0][0] += t[1][0];
		    //t[1][0]++;
		}
		minmaxg = max<unsigned>(minmaxg, t[0][3]);
	    }
	    auto end = next.begin();
	    for (auto &s: next) {
		auto t = s;
		// (overly) optimistic scenario: we build new obsidian and ore robot every day
		// and (impossibly) at the same time build new geode robot once we collected obsidian
		for (unsigned nday = day + 1; nday <= maxday; nday++) {
		    t[0][3] += t[1][3];
		    if (t[0][2] >= costs[3][2] && t[0][0] >= costs[3][0]) {
			t[0][2] -= costs[3][2];
			t[0][0] -= costs[3][0];
			t[1][3]++;
		    }
		    t[0][2] += t[1][2];
		    t[1][2]++;
		    t[0][0] += t[1][0];
		    t[1][0]++;
		}
		if (t[0][3] >= minmaxg)
		    *end++ = s;
	    }
	    //clog << next.end() - end << endl;
	    next.erase(end, next.end());
	    state.swap(next);
	}
	unsigned maxg = 0;
	for (auto &s: state)
	    maxg = max<unsigned>(maxg, s[0][3]);
	clog << blueprint << ' ' << maxg << endl;
	ret *= maxg;
    }
    cout << ret << endl;
    return 0;
}
