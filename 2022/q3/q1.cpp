#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	string s;
	uint64_t bs = 0;
	int ret = 0;
	while(cin >>s) {
	    auto n = s.size();
	    assert(!(n & 1));
	    auto nhalf = n / 2;
	    uint64_t bs1 = 0;
	    for (unsigned i = 0; i < nhalf; i++)
		bs1 |= 1ull<<(s[i] - 64);
	    uint64_t bs2 = 0;
	    for (unsigned i = nhalf; i < n; i++)
		bs2 |= 1ull<<(s[i] - 64);
	    bs2 &= bs1;
	    if (bs2 & bs)
		clog << s << endl;
	    for (unsigned i = 64; bs2; bs2 >>= 1, ++i) {
		if (bs2 & 1) {
		    if (i >= 'a' && i <= 'z')
			ret += (i - 'a') + 1;
		    else if (i >= 'A' && i <= 'Z')
			ret += (i - 'A') + 27; 
		}
	    }
	}
	cout << ret << endl;
	return 0;
}
