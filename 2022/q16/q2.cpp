#include <bits/stdc++.h>
using namespace std;
template <class T>
    struct any_hash {
        size_t operator () (const T &c) const {
            static const hash<string_view> sv_hash;
            return sv_hash(string_view((const char *)(&c), sizeof(c)));
        }
    };
unordered_map<tuple<unsigned,unsigned,unsigned,unsigned,uint32_t>, unsigned, any_hash<tuple<unsigned,unsigned,unsigned,unsigned,uint32_t>>> memo;
static unsigned dfs(unsigned day1, unsigned day2, unsigned src1, unsigned src2, unsigned release, uint32_t visited,
	const vector<unsigned> &unopened,
	const vector<vector<unsigned>> &dists,
	const vector<unsigned> &rates) {
    unsigned max_release = release;
    if (day1 >= 30 && day2 >= 30)
	return release;
#if 0
    auto j = memo.emplace(make_tuple(min(day1,30u),min(day2,30u),src1,src2,visited), 0);
    if (!j.second)
	return j.first->second;
#endif
    for (unsigned dest = 0; dest < unopened.size(); dest ++) {
	const uint32_t mask = 1u<<dest;
	if ((visited & mask) == 0) {
	    auto v = unopened[dest];
	    if (day1 <= day2) {
		auto nextday = day1 + dists[src1][v] + 1;
		if (nextday < 30)
		    max_release = max(max_release,
			    dfs(nextday, day2, v, src2, release + rates[v]*(30 - nextday), (visited ^ mask),
				unopened, dists, rates));
	    } else {
		auto nextday = day2 + dists[src2][v] + 1;
		if (nextday < 30)
		    max_release = max(max_release,
			    dfs(day1, nextday, src1, v, release + rates[v]*(30 - nextday), (visited ^ mask),
				unopened, dists, rates));
	    }
	}
    }
    return //j.first->second = 
	max_release;
}
int main(int ac, const char *av[]) {
    //if (ac > 1 && av[1][0])
    //	maxs = atoi(av[1]);
    string s;
    array<unsigned, 26*26> ids;
    ids.fill(26*26);
    auto nid = 0u;
    vector<vector<unsigned>> adj;
    vector<unsigned> unopened;
    vector<unsigned> rates;
    vector<unsigned> rid;
    while(getline(cin, s) && s.length()) {
	auto pos = s.find(' ');
	auto id = (s[pos + 1] - 'A')*26 + (s[pos + 2] - 'A');
	clog << s.substr(pos, 3) << ' ' << id;
	if (ids[id] == 26*26) {
	    rid.push_back(id);
	    ids[id] = nid++;
	    adj.emplace_back();
	    rates.emplace_back(0);
	}
	id = ids[id];
	clog << ' ' << id;
	pos = s.find('=', pos + 3);
	auto rate = stoi(s.substr(pos + 1));
	if (rate)
	    unopened.push_back(id);
	rates[id] = rate;
	clog << '@' << rate;
	pos = s.find(' ', pos + 1);
        pos += sizeof(" tunnels lead to valve") - 1;
	if (s[pos] == 's') ++ pos;
	while(pos < s.length()) {
	    auto did = (s[pos + 1] - 'A')*26 + (s[pos + 2] - 'A');
	    clog << ' ' << s.substr(pos, 3) << ' ' << did;
	    pos += sizeof(" AA,") - 1;
	    if (ids[did] == 26*26) {
		ids[did] = nid++;
		adj.emplace_back();
		rates.emplace_back(0);
		rid.push_back(did);
	    }
	    did = ids[did];
	    clog << '/' << did;
	    adj[id].push_back(did);
	}
	clog << endl;
    }
    clog << nid << endl;
    // find minimum distance between each pair of valves
    vector<vector<unsigned>> dists(nid, vector<unsigned>(nid, UINT_MAX));
    queue<unsigned> q;
    // this can be done much faster, but who cares? good enough;
    for (unsigned i = 0; i < nid; i++) {
	q.emplace(i);
	unsigned dist = 0;
	dists[i][i] = 0;
	clog << i;
	for (;;) {
	    ++dist;
	    auto l = q.size();
	    if (l == 0)
		break;
	    while(l--) {
		auto u = q.front();
		q.pop();
		for (auto v: adj[u]) {
		    if (dists[i][v] == UINT_MAX) {
			dists[i][v] = dist;
			q.emplace(v);
		    }
		}
	    }
	}
    }
    sort(unopened.begin(), unopened.end(), [&rates](const auto a, const auto b) {
	    return rates[a] > rates[b];
	    });
    {
	unsigned j = 0;
	for (unsigned i = 0; i < unopened.size(); i++) {
	    if (dists[ids[0]][unopened[i]] != UINT_MAX && dists[ids[0]][unopened[i]] < 30)
		unopened[j++] = unopened[i];
	}
	unopened.resize(j);
    }
    for (auto &d: dists) { for(auto x: d) clog << x << ' '; clog << endl; }
    cout << dfs(4, 4, ids[0], ids[0], 0u, 0u, unopened, dists, rates) << endl;
    return 0;
}
