#include <bits/stdc++.h>
//#include <boost/pool/singleton_pool.hpp>
//struct node_pool { };
//using singleton_node_pool = boost::singleton_pool<node_pool, sizeof(PatriciaNode)>;

using namespace std;
int main(int ac, const char *av[]) {
    // robot type: [ore, clay, obsidan, geode]
    // resources: [ore, clay, obsidan]
    array<array<unsigned,3>,4> costs {{0}};
    string s;
    int i;
    char c;
    unsigned ret = 1;
    const unsigned maxday = 24;
    while(cin >> s >> i >> c) { // <Blueprint> $num <:>
	int blueprint = i;
	if (blueprint > 3) break;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >>  i >> s;
	costs[0][0] = i;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[1][0] = i;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[2][0] = i;
	// <and> $num <clay>
	cin >> s >> i >> s;
	costs[2][1] = i;
	// <Each> <XXX> <robot> <costs> $num <ore>
	cin >> s >> s >> s >> s >> i >> s;
	costs[3][0] = i;
	// <and> $num <obsidan>
	cin >> s >> i >> s;
	costs[3][2] = i;

	for (unsigned type = 0; type < 4; type++) {
	    for (auto c: costs[type])
		clog << c << ' ';
	    clog << endl;
	}
	// state: { collected: ore, clay, obsidan, geode; robots: ore, clay, obsidan, geode }
	vector<array<array<uint8_t,4>, 2>> state;
	auto vhash = [](auto &v) {
	    static const hash<string_view> sv_hash;
	    return sv_hash(string_view((const char *)(v.data()), v.size()*sizeof(v[0])));
	};

	unordered_set<array<array<uint8_t,4>, 2>, decltype(vhash)> next(1000, vhash);
	state.emplace_back();
	state.front()[1][0] = 1;
	for (unsigned day = 1; day <= maxday; day++) {
	    next.clear();
	    next.reserve(state.size()*4);
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
		next.insert(s);
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
			next.insert(t);
			ins++;
			//clog << '>'  << next.back()[0][0] << ' ' << next.back()[0][1] << ' ' << next.back()[0][2] << ' ' << next.back()[0][3] << '@'
			//    << next.back()[1][0] << ' ' << next.back()[1][1] << ' ' << next.back()[1][2] << ' ' << next.back()[1][3] << ' ' << endl;
		    }
		}
	    }
	    state.clear();
	    state.reserve(next.size());
	    state.assign(next.begin(), next.end());
	    clog << ' ' << ins - next.size() << ' ' << next.size() << endl;
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
