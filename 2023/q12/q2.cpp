#include <bits/stdc++.h>
using namespace std;
static uint64_t dfs(string_view s, const vector<unsigned> &lens,
	unsigned spos, unsigned lpos, unsigned rem, vector<vector<uint64_t>> &memo) {
    if (spos == s.length())
	return lpos == lens.size() && rem == 0;
    if (s[spos] == '#' || (s[spos] == '?' && rem)) {
	if (rem == 0) {
	    if (lpos == lens.size())
		return 0;
	    rem = lens[lpos++];
	}
	if (rem > 1)
	    return dfs(s, lens, spos + 1, lpos, rem - 1, memo);
	assert(rem == 1);
	if (spos + 1 == s.length())
	    return lpos == lens.size();
	if (s[spos + 1] == '#')
	    return 0;
	return dfs(s, lens, spos + 2, lpos, 0, memo);
    }
    if (s[spos] == '.') {
	if (rem)
	    return 0;
	return dfs(s, lens, spos + 1, lpos, 0, memo);
    }
    assert(s[spos] == '?');
    assert(rem == 0);
    uint64_t res = 0;
    // assume spos is .
    res += dfs(s, lens, spos + 1, lpos, rem, memo);
    if (lpos < lens.size()) { // assume spos is # 
	if (memo[spos].empty())
	    memo[spos].resize(lens.size() + 1, UINT64_MAX);
	if (memo[spos][lpos] != UINT64_MAX)
	    return memo[spos][lpos];
	res += dfs(s, lens, spos, lpos + 1, lens[lpos], memo);
	memo[spos][lpos] = res;
    }
    return res;
}
int main() {
    string s;
    //vector<string> grid;
    vector<unsigned> lens;
    uint64_t res = 0;
    vector<vector<uint64_t>> memo;
    while(cin >> s) {
	lens.clear();
	memo.clear();
	//grid.emplace_back(s);
	while(cin.get() != '\n') {
	    unsigned v;
	    cin >> v;
	    lens.push_back(v);
	}
	unsigned slen = s.length();
	unsigned llen = lens.size();
	s.resize(slen*5 + 4, ' ');
	lens.resize(llen*5);
	for (unsigned c = 1, lpos = 0, spos = 0; c < 5; ++c) {
	    lpos += llen;
	    spos += slen;
	    s[spos++] = '?';
	    copy(s.begin(), s.begin() + slen, s.begin() + spos);
	    copy(lens.begin(), lens.begin() + llen, lens.begin() + lpos);
	}
	clog << s << ' ';
	for (auto l: lens) clog << ',' << l;
	clog << endl;
	memo.resize(s.size());
	auto comb = dfs(s, lens, 0, 0, 0, memo);
	clog << comb << endl;
	res += comb;
    }
    cout << res << endl;
    return 0;
}
