#include <bits/stdc++.h>
using namespace std;
// right, down, left, up
const array<pair<int,int>, 4> movement { make_pair(0,+1), make_pair(+1,0), make_pair(0,-1), make_pair(-1,0) }; // {dy,dx}
const char dirs[] = ">v<^";
int main(int ac, const char *av[]) {
    int i;
    string s;
    vector<string> map;
    while(getline(cin, s) && !s.empty())
	map.push_back(s);
    getline(cin, s);
    vector<vector<array<int,4> > > cache(map.size());
    int dir = 0; // right
    int x = 0, y = 0;
    while(map[y][x] != '.') x++;
    s += 'X';
    int val = 0;
    size_t maxx = 0;
    for (auto &m: map) maxx = max(maxx, m.size());
    for (auto c: s) {
	if (isdigit(c)) {
	    val *= 10; val += c - '0';
	    continue;
	}
	// perform movement
	//clog << val << endl;
	while(val-- > 0) {
	    assert(map[y][x] != '#');
	    //map[y][x] = dirs[dir];
	    auto ny = y;
	    auto nx = x;
	    for (;;) {
		ny += movement[dir].first;
		nx += movement[dir].second;
		if (ny < 0)
		    ny = map.size();
		else if (ny >= (int)map.size())
		    ny = -1;
		else if (nx < 0)
		    nx = map[ny].size();
		else if (nx >= (int)maxx)
		    nx = -1;
		else if (nx >= (int)map[ny].size() || map[ny][nx] == ' ')
		    ;
		else
		    break;
	    }
	    if (map[ny][nx] == '#')
		break;
	    y = ny; x = nx;
	}
	val = 0;
	map[y][x] = c;
	switch(c) {
	    case 'X':
		break;
	    case 'R':
		dir = (dir + 1) & 3;
		break;
	    case 'L':
		dir = (dir - 1) & 3;
		break;
	    default:
		assert(0);
	}
    }
    for (auto &m: map) clog << m << endl;
    ++x; ++y;
    clog << x << ' ' << y << ' ' << dir << endl;
    cout << (1000*y + 4*x + dir) << endl;
    return 0;
}
