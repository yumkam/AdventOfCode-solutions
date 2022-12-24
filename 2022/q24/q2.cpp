#include <bits/stdc++.h>
using namespace std;
const array<pair<int,int>, 5> movement {
    make_pair(-1,0), // north
    make_pair(+1,0), // south
    make_pair(0,-1), // west
    make_pair(0,+1), // east
    make_pair(0, 0), // stay
}; // {dy,dx}
const char dirs[] = "^v<>";
enum Dir {
    north,south,west,east,stay
};
struct elf {
    pair<int,int> pos; // y, x
    enum Dir prop;
    elf(int x, int y):pos{x, y}, prop{stay} {}
};
int main(int ac, const char *av[]) {
    string s;
    vector<string> map;
    while(getline(cin, s) && !s.empty())
	map.push_back(s);
    const unsigned m = map.size() - 2;
    const unsigned n = map[0].length() - 2;
    const unsigned nstate = n*m/gcd(n, m); // states repeat itself after this number of minutes
    vector<vector<bool>> border(m + 2, vector<bool>(n + 2));
    {
	for (unsigned i = 0; i <= m + 1; i++) {
	    border[i][0] = true;
	    border[i][n + 1] = true;
	}
	for (unsigned j = 0; j <= n + 1; j++) {
	    border[0][j] = true;
	    border[m + 1][j] = true;
	}
	border[0][1] = false;
	border[m + 1][n] = false;
    }
    vector<vector<vector<bool>>> states(nstate, border);
    for (unsigned i = 1; i <= m; i++) {
	for (unsigned j = 1; j <= n; j++) {
	    Dir dir;
	    switch(map[i][j]) {
		case '>': dir = east; break;
		case '<': dir = west; break;
		case '^': dir = north; break;
		case 'v': dir = south; break;
		default: continue;
	    }
	    unsigned ii = i, jj = j;
	    for (unsigned st = 0; st < nstate; st++) {
		states[st][ii][jj] = true;
		ii += movement[dir].first;
		jj += movement[dir].second;
		if (ii == 0) ii = m; else if (ii > m) ii = 1;
		else if (jj == 0) jj = n; else if (jj > n) jj = 1;
	    }
	}
    }
    for (unsigned st = 0; st < nstate; st++) {
	for (unsigned i = 0; i <= m + 1; i++) {
	    for (unsigned j = 0; j <= n + 1; j++)
		clog << states[st][i][j];
	    clog << endl;
	}
	clog << endl;
    }
    typedef tuple<unsigned,uint8_t,uint8_t> qitem;
    auto cmp = [](const auto a, const auto b) {
	return get<0>(a) > get<0>(b);
    };
    // A*; heuristic = day + distance(dest, cur)
#define DIST(A, B) ((A) >= (B) ? (A) - (B) : (B) - (A))
    auto astar = [&](unsigned day, unsigned src_i, unsigned src_j, unsigned dest_i, unsigned dest_j, int delta) {
	priority_queue<qitem,vector<qitem>,decltype(cmp)> q(cmp);
	vector<vector<vector<bool>>> visited(nstate, vector<vector<bool>>(m + 2, vector<bool>(n + 2)));
	visited[day % nstate][src_i][src_j] = true;
	q.emplace(DIST(dest_i, src_i) + 1 + DIST(dest_j, src_j) + 1 + day, src_i, src_j);
	while(!q.empty()) {
	    auto [cost, i, j] = q.top();
	    q.pop();
	    // recover day
	    auto day = cost - ((DIST(dest_i, i) + 1) + (DIST(dest_j, j) + 1));
	    clog << (int)i << ' ' << (int)j << ' ' << day << ' ' << cost << endl;
	    if (i == dest_i && j == dest_j) {
		clog << day << '/' << q.size() << endl;
		return day;
	    }
	    auto st = day % nstate;
	    auto nextst = st + 1; if (nextst == nstate) nextst = 0;
#define ENQ(I, J, DELTA) do { \
	if (!states[nextst][I][J] && !visited[nextst][I][J]) { \
	    visited[nextst][I][J] = true; \
	    q.emplace(cost + 1 + DELTA, I, J); \
	} \
    } while(0)
	    ENQ(i, j, 0);
	    if (i != m + 1)
		ENQ(i + 1, j, -delta);
	    if (j != n + 1)
		ENQ(i, j + 1, -delta);
	    if (i)
		ENQ(i - 1, j, +delta);
	    if (j)
		ENQ(i, j - 1, +delta);
	}
	return 0u;
    };
    int first = astar(0,  0, 1,  m + 1, n,  +1);
    int second = astar(first, m + 1, n,  0, 1,  -1);
    int third = astar(second, 0, 1,  m + 1, n,  +1);
    cout << third << endl;
    return 0;
}
