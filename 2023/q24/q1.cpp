#include <bits/stdc++.h>
#include "int128.h"
using namespace std;
__int128 abs(__int128 x) {
    return x < 0 ? -x : x;
}
__int128 gcd(__int128 x, __int128 y) {
    if (y < x) swap(x, y);
    while(y != 0) {
	auto t = x % y;
	x = y;
	y = t;
    }
    return x;
}
int main() {
    __int128 x;
    struct dir {
	__int128 p, v;
    };
    vector<array<dir, 3>> dirs;
    while(cin >> x) {
	char c;
	__int128 y, z, vx, vy, vz;
	cin >> c >> y; assert(c == ',');
	cin >> c >> z; assert(c == ',');
	cin >> c >> vx; assert(c == '@');
	cin >> c >> vy; assert(c == ',');
	cin >> c >> vz; assert(c == ',');
	dirs.emplace_back(array<dir, 3> {{{x, vx}, {y, vy}, {z, vz}}});
    }
    __int128 minv = 200000000000000;
    __int128 maxv = 400000000000000;
    if (getenv("TEST1")) {
	minv = 7;
	maxv = 27;
    }
    unsigned res = 0;
    for (unsigned i = 0; i < dirs.size(); ++i) {
	auto x1 = dirs[i][0];
	auto y1 = dirs[i][1];
	for (unsigned j = 0; j < i; ++j) {
	    auto x2 = dirs[j][0];
	    auto y2 = dirs[j][1];
	    clog << x1.p <<','<<y1.p <<' ' << x2.p <<',' << y2.p << endl;
/*
solve([x1+vx1*t1=x2+vx2*t2,y1+vy1*t1=y2+vy2*t2],[t1,t2]);
           vx2 (y2 - y1) + vy2 (x1 - x2)
[[ t1 = + -------------------------------, 
                 vx2 vy1 - vx1 vy2
	  vx1 (y2 - y1) + vy1 (x1 - x2)
   t2 = + -------------------------------]]
		 vx2 vy1 - vx1 vy2

 */
	    __int128 t1m = x2.v*(y2.p - y1.p) + y2.v* (x1.p - x2.p);
	    __int128 t2m = x1.v*(y2.p - y1.p) + y1.v* (x1.p - x2.p);
	    __int128 td = x2.v*y1.v - x1.v*y2.v;
	    clog <<t1m << '/' << td << endl;
	    clog <<t2m << '/' << td << endl;
	    if (td < 0) { t1m = -t1m; t2m = -t2m; td = -td; }
	    if (td == 0)
		continue;
	    if (t1m < 0)
		continue;
	    if (t2m < 0)
		continue;
	    assert(td > 0);
	    auto g = gcd(abs(t1m), td);
	    clog << g << 'g' << gcd(abs(t2m), g) << endl;
	    //g = gcd(abs(t2m), td);
	    t1m /= g;
	    //t2m /= g;
	    td /= g;
	    if (x1.p*td + x1.v*t1m < minv*td) continue;
	    if (x1.p*td + x1.v*t1m > maxv*td) continue;
	    if (y1.p*td + y1.v*t1m < minv*td) continue;
	    if (y1.p*td + y1.v*t1m > maxv*td) continue;
	    clog << i << '+' << j << ' ' << x1.p*td + x1.v*t1m << '/' << td << ' ' << y1.p*td + y1.v*t1m << '/' << td << '@' << t1m << '/' << td << endl;
	    // x = x1.p + x1.v*t1m/td; x1.p*td + v*t1m/
#if 0
	    if ((y2.p-y1.p)*(x1.v-x2.v) == (x2.p-x1.p)*(y1.v-y2.v)) {
		clog << i << ' ' << j << " no collide\n";
		continue;
	    }
	    __int128 tm;
	    __int128 td;
	    if (x1.v != x2.v)
		tm = x2.p - x1.p, td = x1.v - x2.v;
	    else if (y1.v != y2.v)
		tm = y2.p - y1.p, td = y1.v - y2.v;
	    else
		assert(0);
	    if (td < 0) { tm = -tm; td = -td; }
	    if (tm < 0) {
		clog << i << ' ' << j << " negtime\n";
		continue;
	    }
	    auto g = gcd(abs(tm), abs(td));
	    tm /= g;
	    td /= g;
	    __int128 cx = x1.p*td + x1.v*tm;
	    __int128 cy = y1.p*td + y1.v*tm;
	    clog << cx << '|' << x2.p*td + x2.v*tm << endl;
	    clog << cy << '|' << y2.p*td + y2.v*tm << endl;
	    //assert(cx == x2.p*td + x2.v*tm);
	    //assert(cy == y2.p*td + y2.v*tm);
	    if (cx < minv*td) {
		clog <<'x'<< cx << '/' << td << '<' << minv << endl;
		continue;
	    }
	    if (cx > maxv*td) {
		clog <<'x'<< cx << '/' << td << '>' << minv << endl;
		continue;
	    }
	    if (cy < minv*td) {
		clog <<'y'<< cy << '/' << td << '<' << minv << endl;
		continue;
	    }
	    if (cy > maxv*td) {
		clog <<'y'<< cy << '/' << td << '>' << minv << endl;
		continue;
	    }
#endif
	    ++res;
	}
    }
    cout << res << endl;
    return 0;
}
