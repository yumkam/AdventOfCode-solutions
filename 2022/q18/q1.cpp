#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    unordered_set<uint32_t> u;
    int x, y, z;
    char c;
    vector<tuple<int8_t,int8_t,int8_t>> a;
    while(cin >> x >> c >> y >> c >> z) {
	x++; y++; z++;
	assert(x > 0 && x < 256);
	assert(y > 0 && y < 256);
	assert(z > 0 && z < 256);
	u.insert((x<<24)^(y<<16)^z);
	a.emplace_back(x, y, z);
    }
    unsigned ret = 0;
    for (auto [x, y, z]: a) {
	ret += 1 - u.count(((x - 1) << 24) ^ ((y) << 16) ^ (z));
	ret += 1 - u.count(((x + 1) << 24) ^ ((y) << 16) ^ (z));
	ret += 1 - u.count(((x) << 24) ^ ((y - 1) << 16) ^ (z));
	ret += 1 - u.count(((x) << 24) ^ ((y + 1) << 16) ^ (z));
	ret += 1 - u.count(((x) << 24) ^ ((y) << 16) ^ (z - 1));
	ret += 1 - u.count(((x) << 24) ^ ((y) << 16) ^ (z + 1));
    }
    cout << ret << endl;
    return 0;
}
