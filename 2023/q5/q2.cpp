#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    vector<pair<uint64_t,uint64_t>> src, dst;
    string prevset;
    {
	cin >> s; // "seeds:"
	//clog << s << endl;
	assert(s.back() == ':');
	assert(s == "seeds:");
	prevset = s;
	prevset.pop_back();
	prevset.pop_back();
	while(cin.peek() != '\n') {
	    uint64_t a, b;
	    cin >> a >> b;
	    src.emplace_back(a, b);
	}
	auto c = cin.get();
	assert(c == '\n');
    }
    sort(src.begin(), src.end());
    { // verify disjoint
	uint64_t prev = 0;
	for (auto [s, l]: dst) {
	    assert(l);
	    assert(prev <= s);
	    prev = s + l;
	}
    }
    vector<tuple<uint64_t, uint64_t, uint64_t>> m;
    while(getline(cin, s)) {
	assert(s.empty());
	getline(cin, s);
	assert(s.back() == ':');
	{
	    auto space = s.find(' ');
	    assert(s.substr(space) == " map:");
	    auto dash = s.find('-');
	    assert(s.substr(0, dash) == prevset);
	    assert(s.substr(dash, 4) == "-to-");
	    clog << prevset << " -> ";
	    prevset = s.substr(dash + 4, space - (dash + 4));
	    clog << prevset << endl;
	}
	uint64_t d, s, l;
	m.clear();
	while(cin.peek() != '\n' && cin.peek() != char_traits<char>::eof()) {
	    cin >> d >> s >> l;
	    assert(cin.get() == '\n');
	    m.emplace_back(s, l, d);
	    //clog << s << '/' << l << '>' << d << endl; 
	}
	sort(m.begin(), m.end());
	dst.clear();
	for (auto [s, l]: src) {
	    while(l) {
		auto ub = upper_bound(m.begin(), m.end(), s, [](auto k, const auto &a) {
			return k < get<0>(a) + get<1>(a);
			});
		if (ub == m.end() || get<0>(*ub) > s + l) {
		    dst.emplace_back(s, l);
		    break;
		}
		auto [ms,ml,ds] = *ub;
		//clog << s << ':' << s + l << '!' << get<0>(*lb) << ' ' << get<0>(*lb) + get<1>(*lb) << ' ' << get<2>(*lb) << endl;
		if (ms >= s) {
		    //d = get<2>(*lb) + s - get<0>(*lb);
		    if (ms > s) // directly map
			dst.emplace_back(s, ms - s);
		    auto se = min(s + l, ms + ml);
		    dst.emplace_back(ds, se - ms);
		    l = (s + l) - se;
		    s = se;
		} else {
		    auto se = min(ms + ml, s + l);
		    if (se != s)
			dst.emplace_back(ds + s - ms, se - s);
		    l = (s + l) - se;
		    s = se;
		}
		//clog << s << '>' << d << endl;
	    }
	}
	sort(dst.begin(), dst.end());
	src.clear();
	for (auto [s, l]: dst) {
	    assert(src.empty() || src.back().first + src.back().second <= s);
	    assert(l);
	    if (l == 0) continue;
	    if (!src.empty() && src.back().first + src.back().second == s)
		(clog << "merge\n"),
		src.back().second += l;
	    else
		src.emplace_back(s, l);
	}
	//for (auto [s, l]: src) clog << s << ':' << s + l << endl; clog << endl;
    }
    assert(prevset == "location");
    cout << src.front().first << endl;
    return 0;
}
