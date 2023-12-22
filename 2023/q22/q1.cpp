#include <bits/stdc++.h>
using namespace std;
struct point {
    unsigned x, y, z;
};
int main() {
    string s;
    vector<array<point, 2>> bricks;
    point minv {UINT_MAX, UINT_MAX, UINT_MAX}, maxv {0u, 0u, 0u};
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
    sort(bricks.begin(), bricks.end(), [](const auto &a, const auto &b) { return a[0].z < b[0].z; });
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
    unsigned zz = *max_element(maxz.begin(), maxz.end());
    for (auto &brick: bricks)
	clog 
	    << brick[0].x <<','<<brick[0].y<<','<<brick[0].z << '~'
	    << brick[1].x <<','<<brick[1].y<<','<<brick[1].z << '\n';
    vector<unsigned> vol(m*n*(zz + 1), UINT_MAX);
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		for (unsigned z = brick[0].z; z <= brick[1].z; ++z) {
		    if(vol[(z*m+y)*n+x] != UINT_MAX)
			clog << x << ',' << y << ',' << z << " collide " << i << ' ' << vol[(z*m+y)*n+x] << endl;
		    vol[(z*m+y)*n+x] = i;
		}
    }
    for (unsigned z = 0; z <= zz; ++z) {
	for (unsigned x = 0; x < n; ++x) {
	    for (unsigned y = 0; y < m; ++y) 
		if (vol[(z*m+y)*n+x] == UINT_MAX)
		    clog << "  N";
		else
		    clog << setw(3) << vol[(z*m+y)*n+x];
	    clog << endl;
	}
	clog << endl;
    }
    vector<set<unsigned>> supported_by(bricks.size());
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		if (auto below = vol[((brick[0].z - 1)*m+y)*n+x]; below != UINT_MAX)
		    supported_by[i].insert(below);
    }
    unsigned ret = 0;
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	clog << i << '/'
	    << brick[0].x <<','<<brick[0].y<<','<<brick[0].z << '~'
	    << brick[1].x <<','<<brick[1].y<<','<<brick[1].z << ':';
	for (auto s: supported_by[i]) clog << ' ' << s;
	clog << endl;
    }
    for (unsigned i = 0; i < bricks.size(); ++i) {
	auto &brick = bricks[i];
	for (unsigned x = brick[0].x; x <= brick[1].x; ++x)
	    for (unsigned y = brick[0].y; y <= brick[1].y; ++y)
		if (auto above = vol[((brick[1].z + 1)*m+y)*n+x]; above != UINT_MAX)
		    if (supported_by[above].size() == 1)
			goto skip;
	++ret;
skip:;
    }
    cout << ret << endl;
    return 0;
}
