// Copyright (2023) Yuriy M. Kaminskiy <yumkam+from-git@gmail.com>
// You are free to use under either LGPGv2.1+ or BSD-3-Clause license
#include <bits/stdc++.h>
//using namespace std;
using nodeid_type = unsigned;
static constexpr auto undefined = std::numeric_limits<nodeid_type>::max();
static constexpr auto loop = std::numeric_limits<nodeid_type>::max() - 1; // loop without Z-nodes
static void dfs(nodeid_type src, unsigned pc, auto &trans, const auto &g, const std::string_view inst) {
    auto &cur = trans[src][pc];
    if (cur.first != undefined)
        return;
    if (cur.first == loop)
        return;
    if (g[src].first) {
        cur = std::pair { src, 0u };
        return;
    }
    auto next = g[src].second[inst[pc++]];
    if (pc == inst.size()) pc = 0;
    cur.first = loop;
    dfs(next, pc, trans, g, inst);
    cur = trans[next][pc];
    ++cur.second;
}
int main() {
    std::string inst;
    std::cin >> inst;
    for(auto &i: inst) i = i =='L' ? 0 : 1;
    { auto c = std::cin.get(); assert(c == '\n'); }
    { auto c = std::cin.get(); assert(c == '\n'); }
    std::string s;
    std::unordered_map<std::string, nodeid_type> u;
    std::vector<nodeid_type> nodes;
    std::vector<std::pair<int,std::array<nodeid_type,2>>> g;
    std::vector<std::string> names;
#define DEBUG 0
#define VERBOSE 1
    auto getid = [&u,&g,&names](const auto &name) {
        auto id =  u.emplace(name, u.size());
        if (id.second) {
            g.emplace_back(name[2] == 'Z', std::array<nodeid_type, 2> {~0u, ~0u});
            names.emplace_back(name);
        }
        return id.first->second;
    };
    while(std::getline(std::cin, s)) {
        assert(s.length() == 16);
        // 0123456789012345
        // XXX = (YYY, ZZZ)
        auto a = s.substr(0, 3);
        auto l = s.substr(7, 3);
        auto r = s.substr(12, 3);
        auto aid = getid(a);
        auto lid = getid(l);
        auto rid = getid(r);
        g[aid].second[0] = lid;
        g[aid].second[1] = rid;
        //cout << a << '=' << aid.first->second << ' ' << l << ' ' << r << endl;
        if (a[2] == 'A')
            nodes.push_back(aid);
    }
    const auto ninst = inst.size();
#if VERBOSE
    // [node][pc] -> {next Z node, steps} (next pc = pc + steps)
    std::clog << "dfs..." << std::flush;
#endif
    // O(n*m) time, O(n*m) space
    std::vector<std::vector<std::pair<nodeid_type, unsigned>>> trans(g.size(), std::vector<std::pair<nodeid_type, unsigned>>(ninst, std::pair{undefined, undefined}));
    // if we start at `node` and index `pc, pcmod = pc % ninst`, how many steps till next Z, and on which node we will end up?
    for (nodeid_type src = 0; src < g.size(); ++src) {
#if DEBUG
	std::clog << names[src];
#endif
        for (unsigned srcpc = 0; srcpc < ninst; ++srcpc) {
            dfs(src, srcpc, trans, g, inst);
#if DEBUG
            if (trans[src][srcpc].first == loop)
                std::clog << " N/A";
            else
                std::clog << ' ' << names[trans[src][srcpc].first] << '/' << trans[src][srcpc].second << '%' << (trans[src][srcpc].second % ninst);
#endif
        }
#if DEBUG
	std::clog << std::endl;
#endif
    }
#if VERBOSE
    std::clog << "done" << std::endl;
    std::clog << "glift..." <<std::flush;
#endif
    // O(n*m*nbit) time, O(n*m*nbit) space
    constexpr unsigned nbit = 64;
    std::vector<std::vector<std::array<nodeid_type, nbit>>> glift(g.size(), std::vector<std::array<nodeid_type, nbit>>(ninst));
    // glift[node][pcmod][i]
    // if we start at `node` and index pc, pc % ninst = pcmod, what node we will land after 2**i steps?
    for (nodeid_type src = 0; src < g.size(); ++src) {
        for (unsigned srcpc = 0; srcpc < ninst; ++srcpc) {
            glift[src][srcpc][0] = g[src].second[inst[srcpc]];
        }
    }
    for (uint64_t bit = 1, mask = 1; bit < nbit; ++bit, mask <<= 1) {
        for (nodeid_type src = 0; src < g.size(); ++src) {
            for (unsigned srcpc = 0; srcpc < ninst; ++srcpc) {
                auto a = glift[src][srcpc][bit - 1];
                glift[src][srcpc][bit] = glift[a][(srcpc + mask) % ninst][bit - 1];
            }
        }
    }
#if VERBOSE
    std::clog << "done" << std::endl;
    for (auto node: nodes) std::clog << ' ' << names[node] << '/' << node;
    std::clog << std::endl;
#endif
    std::array<unsigned, nbit> maskmod;
    for (unsigned i = 0; i < maskmod.size(); ++i)
        maskmod[i] = (1ull<<i) % ninst;
    std::clog.imbue(std::locale("en_US.UTF-8"));
    constexpr uint64_t range = 1ull<<34;
    const auto nthread = std::max<unsigned>(std::thread::hardware_concurrency(), 1u);
    auto res = std::numeric_limits<uint64_t>::max();
    std::mutex lock;
    std::deque<std::thread> pool;
    for (uint64_t start = nthread*range; start > 0; ) {
        start -= range;
        pool.emplace_back([start, &maskmod = std::as_const(maskmod),
                ninst, &nodes = std::as_const(nodes), &names = std::as_const(names),
                &glift = std::as_const(glift), &trans = std::as_const(trans),
                nthread, range, &lock, &res]() {
	    std::vector<std::pair<nodeid_type, uint64_t>> cnodes;
#if VERBOSE
            {
		std::unique_lock l(lock);
		std::clog << "started thread @" << start << std::endl;
            }
#endif
            unsigned ctr = 0;
            for (auto st = start;; st += nthread*range) {
                {
		    std::unique_lock l(lock);
                    if (st >= res)
                        return;
                }
                const auto endst = st + range;
                cnodes.clear();
#if DEBUG
		std::clog << st << " to " << endst << std::endl;
#endif
                uint64_t maxpc = st;
                if (st) {
                    for (auto node: nodes)
                        cnodes.emplace_back(node, 0);
                } else {
                    for (auto node: nodes) {
                        auto [next, s] = trans[node][0];
                        maxpc = std::max(maxpc, (uint64_t)s);
                        cnodes.emplace_back(next, st);
                    }
                } 
                for (;;) {
                    if ((++ctr & 0xfffff) == 0) {
			std::unique_lock l(lock);
                        if (maxpc >= res) // early exit
                            return;
#if VERBOSE
			std::clog << '\r' << maxpc << ' ';
                        for (auto [node, pc]: cnodes) {
			    std::clog << names[node] << ':' << maxpc - pc << ' ';
                        }
			std::clog << std::flush;
#endif
                    }
                    auto oldmax = maxpc;
                    for (unsigned i = 0; i < cnodes.size(); ++i) {
                        auto [node, pc] = cnodes[i];
                        if (pc == maxpc)
                            continue;
			// fast-forward to maxpc (O(log dist))
                        auto skip = maxpc - pc;
                        unsigned pcmod = pc % ninst;
                        while(skip) {
                            auto tz = std::countr_zero(skip);
                            auto mask = 1ull<<tz;
                            auto bit = tz;
                            skip ^= mask;
                            node = glift[node][pcmod][bit];
                            pc += mask;
                            pcmod += maskmod[bit];
                            if (pcmod >= ninst) pcmod -= ninst;
                        }
			// then move to next Z (O(1))
			std::tie(node, skip) = trans[node][pcmod];
                        pc += skip;
                        cnodes[i] = std::make_pair(node, pc);
                        maxpc = std::max(maxpc, pc);
                    }
                    if (oldmax == maxpc) {
			std::unique_lock l(lock);
                        res = std::min(res, oldmax);
                        return;
                    }
                    if (maxpc >= endst)
                        break;
                }
            }
        });
    }
    for (auto &th: pool) {
        th.join();
    }
#if DEBUG
    for (unsigned i = 0; i < nodes.size(); ++i) {
        auto node = nodes[i];
        uint64_t pc = 0;
        auto skip = res - pc;
        unsigned pcmod = pc % ninst;
        while(skip) {
            auto tz = std::countr_zero(skip);
            auto mask = 1ull<<tz;
            auto bit = tz;
            skip ^= mask;
            node = glift[node][pcmod][bit];
            pc += mask;
            pcmod += maskmod[bit];
            if (pcmod >= ninst) pcmod -= ninst;
        }
	std::cout << names[node] << std::endl;
    }
#endif
    std::cout << res << std::endl;
    return 0;
}
