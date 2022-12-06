#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	array<size_t, 26> cnt;
	cnt.fill(0);
	static constexpr size_t wlen = 14;
	size_t mismatch = 0;
	array<char, wlen> w;
	size_t pos = 0, wpos = 0;
	for (; pos < wlen; pos++) {
	    auto c = cin.get();
	    //clog << (char)c;
	    c -= 'a';
	    w[pos] = c;
	    mismatch += cnt[c]++ == 1;
	}
	if (mismatch == 0) {
	    cout << pos + 1 << endl;
	    return 0;
	}
	for (;; ++pos, ++wpos) {
	    auto c = cin.get();
	    if (!(c >= 'a' && c <= 'z'))
		break;
	    //clog << (char)c;
	    c -= 'a';
	    if (wpos == wlen)
		wpos = 0;
	    if (--cnt[w[wpos]] == 1)
		mismatch--;
	    w[wpos] = c;
	    if (cnt[c]++ == 1)
		mismatch++;
	    if (mismatch == 0) {
		cout << pos + 1 << endl;
		return 0;
	    }
	}
	cout << endl;
	return 0;
}
