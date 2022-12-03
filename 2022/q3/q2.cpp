#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	string s;
	int ret = 0;
	uint64_t bss = ~0ull;
	unsigned cnt = 0;
	while(cin >>s) {
	    auto n = s.size();
	    uint64_t bs = 0;
	    for (unsigned i = 0; i < n; i++) {
		if ((bs & 1ull<<(s[i] - 64)))
		    continue;
		bs |= 1ull<<(s[i] - 64);
	    }
	    bss &= bs;
	    if (++cnt == 3) {
		//clog << bss << endl;
		assert (bss != 0);
		assert((bss & (bss - 1)) == 0);
		unsigned i = __builtin_ctzll(bss);
		i += 64;
		//clog << (char)i << endl;
		if (i >= 'a' && i <= 'z')
		    ret += (i - 'a') + 1;
		else if (i >= 'A' && i <= 'Z')
		    ret += (i - 'A') + 27;
		cnt = 0;
		bss = ~0ull;
	    }
	}
	cout << ret << endl;
	return 0;
}
