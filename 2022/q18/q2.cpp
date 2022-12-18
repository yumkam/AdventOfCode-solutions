#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    unordered_set<uint32_t> u;
    int x, y, z;
    char c;
    vector<tuple<int8_t,int8_t,int8_t>> a;
    auto minx = INT_MAX;
    auto maxx = INT_MIN;
    auto miny = INT_MAX;
    auto maxy = INT_MIN;
    auto minz = INT_MAX;
    auto maxz = INT_MIN;
    while(cin >> x >> c >> y >> c >> z) {
	x++; y++; z++;
	minx = min(minx, x); maxx = max(maxx, x);
	miny = min(miny, y); maxy = max(maxy, y);
	minz = min(minz, z); maxz = max(maxz, z);
	assert(x > 0 && x < 256);
	assert(y > 0 && y < 256);
	assert(z > 0 && z < 256);
	//u.insert((x<<24)^(y<<16)^z);
	a.emplace_back(x, y, z);
    }
    clog << minx << ',' << maxx << ' ' << miny << ',' << maxy << ' ' << minz << ',' << maxz << endl;
    vector<vector<vector<bool>>> vis(maxx + 2, vector<vector<bool>>(maxy + 2, vector<bool>(maxz + 2)));
    vector<vector<vector<bool>>> air(maxx + 2, vector<vector<bool>>(maxy + 2, vector<bool>(maxz + 2)));
    for (auto [x, y, z]: a)
	vis[x][y][z] = true;
    deque<tuple<int8_t,int8_t,int8_t>> q;
    for (unsigned x = 0; x <= maxx + 1; x++)
	for (unsigned y = 0; y <= maxy + 1; y++) {
	    q.emplace_back(x, y, 0);
	    vis[x][y][0] = true;
	    air[x][y][0] = true;
	    q.emplace_back(x, y, maxz + 1);
	    vis[x][y][maxz + 1] = true;
	    air[x][y][maxz + 1] = true;
	}
    for (unsigned x = 0; x <= maxx + 1; x++)
	for (unsigned z = 0; z <= maxz + 1; z++) {
	    q.emplace_back(x, 0, z);
	    vis[x][0][z] = true;
	    air[x][0][z] = true;
	    q.emplace_back(x, maxy + 1, z);
	    vis[x][maxy + 1][z] = true;
	    air[x][maxy + 1][z] = true;
	}
    for (unsigned y = 0; y <= maxy + 1; y++)
	for (unsigned z = 0; z <= maxz + 1; z++) {
	    q.emplace_back(0, y, z);
	    vis[0][y][z] = true;
	    air[0][y][z] = true;
	    q.emplace_back(maxx + 1, y, z);
	    vis[maxx + 1][y][z] = true;
	    air[maxx + 1][y][z] = true;
	}
    while(!q.empty()) {
	auto [x, y, z] = q.front();
	q.pop_front();
	air[x][y][z] = true;
#define ENQ(CHECK, X, Y, Z) if (CHECK && !vis[X][Y][Z]) { vis[X][Y][Z] = true; q.emplace_back(X, Y, Z); }
	ENQ(x > 0, x - 1, y, z); ENQ(x + 1 <= maxx + 1, x + 1, y, z);
	ENQ(y > 0, x, y - 1, z); ENQ(y + 1 <= maxy + 1, x, y + 1, z);
	ENQ(z > 0, x, y, z - 1); ENQ(z + 1 <= maxz + 1, x, y, z + 1);
    }
    unsigned ret = 0;
    for (auto [x, y, z]: a) {
	ret += air[x - 1][y][z];
	ret += air[x + 1][y][z];
	ret += air[x][y - 1][z];
	ret += air[x][y + 1][z];
	ret += air[x][y][z - 1];
	ret += air[x][y][z + 1];
    }
    cout << ret << endl;
    return 0;
}
