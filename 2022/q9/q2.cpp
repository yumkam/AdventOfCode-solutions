#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	set<pair<int,int>> s;
	array<pair<int,int>, 10> r;
	r.fill(make_pair(0,0));
	char c;
	int steps;
	s.emplace(r.back().first, r.back().second);
	while(cin >> c >> steps) {
	    int dx = c == 'L' ? -1 : c == 'R' ? +1 : 0;
	    int dy = c == 'U' ? +1 : c == 'D' ? -1 : 0;
	    while(steps--) {
		r[0].first += dx;
		r[0].second += dy;
		for (unsigned i = 1; i < r.size(); i++) {
		    if (r[i-1].first - r[i].first > 1) {
			assert(r[i-1].first - r[i].first == 2);
			r[i].first = r[i-1].first - 1;
			/*pad*/if (r[i-1].second - r[i].second > 1) {
			    assert(r[i-1].second - r[i].second == 2);
			    r[i].second = r[i-1].second - 1;
			} else if (r[i].second - r[i-1].second > 1) {
			    assert(r[i].second - r[i-1].second == 2);
			    r[i].second = r[i-1].second + 1;
		    	} else {
			    r[i].second = r[i-1].second;
			}
		    } else if (r[i].first - r[i-1].first > 1) {
			assert(r[i].first - r[i-1].first == 2);
			r[i].first = r[i-1].first + 1;
			/*pad*/if (r[i-1].second - r[i].second > 1) {
			    assert(r[i-1].second - r[i].second == 2);
			    r[i].second = r[i-1].second - 1;
			} else if (r[i].second - r[i-1].second > 1) {
			    assert(r[i].second - r[i-1].second == 2);
			    r[i].second = r[i-1].second + 1;
		    	} else {
			    r[i].second = r[i-1].second;
			}
		    } else if (r[i-1].second - r[i].second > 1) {
			assert(r[i-1].second - r[i].second == 2);
			r[i].second = r[i-1].second - 1;
			/*pad*/if (r[i-1].first - r[i].first > 1) {
			    assert(r[i-1].first - r[i].first == 2);
			    r[i].first = r[i-1].first - 1;
			} else if (r[i].first - r[i-1].first > 1) {
			    assert(r[i].first - r[i-1].first == 2);
			    r[i].first = r[i-1].first + 1;
		    	} else {
			    r[i].first = r[i-1].first;
			}
		    } else if (r[i].second - r[i-1].second > 1) {
			assert(r[i].second - r[i-1].second == 2);
			r[i].second = r[i-1].second + 1;
			/*pad*/if (r[i-1].first - r[i].first > 1) {
			    assert(r[i-1].first - r[i].first == 2);
			    r[i].first = r[i-1].first - 1;
			} else if (r[i].first - r[i-1].first > 1) {
			    assert(r[i].first - r[i-1].first == 2);
			    r[i].first = r[i-1].first + 1;
		    	} else {
			    r[i].first = r[i-1].first;
			}
		    } else {
			break;
		    }
		}
		//for (auto x: r) clog << x.first << '/' << x.second << ' '; clog << endl;
		s.emplace(r.back().first, r.back().second);
	    }
	    //clog<<endl;
	}
	cout << s.size() << endl;
	return 0;
}
