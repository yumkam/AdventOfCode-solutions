#include <bits/stdc++.h>
using namespace std;
// right, down, left, up
const array<pair<int,int>, 4> movement { make_pair(0,+1), make_pair(+1,0), make_pair(0,-1), make_pair(-1,0) }; // {dy,dx}
const char dirs[] = ">v<^";
#if 0
const int sidemap[3 + 2][4 + 2] = {
    { 0,  0, 0,-2, 0,  0 },

    { 0, -1,-3, 1,-6,  0 },
    {-6,  2, 3, 4,-6,  0 },
    { 0, -5,-5, 5, 6, -1 },

    { 0,  0, 0,-2,-2,  0 }
};
#else
const int sidemap[4 + 2][3 + 2] = {
    { 0,  0,-6,-6,  0 },

    { 0, -4, 1, 2, -5 },
    { 0, -3, 3,-2,  0 },
    {-1,  4, 5,-2,  0 },
    {-1,  6,-6, 0,  0 },

    { 0, -2, 0, 0,  0 }
};
#endif
namespace Dir {
    enum { right, down, left, up };
};
int main(int ac, const char *av[]) {
    int i;
    string s;
    vector<string> map;
    while(getline(cin, s) && !s.empty())
	map.push_back(s);
    getline(cin, s);
    vector<vector<array<int,4> > > cache(map.size());
    int dir = Dir::right;
    //int x = 0, y = 0;
    //while(map[y][x] != '.') x++;
    s += 'X';
    int val = 0;
#if 0
    int side = map.size()/3;
    int x = side*2;
#else
    int side = map.size()/4;
    int x = side;
#endif
    int y = 0;
    int cube = 1;
    assert(map[y][x] == '.');
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
	    map[y][x] = dirs[dir];
	    auto ny = y;
	    auto nx = x;
	    auto ndir = dir;
	    auto ncube = cube;
	    {
		ny += movement[dir].first;
		nx += movement[dir].second;
		ncube = sidemap[(ny + side)/side][(nx + side)/side];
#if 0
		if (ncube > 0) {
		    // nothing
		} else if (cube == 1 && ncube == -2) { // transite to 2nd cube
		    assert(dir == Dir::up);
		    ncube = -ncube;
		    ny = side;
		    nx = 3*side - x - 1;
		    ndir = Dir::down;
		} else if (cube == 1 && ncube == -3) {
		    assert(dir == Dir::left);
		    ncube = -ncube;
		    ny = side;
		    nx = side + y;
		    ndir = Dir::down;
		} else if (cube == 1 && ncube == -6) {
		    assert(dir == Dir::right);
		    ncube = -ncube;
		    ny = 3*side - y - 1;
		    nx = x + side;
		    ndir = Dir::left;
		} else if (cube == 4 && ncube == -6) {
		    assert(dir == Dir::right);
		    ncube = -ncube;
		    ny = 2*side;
		    nx = (2 + 3)*side - y - 1;
		    ndir = Dir::down;
		} else if (cube == 6 && ncube == -6) {
		    assert(dir == Dir::up);
		    ncube = 4;
		    nx = y + side;
		    ny = x - 2*side;
		} else if (cube == 6 && ncube == -1) {
		    assert(dir == Dir::right);
		    ncube = -ncube;
		    ny = 3*side - y - 1;
		    nx = x - side;
		    ndir = Dir::left;
		} else if (cube == 6 && ncube == -2) {
		    assert(dir == Dir::down);
		    ncube = -ncube;
		    nx = 0;
		    ny = (4 + 1)*side - x - 1;
		    ndir = Dir::right;
		} else if (cube == 5 && ncube == -2) {
		    assert(dir == Dir::down);
		    ncube = -ncube;
		    ny = y - side;
		    nx = 3*side - x - 1;
		    ndir = Dir::up;
		} else if (cube == 5 && ncube == -5) {
		    assert(dir == Dir::left);
		    ncube = 3;
		    ny = 2*side - 1;
		    nx = (3 + 1)*side - y - 1;
		    ndir = Dir::up;
		} else if (cube == 3 && ncube == -5) {
		    assert(dir == Dir::down);
		    ncube = -ncube;
		    nx = 2*side;
		    ny = (2 + 2)*side - x - 1;
		    ndir = Dir::right;
		} else if (cube == 2 && ncube == -5) {
		    assert(dir == Dir::down);
		    ncube = -ncube;
		    ny = y + side;
		    nx = (1 + 2)*side - x - 1;
		    ndir = Dir::up;
		} else if (cube == 2 && ncube == -6) {
		    assert(dir == Dir::left);
		    ncube = -ncube;
		    ny = 3*side - 1;
		    nx = (2 + 3)*side - y - 1;
		    ndir = Dir::up;
		} else if (cube == 2 && ncube == -1) {
		    assert(dir == Dir::up);
		    ncube = -ncube;
		    ny = y - side;
		    nx = (1 + 2)*side - x - 1;
		    ndir = Dir::down;
		} else if (cube == 3 && ncube == -3) {
		    assert(dir == Dir::up);
		    ncube = 1;
		    nx = 2*side;
		    ny = x - side;
		    ndir = Dir::right;
		} else
		    assert(0);
#else
		if (ncube > 0) {
		    // nothing
		} else if (cube == 1 && ncube == -6) {
		    // up 1 to left 6
		    assert(dir == Dir::up);
		    ncube = -ncube;
		    nx = 0;
		    ny = (-1+3)*side + x;
		    ndir = Dir::right;
		} else if (cube == 1 && ncube == -4) {
		    // left 1 to left 4
		    assert(dir == Dir::left);
		    ncube = -ncube;
		    nx = 0;
		    ny = (1+2)*side - y - 1;
		    ndir = Dir::right;
		} else if (cube == 2 && ncube == -6) {
		    // up 2 to down 6
		    assert(dir == Dir::up);
		    ncube = -ncube;
		    ny = 4*side - 1;
		    nx = x + (-2 + 0)*side;
		    ndir = Dir::up;
		} else if (cube == 2 && ncube == -5) {
		    // right 2 to right 5
		    assert(dir == Dir::right);
		    ncube = -ncube;
		    nx = 2*side - 1;
		    ny = (1 + 2)*side - y - 1;
		    ndir = Dir::left;
		} else if (cube == 2 && ncube == -2) {
		    // bottom 2 to right 3
		    assert(dir == Dir::down);
		    ncube = 3;
		    nx = 2*side - 1;
		    ny = x + (-2 + 1)*side;
		    ndir = Dir::left;
		} else if (cube == 3 && ncube == -3) {
		    // left 3 to up 4
		    assert(dir == Dir::left);
		    ncube = 4;
		    ny = 2*side;
		    nx = y + (-1 + 0)*side;
		    ndir = Dir::down;
		} else if (cube == 3 && ncube == -2) {
		    // right 3 to down 2
		    assert(dir == Dir::right);
		    ncube = -ncube;
		    ny = 1*side - 1;
		    nx = y + (-1 + 2)*side;
		    ndir = Dir::up;
		} else if (cube == 5 && ncube == -2) {
		    // right 5 to right 2
		    assert(dir == Dir::right);
		    ncube = -ncube;
		    nx = 3*side - 1;
		    ny = (3 + 0)*side - y - 1;
		    ndir = Dir::left;
		} else if (cube == 5 && ncube == -6) {
		    // down 5 to right 6
		    assert(dir == Dir::down);
		    ncube = -ncube;
		    nx = 1*side - 1;
		    ny = x + (-1+3)*side;
		    ndir = Dir::left;
		} else if (cube == 6 && ncube == -6) {
		    // right 6 to down 5
		    assert(dir == Dir::right);
		    ncube = 5;
		    ny = 3*side - 1;
		    nx = y + (-3 + 1)*side;
		    ndir = Dir::up;
		} else if (cube == 6 && ncube == -1) {
		    // left 6 to up 1
		    assert(dir == Dir::left);
		    ncube = -ncube;
		    ny = 0;
		    nx = y + (-3 + 1)*side;
		    ndir = Dir::down;
		} else if (cube == 6 && ncube == -2) {
		    // down 6 to up 2
		    assert(dir == Dir::down);
		    ncube = -ncube;
		    ny = 0;
		    nx = x + (-0 + 2)*side;
		    ndir = Dir::down;
		} else if (cube == 4 && ncube == -1) {
		    // left 4 to left 1
		    assert(dir == Dir::left);
		    ncube = -ncube;
		    nx = x + side; // side
		    ny = (3 + 0)*side - y - 1;
		    ndir = Dir::right;
		} else if (cube == 4 && ncube == -3) {
		    // up 4 to left 3
		    assert(dir == Dir::up);
		    ncube = -ncube;
		    nx = side;
		    ny = x + (-0 + 1)*side;
		    ndir = Dir::right;
		} else {
	    	    //clog << x << ' ' << y << '>' << ny << ' ' << nx << ' ' << cube << '>' << ncube << ' ' << dir << '>' << ndir << ' ' << side << ' ' << map.size() << ' ' << map[ny].size() << endl << flush;
		    assert(0);
		}
#endif
	    }
	    //clog << x << ' ' << y << '>' << ny << ' ' << nx << ' ' << cube << '>' << ncube << ' ' << dir << '>' << ndir << ' ' << side << ' ' << map.size() << ' ' << map[ny].size() << endl << flush;
	    assert(ncube == sidemap[(ny + side)/side][(nx + side)/side]);
	    if (map[ny][nx] == '#')
		break;
	    y = ny; x = nx; dir = ndir; cube = ncube;
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
