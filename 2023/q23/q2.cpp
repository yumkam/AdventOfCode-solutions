#include <bits/stdc++.h>
using namespace std;
static void dfs(unsigned u, unsigned cost, const auto &adj, auto &onpath, auto &maxcost) {
    maxcost[u] = max(maxcost[u], cost);
    onpath[u] = true;
    for (auto [w, v]: adj[u]) {
	if (onpath[v]) continue;
	dfs(v, cost + 1 + w, adj, onpath, maxcost);
    }
    onpath[u] = false;
}
int main() {
    string s;
    vector<string> grid;
    while(cin >> s)
	grid.push_back(s);
    const unsigned m = grid.size();
    const unsigned n = grid[0].size();
    const unsigned mn = m*n;
    unsigned src = 0;
    assert(grid[0][0] != '.');
    for (unsigned j = 0; j < n; ++j)
	if (grid[0][j] == '.') {
	    assert(src == 0 /* at most one grass at top side */);
	    src = j;
	}
    assert(src != 0 /* there are grass at top side */);
    unsigned dst = 0;
    assert(dst != mn - n);
    for (unsigned j = 0; j < n; ++j)
	if (grid[m - 1][j] == '.') {
	    assert(dst == 0 /* at most one grass at bottom side */);
	    dst = mn - n + j;
	}
    assert(dst != 0 /* dst must be only grass on bottom side */);
    vector<vector<pair<unsigned, unsigned>>> adj(mn);
    for (unsigned i = 1; i < m; ++i) {
	auto left = '#';
	auto &row = grid[i];
	auto &up = grid[i - 1];
	for (unsigned j = 0; j < n; j++) {
	    auto k = i*n + j;
	    if (row[j] == '#') {
		left = '#';
		continue;
	    }
	    if (left != '#') { adj[k - 1].emplace_back(0, k); adj[k].emplace_back(0, k - 1); }
	    if (up[j] != '#') { adj[k - n].emplace_back(0, k); adj[k].emplace_back(0, k - n); }
	    left = '.';
	}
    }
    assert(adj[src].size() == 1);
    assert(adj[dst].size() == 1);
#if 1
    unsigned collapsed = 0;
    // simplify graph (collapse edges)
    for (unsigned k = 0; k < mn; ++k) {
	auto &a = adj[k];
	if (a.size() == 2) {
	    ++collapsed;
	    for (auto &[w, v]: adj[a[0].second])
		if (v == k) {
		    v = a[1].second;
		    w += a[1].first + 1;
		    break;
		}
	    for (auto &[w, v]: adj[a[1].second])
		if (v == k) {
		    v = a[0].second;
		    w += a[0].first + 1;
		    break;
		}
	    a.clear();
	}
    }
    unsigned erased = 0;
    // simplify graph: removed edges to self
    for (unsigned u = 0; u < mn; ++u) {
	auto &a = adj[u];
	erased -= a.size();
	a.erase(remove_if(a.begin(), a.end(), [u](auto &x) { return x.second == u; }), a.end());
	erased += a.size();
    }
    clog << "collapsed " << collapsed << " erased " << erased << endl;
#endif
#if 0
    for (unsigned i = 0; i < m; ++i) {
	for (unsigned j = 0; j < n; ++j) {
	    clog << grid[i][j] <<'@'<<setw(4)<< (i*n+j);
	    for (auto [w,v]: adj[i*n+j]) clog << '/' << w << ',' << v;
	    clog << ' ';
	}
	clog << '\n';
    }
#endif
    vector<unsigned> maxcost(mn, 0);
    vector<bool> onpath(mn);
    dfs(src, 1u, adj, onpath, maxcost);
    cout << maxcost[dst] - 1 << endl;
    return 0;
}
