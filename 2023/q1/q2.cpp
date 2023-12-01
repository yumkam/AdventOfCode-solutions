#include <bits/stdc++.h>
using namespace std;
template<class ValueType, char minc = 'a', char maxc = 'z', typename SizeType = unsigned>
class Trie {
    static constexpr SizeType nil = 0;
    struct TrieNode {
	SizeType idx = 0;
	array<SizeType, 26> children {};
    };
    vector<ValueType> vals;
    vector<TrieNode> t;
    public:
    Trie():t(1) {}
    bool insert(string_view s, ValueType &&val) {
	auto node = 0;
	for (auto c: s) {
	    c -= minc;
	    auto &next = t[node].children[c];
	    if (next != nil)
		node = next;
	    else {
		node = next = t.size();
		t.emplace_back();
	    }
	}
	if (auto &idx = t[node].idx; idx == 0) {
	    vals.push_back(val);
	    idx = vals.size();
	    return true;
	}
	return false;
    }
    SizeType lookup(string_view s, ValueType &val, SizeType node = 0) {
	for (auto i = s.cbegin(), e = s.cend(); i != e; ) {
	    auto c = *i++;
	    if (c < minc || c > maxc)
		return 0;
	    c -= minc;
	    auto next = t[node].children[c];
	    if (next == nil)
		return 0;
	    node = next;
	    if (auto idx = t[node].idx; idx) {
		val = vals[idx - 1];
		return node;
	    }
	}
	return 0;
    }
};

int main(int ac, const char *av[]) {
    string s;
    int32_t res = 0;
    Trie<int> t;
    //t.insert("zero", 0);
    t.insert("one", 1);
    t.insert("two", 2);
    t.insert("three", 3);
    t.insert("four", 4);
    t.insert("five", 5);
    t.insert("six", 6);
    t.insert("seven", 7);
    t.insert("eight", 8);
    t.insert("nine", 9);
    while(cin >> s) {
	int first = -1, last = -1;
	auto sv = string_view(s);
	for (unsigned i = 0; i < sv.length(); ++i) {
	    int c ;
	    if (isdigit(c = sv[i]) ? c -= '0' : t.lookup(sv.substr(i), c)) {
		if (first == -1)
		    first = c;
		last = c;
	    }
	}
	//clog << sv << ' ' << first << ' ' << last << endl;
	assert(first >= 0 && last >= 0);
	res += first*10 + last;
    }
    cout << res << endl;
}
