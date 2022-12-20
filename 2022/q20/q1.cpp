#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    int i;
    list<int> a;
    while(cin >> i)
	a.push_back(i);
    const int n = a.size();
    typedef decltype(a)::iterator iterator;
    vector<iterator> ap(n);
    iota(ap.begin(), ap.end(), a.begin());
    list<int> tmp;
    for (auto v: ap) {
	auto t = *v;
	//t %= n;
	//clog << t << endl;
	if (t == 0)
	    continue;
	auto newpos = v;
	if (t > 0) {
	    t %= n - 1;
	    if (t == 0)
		t = n - 1;
	    if (++newpos == a.end())
		newpos = a.begin();
	    while(t-- > 0) {
		if (++newpos == a.end())
		    newpos = a.begin();
	    }
	} else {
	    t %= n - 1;
	    assert(t); // NOT TESTED YET
	    if (t == 0)
		t = -(n - 1);
	    while(t++ < 0) {
		if (newpos == a.begin())
			newpos = a.end();
		--newpos;
	    }
	}
	//a.splice(newpos, a, v);
	a.splice(newpos, a, v);
	//for (auto x: a) clog << x << ' '; clog << endl;
    }
	for (auto x: a) clog << x << ' '; clog << endl;
    int ret = 0;
    vector<int> r(a.begin(), a.end());
    auto z = find(r.begin(), r.end(), 0) - r.begin();
    for (int t = 1000; t <= 3000; t += 1000) {
	clog << r[(z + t) % n] << endl;
	ret += r[(z + t) % n];
    }
    cout << ret << endl;
    return 0;
}
