#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    unordered_set<uint64_t> src;
    unordered_set<uint64_t> dst;
    {
	cin >> s; // "seeds:"
	//clog << s << endl;
	assert(s.back() == ':');
	assert(s == "seeds:");
	while(cin.peek() != '\n') {
	    uint64_t i;
	    cin >> i;
	    src.insert(i);
	}
	auto c = cin.get();
	assert(c == '\n');
    }
    vector<tuple<uint64_t, uint64_t, uint64_t>> m;
    while(getline(cin, s)) {
	assert(s.empty());
	getline(cin, s);
	assert(s.back() == ':');
	clog << "map " << s << endl;
	uint64_t d, s, l;
	m.clear();
	while(cin.peek() != '\n' && cin.peek() != EOF) {
	    cin >> d >> s >> l;
	    assert(cin.get() == '\n');
	    m.emplace_back(s, l, d);
	    clog << s << '/' << l << '>' << d << endl; 
	}
	sort(m.begin(), m.end());
	dst.clear();
	for (auto s: src) {
	    auto lb = upper_bound(m.begin(), m.end(), s, [](auto k, const auto &a) {
		    return k < get<0>(a) + get<1>(a);
		    });
	    uint64_t d = s;
	    if (lb != m.end() && s >= get<0>(*lb)) {
		clog << '!' << get<0>(*lb) << ' ' << get<1>(*lb) << ' ' << get<2>(*lb) << endl;
		d = get<2>(*lb) + s - get<0>(*lb);
	    }
	    dst.insert(d);
	    clog << s << '>' << d << endl;
	}
	cout << endl;
	swap(src, dst);
    }
    cout << *min_element(src.cbegin(), src.cend()) << endl;
    return 0;
}
