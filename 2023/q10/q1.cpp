#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    vector<string> grid;
    grid.emplace_back();
    while(cin >> s) {
	grid.emplace_back();
	grid.back() += '.';
	grid.back() += s;
	grid.back() += '.';
    }
    const auto n = grid.back().size();
    grid.emplace_back(string(n, '.'));
    grid[0].resize(n, '.');
    const auto m = grid.size();
    int si = m, sj = n;
    for (int i = 0; i < m; ++i)
	for (int j = 0; j < n; ++j) {
	    if (grid[i][j] == 'S') {
		si = i; sj = j;
		i = m;
		break;
	    }
	}
    assert(si != m);
    array<array<pair<int,int>, 2>, 256> dirs;
    dirs['|'] =  { pair { -1, 0 }, pair { +1, 0 } };
    dirs['-'] =  { pair { 0, -1 }, pair { 0, +1 } };
    dirs['L'] =  { pair { -1, 0 }, pair { 0, +1 } };
    dirs['J'] =  { pair { 0, -1 }, pair { -1, 0 } };
    dirs['7'] =  { pair { 0, -1 }, pair { +1, 0 } };
    dirs['F'] =  { pair { 0, +1 }, pair { +1, 0 } };
    constexpr unsigned inf = UINT_MAX - 1;
    vector<vector<unsigned>> dist(m, vector<unsigned>(n, inf));
    dist[si][sj] = 0;
    deque<pair<int, int>> q;
    //for (auto &row: grid) clog << row << endl;
    auto check = [&](int i, int j, int di, int dj) {
	auto &dir = dirs[grid[i + di][j + dj]];
	for (auto [rdi, rdj]: dir) {
	    if (i + di + rdi == i && j + dj + rdj == j)
		return true;
	}
	return false;
    };
    if (check(si, sj, +1, 0)) { q.emplace_back(si + 1, sj + 0); dist[si + 1][sj + 0] = 1; }
    if (check(si, sj, -1, 0)) { q.emplace_back(si - 1, sj + 0); dist[si - 1][sj + 0] = 1; }
    if (check(si, sj, 0, +1)) { q.emplace_back(si + 0, sj + 1); dist[si + 0][sj + 1] = 1; }
    if (check(si, sj, 0, -1)) { q.emplace_back(si + 0, sj - 1); dist[si + 0][sj - 1] = 1; }
    unsigned steps = 0;
    for (;;) {
	auto l = q.size();
	if (l == 0)
	    break;
	++steps;
	while(l--) {
	    auto [i, j] = q.front();
	    //clog << i << ',' << j << endl;
	    q.pop_front();
	    auto &dir = dirs[grid[i][j]];
	    for (auto [di, dj]: dir) {
		if (check(i, j, di, dj)) {
		    if (dist[i + di][j + dj] == inf) {
			q.emplace_back(i + di, j + dj); dist[i + di][j + dj] = steps + 1;
			continue;
		    }
		    if (dist[i + di][j + dj] >= steps) {
			cout << dist[i + di][j + dj] << endl;
			return 0;
		    }
		}
	    }
	}
    }
    return 1;
}
