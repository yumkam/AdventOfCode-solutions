#include <bits/stdc++.h>
using namespace std;
struct point {
    unsigned x, y, z;
};
int main() {
    string s;
    vector<array<point, 2>> bricks;
    point minv {UINT_MAX, UINT_MAX, UINT_MAX}, maxv {0u, 0u, 0u};
#define DEBUG 0
#if DEBUG
#define debug(...) __VA_ARGS__
#else
#define debug(...)
#endif
    {
	array<point, 2> p;
	char c;
	while(cin >> p[0].x) {
	    cin >> c >> p[0].y >> c >> p[0].z >> c >> p[1].x >> c >> p[1].y >> c >> p[1].z;
	    assert(p[0].x <= p[1].x);
	    assert(p[0].y <= p[1].y);
	    assert(p[0].z <= p[1].z);
	    minv.x = min(minv.x, p[0].x); maxv.x = max(maxv.x, p[1].x);
	    minv.y = min(minv.y, p[0].y); maxv.y = max(maxv.y, p[1].y);
	    minv.z = min(minv.z, p[0].z); maxv.z = max(maxv.z, p[1].z);
	    bricks.push_back(p);
	}
    }
    auto cmpz = [](const auto &a, const auto &b) { return a[0].z < b[0].z; };
    sort(bricks.begin(), bricks.end(), cmpz);
    const unsigned m = maxv.y - minv.y + 1;
    const unsigned n = maxv.x - minv.x + 1;
    const auto mn = m*n;
    vector<unsigned> maxz(mn, 1);
    for (auto &brick: bricks) {
	unsigned mz = 0;
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		mz = max(maxz[y*n+x], mz);
	assert(brick[0].z >= mz);
	brick[1].z -= brick[0].z - mz;
	brick[0].z = mz;
	mz = brick[1].z + 1;
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		maxz[y*n+x] = mz;
    }
    sort(bricks.begin(), bricks.end(), cmpz);
    unsigned zz = *max_element(maxz.begin(), maxz.end());
#if DEBUG
    for (auto &brick: bricks)
	clog 
	    << brick[0].x <<','<<brick[0].y<<','<<brick[0].z << '~'
	    << brick[1].x <<','<<brick[1].y<<','<<brick[1].z << '\n';
#endif
    vector<unsigned> vol(m*n*(zz + 1), UINT_MAX);
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		for (unsigned z = brick[0].z; z <= brick[1].z; ++z) {
#if DEBUG
		    if(vol[(z*m+y)*n+x] != UINT_MAX)
			clog << x << ',' << y << ',' << z << " collide " << i << ' ' << vol[(z*m+y)*n+x] << endl;
#endif
		    assert(vol[(z*m+y)*n+x] == UINT_MAX);
		    vol[(z*m+y)*n+x] = i;
		}
    }
#if DEBUG > 1
    for (unsigned z = 0; z <= zz; ++z) {
	for (unsigned x = 0; x < n; ++x) {
	    for (unsigned y = 0; y < m; ++y) 
		if (vol[(z*m+y)*n+x] == UINT_MAX)
		    clog << "    N";
		else
		    clog << setw(5) << vol[(z*m+y)*n+x];
	    clog << endl;
	}
	clog << endl;
    }
#endif
    vector<set<unsigned>> supported_by(bricks.size());
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		if (auto below = vol[((brick[0].z - 1)*m+y)*n+x]; below != UINT_MAX)
		    supported_by[i].insert(below);
    }
#if DEBUG
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	clog << i << '/'
	    << brick[0].x <<','<<brick[0].y<<','<<brick[0].z << '~'
	    << brick[1].x <<','<<brick[1].y<<','<<brick[1].z << ':';
	for (auto s: supported_by[i]) clog << ' ' << s;
	clog << endl;
    }
#endif
    assert(is_sorted_until(bricks.begin(), bricks.end(), cmpz) == bricks.end());
    vector<set<unsigned>> trigger_fall(bricks.size());
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		if (auto above = vol[((brick[1].z + 1)*m+y)*n+x]; above != UINT_MAX)
		    if (supported_by[above].size() == 1)
			trigger_fall[i].insert(above);
    }
    uint64_t ret = 0;
    for (unsigned i = 0; i < bricks.size(); ++i) {
	//auto &brick = bricks[i];
	set<unsigned> falling;
	falling.insert(i);
	bool ok = false;
	debug(clog << "trying " << i << endl);
	do {
	    ok = false;
	    vector<unsigned> fl (falling.begin(), falling.end());
	    for (auto f: fl) {
		auto &brick = bricks[f];
		for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
		    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
			if (auto above = vol[((brick[1].z + 1)*m+y)*n+x]; above != UINT_MAX) {
			    auto sc = 0;
			    for (auto s: supported_by[above])
				sc += (falling.count(s)) == 0;
			    if (sc == 0) {
				if (falling.insert(above).second) {
				    debug(clog << " added " << above << endl);
				    ok = true;
				}
			    }
			}
	    }
	} while(ok);
	ret += falling.size() - 1;
    }
    cout << ret << endl;
    return 0;
}
