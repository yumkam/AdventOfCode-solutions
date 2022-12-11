#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	enum class eop { square, add, mul };
	struct monkey {
	    deque<int64_t> items;
	    size_t qsize;
	    eop	op;
	    int arg;
	    int test;
	    int branch[2];
	    int64_t stat;
	};
	vector<monkey> monkeys;
	string s;
	int i;
	char c;
	while(cin >> s >> s) {
	    auto i = stoi(s);
	    getline(cin, s);
	    if (monkeys.size() <= i)
		monkeys.resize(i + 1);
	    getline(cin, s);
	    //clog << s << endl;
	    auto pos = s.find(':');
	    for (;;) {
		int j = stoi(s.substr(pos + 2));
		monkeys[i].items.push_back(j);
		auto k = s.find(',', pos + 2);
		if (k == string::npos)
		    break;
		pos = k;
	    }
	    getline(cin, s);
	    pos = s.find('*');
	    if (pos == string::npos) {
		pos = s.find('+');
		monkeys[i].arg = stoi(s.substr(pos + 2));
		monkeys[i].op = eop::add;
	    } else if (s[pos + 2] == 'o') {
		monkeys[i].op = eop::square;
	    } else {
		monkeys[i].op = eop::mul;
		monkeys[i].arg = stoi(s.substr(pos + 2));
	    }
	    getline(cin, s);
	    pos = s.find('y');
	    monkeys[i].test = stoi(s.substr(pos + 2));
	    getline(cin, s);
	    pos = s.find('y');
	    monkeys[i].branch[1] = stoi(s.substr(pos + 2));
	    getline(cin, s);
	    pos = s.find('y');
	    monkeys[i].branch[0] = stoi(s.substr(pos + 2));
	}
	int64_t lcm = 1;
	for (auto &m: monkeys) {
	    lcm *= m.test/gcd(lcm, m.test);
	}
	for (unsigned t = 0; t < 10000; t++) {
	    for (auto &m: monkeys) {
		m.qsize = m.items.size();
		m.stat += m.qsize;
		//clog << m.qsize << endl;
		while(m.qsize--) {
		    auto item = m.items.front();
		    m.items.pop_front();
		    auto val = item;
		    switch(m.op) {
			case eop::square: val *= val; break;
			case eop::add: val += m.arg; break;
			case eop::mul: val *= m.arg; break;
		    }
		    val %= lcm;
		    //clog << item << ' ' << val << ' ' << (m.branch[(val % m.test) == 0]) << endl;
		    monkeys[m.branch[(val % m.test) == 0]].items.push_back(val);
		}
	    }
	}
	#if 0
	sort(monkeys.begin(), monkeys.end(), [](const auto &a, const auto &b) {
		return a.stat > b.stat;
		});
	clog << monkeys[0].stat << ' ' << monkeys[1].stat << endl;
	cout << monkeys[0].stat*monkeys[1].stat << endl;
	#else
	auto cmp = [](const auto &a, const auto &b) {
	    return a.stat < b.stat;
	};
	make_heap(monkeys.begin(), monkeys.end(), cmp);
	pop_heap(monkeys.begin(), monkeys.end(), cmp);
	cout << monkeys.front().stat*monkeys.back().stat << endl;
	#endif
	return 0;
}
