#include <bits/stdc++.h>
using namespace std;
const array<pair<int,int>, 5> movement {
    make_pair(-1,0), // north
    make_pair(+1,0), // south
    make_pair(0,-1), // west
    make_pair(0,+1), // east
    make_pair(0, 0), // stay
}; // {dy,dx}
const char dirs[] = ">v<^";
enum Dir {
    north,south,west,east,stay
};
struct elf {
    pair<int,int> pos; // y, x
    enum Dir prop;
    elf(int x, int y):pos{x, y}, prop{stay} {}
};
int main(int ac, const char *av[]) {
    string s;
    vector<string> map;
    while(getline(cin, s) && !s.empty())
	map.push_back(s);
    vector<elf> elves;
    for (unsigned y = 0; y < map.size(); y++)
	for (unsigned x = 0; x < map[y].size(); x++)
	    if (map[y][x] == '#')
		elves.emplace_back(y, x);
    auto hop = [](const auto p) -> size_t {
	return (static_cast<size_t>(p.first)<<32)^static_cast<size_t>(p.second);
    };
    unordered_set<pair<int,int>,decltype(hop)> pos(elves.size(), hop);
    unordered_map<pair<int,int>,unsigned,decltype(hop)> prop(elves.size(), hop);
    for (auto &e: elves) pos.emplace(e.pos);
    for (unsigned day = 0; ; day++) {
	prop.clear();
	for (auto &e: elves) {
	    e.prop = stay;
	    auto cnt = 0;
	    for (unsigned i = 0; i < 4; i++) {
		enum Dir dir = (Dir)((i + day) & 3);
		auto move = movement[dir];
		auto altmove = make_pair<int,int>(!move.first, !move.second);
		auto movecnt =
		    (pos.count(make_pair(e.pos.first + move.first, e.pos.second + move.second)) +
		    pos.count(make_pair(e.pos.first + move.first + altmove.first, e.pos.second + move.second + altmove.second)) +
		    pos.count(make_pair(e.pos.first + move.first - altmove.first, e.pos.second + move.second - altmove.second)));
		cnt += movecnt;
		if (e.prop == stay && movecnt == 0)
		    e.prop = dir;
	    }
	    if (cnt == 0)
		e.prop = stay;
	    if (e.prop != stay)
		prop[make_pair(e.pos.first + movement[e.prop].first, e.pos.second + movement[e.prop].second)]++;
	}
	unsigned movecount = 0;
	for (auto &e: elves) {
	    if (e.prop == stay)
		continue;
	    auto next = e.pos; next.first += movement[e.prop].first; next.second += movement[e.prop].second;
	    if (prop[next] > 1)
		continue;
	    pos.erase(e.pos);
	    pos.insert(next);
	    e.pos = next;
	    ++movecount;
	}
	if (movecount == 0) {
	    cout << day + 1 << endl;
	    break;
	}
    }
#if 1
	pair<int,int> minpos {INT_MAX,INT_MAX};
	pair<int,int> maxpos {INT_MIN,INT_MIN};
	for (auto &e: elves) {
	    minpos.first = min(minpos.first, e.pos.first);
	    minpos.second = min(minpos.second, e.pos.second);
	    maxpos.first = max(maxpos.first, e.pos.first);
	    maxpos.second = max(maxpos.second, e.pos.second);
	}
	for (int y = minpos.first; y <= maxpos.first; y++) {
	    for (int x = minpos.second; x <= maxpos.second; x++)
		clog << (pos.count(make_pair(y, x)) ? '#' : '.');
	    clog << endl;
	}
	clog << endl;
#endif
#if 0
    {
	pair<int,int> minpos {INT_MAX,INT_MAX};
	pair<int,int> maxpos {INT_MIN,INT_MIN};
	for (auto &e: elves) {
	    minpos.first = min(minpos.first, e.pos.first);
	    minpos.second = min(minpos.second, e.pos.second);
	    maxpos.first = max(maxpos.first, e.pos.first);
	    maxpos.second = max(maxpos.second, e.pos.second);
	}
	cout << (maxpos.second - minpos.second + 1)*(maxpos.first - minpos.first + 1) - elves.size() << endl;
    }
#endif

    return 0;
}
