#include "union-find3.hpp"
#include <bits/stdc++.h>
using namespace std;
using namespace union_find;
static void dfs(unsigned u, unsigned cost, const auto &adj, const auto &g, auto &onpath, auto &maxcost) {
    cost += g[u].size;
    maxcost[u] = max(maxcost[u], cost);
    onpath[u] = true;
    for (auto v: adj[u]) {
	if (onpath[v]) continue;
	dfs(v, cost + 1, adj, g, onpath, maxcost);
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
    vector<SizedVertex<>> g(m*n, SizedVertex<>(0, 0));
    unsigned src = 0;
#define DEBUG 0
    assert(grid[0][0] != '.');
    for (unsigned j = 0; j < n; ++j)
	if (grid[0][j] == '.') {
	    assert(src == 0);
	    g[0+j] = src = j;
	}
    assert(src != 0);
    g[0].size = 0;
    for (unsigned i = 1; i < m; ++i) {
	unsigned gij1 = 0;
	for (unsigned j = 0; j < n; ++j) {
	    auto k = i*n+j;
	    if (grid[i][j] != '.') {
		gij1 = 0;
	 	continue;
	    }
	    auto gi1j = g[k - n].parent; // (i-1)*n+j
	    auto gij = k;
	    if (gi1j && gij1)
		gij = union_by_size(g, gi1j, gij1);
	    else if (gi1j)
		gij = find_root(g, gi1j);
	    else if (gij1)
		gij = find_root(g, gij1);
	    else
		g[k].size = 0;
	    ++g[gij].size;
	    g[k].parent = gij1 = gij;
	}
    }
    for (unsigned k = 0; k < mn; ++k) // avoid special-case for handle <<
	if (g[k].parent == 0)
	    g[k].parent = k;
    src = find_root(g, src);
    unsigned dst = 0;
    assert(dst != mn - n);
    for (unsigned j = 0; j < n; ++j)
	if (grid[m - 1][j] == '.') {
	    assert(dst == 0);
	    dst = mn - n + j;
	}
    assert(dst != 0);
    dst = find_root(g, dst);
    vector<vector<unsigned>> adj(mn);
    for (unsigned i = 1; i < m - 1; ++i)
	for (unsigned j = 1; j < n - 1; ++j) {
	    auto k = i*n+j;
	    switch(grid[i][j]) {
		case '<':
		    adj[find_root(g, k + 1)].push_back(find_root(g, k - 1));
		    break;
		case '>':
		    adj[find_root(g, k - 1)].push_back(find_root(g, k + 1));
		    break;
		case 'v':
		    adj[find_root(g, k - n)].push_back(find_root(g, k + n));
		    break;
		case '^':
		    adj[find_root(g, k + n)].push_back(find_root(g, k - n));
		    break;
		default:
		    continue;
	    }
	    g[k].size = 1;
	}
#if DEBUG
    for (unsigned k = 0; k < mn; ++k)
	if (adj[k].size()) {
	    clog << k;
	    for (auto v: adj[k])
		clog << ' ' << v;
	    clog << endl;
	}
    for (unsigned i = 0; i < m; ++i) {
	for (unsigned j = 0; j < n; ++j) {
	    clog << grid[i][j] << 'p' << setw(4) << g[i*n+j].parent << 'S' << left << setw(4) << g[find_root(g, i*n+j)].size << ' ';
	}
	clog << '\n';
    }
    clog << "src = " << src << "\ndst = " << dst << endl;
#endif
    vector<unsigned> maxcost(mn, 0);
    vector<bool> onpath(mn);
    dfs(src, 0u, adj, g, onpath, maxcost);
    cout << maxcost[dst] - 1 << endl;
    return 0;
}
