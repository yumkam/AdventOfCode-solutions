#include <bits/stdc++.h>
#include <locale.h>
using namespace std;
static void floodfill(vector<vector<uint8_t>> &grid, unsigned si, unsigned sj, uint8_t oldcolor, uint8_t newcolor) {
    deque<pair<unsigned, unsigned>> q;
    q.emplace_back(si, sj);
    grid[si][sj] = newcolor;
    unsigned m = grid.size();
    unsigned n = grid[0].size();
    while(!q.empty()) {
	auto [i, j] = q.back();
	q.pop_back();
#if 0
	auto li = max(i, 1u) - 1;
	auto lj = max(j, 1u) - 1;
	auto hi = min(i + 2, m);
	auto hj = min(j + 2, n);
	for (auto ti = li; ti < hi; ++ti)
	    for (auto tj = lj; tj < hj; ++tj)
		if (grid[ti][tj] == oldcolor) {
		    grid[ti][tj] = newcolor;
		    q.emplace_back(ti, tj);
		}
#else
#define ENQ(CHECK, I, J) if (CHECK && grid[I][J] == oldcolor) { grid[I][J] = newcolor; q.emplace_back(I, J); }
	ENQ(i > 0, i - 1, j);
	ENQ(j > 0, i, j - 1);
	ENQ(i + 1 < m, i + 1, j);
	ENQ(j + 1 < n, i, j + 1);
#endif
    }
}

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
    setlocale(LC_ALL, "");
    //wclog.imbue(locale("en_US.UTF-8"));
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
    array<string, 256> wc {}; 
    wc['S'] = "S";
    wc[' '] = " ";
    wc['|'] = "│"; //0x2502 │
    wc['-'] = "─"; //0x2500 ─
    wc['L'] = "└"; //0x2514 └ 
    wc['J'] = "┘"; //0x2518 ┘
    wc['7'] = "┐"; //0x2510 ┐
    wc['F'] = "┌"; //0x250c ┌
    array<array<array<uint8_t, 3>, 3>, 6> gmap = {{
        {{{{ 0, 1, 0 }},
	  {{ 0, 1, 0 }},
	  {{ 0, 1, 0 }}}},
	{{{{ 0, 0, 0 }},
	  {{ 1, 1, 1 }},
	  {{ 0, 0, 0 }}}},
	{{{{ 0, 1, 0 }},
	  {{ 0, 1, 1 }},
	  {{ 0, 0, 0 }}}},
	{{{{ 0, 1, 0 }},
	  {{ 1, 1, 0 }},
	  {{ 0, 0, 0 }}}},
	{{{{ 0, 0, 0 }},
	  {{ 1, 1, 0 }},
	  {{ 0, 1, 0 }}}},
	{{{{ 0, 0, 0 }},
	  {{ 0, 1, 1 }},
	  {{ 0, 1, 0 }}}},
    }};
    array<uint8_t, 256> gtr {};
    gtr['|'] = 1; //0x2502 │
    gtr['-'] = 2; //0x2500 ─
    gtr['L'] = 3; //0x2514 └ 
    gtr['J'] = 4; //0x2518 ┘
    gtr['7'] = 5; //0x2510 ┐
    gtr['F'] = 6; //0x250c ┌
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
    vector<vector<pair<int, int>>> from(m, vector<pair<int,int>>(n, make_pair(m, n)));
    if (check(si, sj, +1, 0)) { q.emplace_back(si + 1, sj + 0); dist[si + 1][sj + 0] = 1; from[si + 1][sj + 0] = make_pair(si, sj); }
    if (check(si, sj, -1, 0)) { q.emplace_back(si - 1, sj + 0); dist[si - 1][sj + 0] = 1; from[si - 1][sj + 0] = make_pair(si, sj); }
    if (check(si, sj, 0, +1)) { q.emplace_back(si + 0, sj + 1); dist[si + 0][sj + 1] = 1; from[si + 0][sj + 1] = make_pair(si, sj); }
    if (check(si, sj, 0, -1)) { q.emplace_back(si + 0, sj - 1); dist[si + 0][sj - 1] = 1; from[si + 0][sj - 1] = make_pair(si, sj); }
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
			from[i + di][j + dj] = make_pair(i, j);
			continue;
		    }
		    if (dist[i + di][j + dj] >= steps) {
			cout << dist[i + di][j + dj] << endl;
			vector<vector<bool>> visited(m, vector<bool>(n));
			for (auto ti = i, tj = j; ti != si || tj != sj; ) {
			    visited[ti][tj] = true;
			    tie(ti, tj) = from[ti][tj];
			}
			for (auto ti = i + di, tj = j + dj; ti != si || tj != sj; ) {
			    visited[ti][tj] = true;
			    tie(ti, tj) = from[ti][tj];
			}
			visited[si][sj] = true;
			unsigned res = 0;
			if(visited[si - 1][sj] && check(si, sj, -1, 0)) {
			    if (visited[si + 1][sj] && check(si, sj, +1, 0))
				grid[si][sj] = '|';
			    else if (visited[si][sj - 1] && check(si, sj, 0, -1))
				grid[si][sj] = 'J';
			    else if (visited[si][sj + 1] && check(si, sj, 0, +1))
				grid[si][sj] = 'L';
			    else
				assert(0);
			} else if (visited[si + 1][sj] && check(si, sj, +1, 0)) {
			    if (visited[si][sj - 1] && check(si, sj, 0, -1))
				grid[si][sj] = '7';
			    else if (visited[si][sj + 1] && check(si, sj, 0, +1))
				grid[si][sj] = 'F';
			    else
				assert(0);
			} else if (visited[si][sj - 1] && check(si, sj, 0, -1)) {
			    if (visited[si][sj + 1] && check(si, sj, 0, +1))
				grid[si][sj] = '-';
			    else
				assert(0);
			} else {
			    assert(0);
			}

			for (unsigned i = 0; i < m; ++i) {
			    bool eo = false;
			    for (unsigned j = 0; j < n; ++j) {
				clog << wc[visited[i][j] ? grid[i][j] : ' ']; 
			    }
			    clog << endl;
			}
			vector<vector<uint8_t>> xgrid(m*3, vector<uint8_t>(n*3));
			for (unsigned i = 0; i < m; ++i) {
			    for (unsigned j = 0; j < n; ++j) {
				if (!visited[i][j]) continue;
				auto xt = gtr[grid[i][j]];
				if (xt-- == 0) continue;
				for (unsigned ti = 0; ti < 3; ++ti)
				    for (unsigned tj = 0; tj < 3; ++tj) {
					xgrid[3*i + ti][3*j + tj] = gmap[xt][ti][tj];
				    }
			    }
			}
			floodfill(xgrid, 0, 0, 0, 2);
			for (unsigned i = 0; i < m; ++i) {
			    for (unsigned j = 0; j < n; ++j) {
				clog << (xgrid[3*i + 1][3*j + 1] == 0 ? '#' : '.');
				res += xgrid[3*i + 1][3*j + 1] == 0;
			    }
			    clog << endl;
			}
			for (unsigned i = 0; i < 3*m; ++i) {
			    for (unsigned j = 0; j < 3*n; ++j)
				clog << (xgrid[i][j] == 0 ? '*' : xgrid[i][j] == 1 ? '#' : ' ');
			    clog << endl;
			}
			cout << res << endl;
			return 0;
		    }
		}
	    }
	}
    }
    return 1;
}
