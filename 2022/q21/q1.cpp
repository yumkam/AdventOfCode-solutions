#include <bits/stdc++.h>
using namespace std;
struct monkey {
    string name;
    int64_t number;
    char op;
    pair<string,unsigned> deps[2];
    vector<unsigned> rdeps;
    unsigned ndeps;
};
int main(int ac, const char *av[]) {
    int i;
    string s;
    vector<monkey> monkeys;
    unordered_map<string, unsigned> u;
    // gdbq: gptj * rdcl                                                                                          //     0123456789abc
    vector<unsigned> q;

    while(getline(cin, s) && !s.empty()) {
	auto pos = s.find(':');
	auto id = monkeys.size();
	auto &m = monkeys.emplace_back();
	m.name = s.substr(0, pos);
	u.try_emplace(m.name, id);
	clog << m.name << endl;
	if (isdigit(s[pos + 2])) {
	    m.op = 0;
	    m.number = stoi(s.substr(pos + 2));
	    q.push_back(id);
	    m.ndeps = 0;
	} else {
	    m.ndeps = 2;
	    m.deps[0].first = s.substr(pos + 2, 4);
	    m.op = s[pos + 7];
	    m.deps[1].first = s.substr(pos + 9, 4);
	}
    }
    for (unsigned id = 0; id < monkeys.size(); id++) {
	auto &m = monkeys[id];
	if (m.ndeps)
	    for (auto &d: m.deps) {
		d.second = u[d.first];
		monkeys[d.second].rdeps.push_back(id);
	    }
    }
    for (unsigned e = 0; e < q.size(); e++) {
	auto &m = monkeys[q[e]];
	switch (m.op) {
	    case '+': m.number = monkeys[m.deps[0].second].number + monkeys[m.deps[1].second].number; break;
	    case '-': m.number = monkeys[m.deps[0].second].number - monkeys[m.deps[1].second].number; break;
	    case '*': m.number = monkeys[m.deps[0].second].number * monkeys[m.deps[1].second].number; break;
	    case '/': assert(0 == monkeys[m.deps[0].second].number % monkeys[m.deps[1].second].number);
		      m.number = monkeys[m.deps[0].second].number / monkeys[m.deps[1].second].number; break;
	}
	clog << m.name << '=' << m.number << endl;
	for (auto r: m.rdeps)
	    if (0 == --monkeys[r].ndeps)
		q.push_back(r);
    }
    cout << monkeys[u["root"]].number << endl;
    return 0;
}
