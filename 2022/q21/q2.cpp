#include <bits/stdc++.h>
using namespace std;
template<typename Int>
struct rnum {
    Int num;
    Int den;
    rnum(Int num = 0, Int den = 1):num(num), den(den) {}
    void canonify() {
	assert(den != 0);
	if (den < 0) { den = -den; num = -num; }
	auto g = gcd(abs(num), den);
	num /= g;
	den /= g;
    }
    operator bool() const {
	return num != 0;
    }
    friend rnum operator - (rnum a) {
	rnum c(-a.num, a.den);
	//c.canonify();
	return c;
    }
    friend rnum operator + (rnum a, rnum b) {
	rnum c(a.num*b.den + b.num*a.den, a.den*b.den);
	c.canonify();
	return c;
    }
    friend rnum operator - (rnum a, rnum b) {
	rnum c(a.num*b.den - b.num*a.den, a.den*b.den);
	c.canonify();
	return c;
    }
    friend rnum operator * (rnum a, rnum b) {
	rnum c(a.num*b.num, a.den*b.den);
	c.canonify();
	return c;
    }
    friend rnum operator / (rnum a, rnum b) {
	rnum c(a.num*b.den, a.den*b.num);
	c.canonify();
	return c;
    }
    friend ostream &operator <<(ostream &os, rnum x) {
	if (x.den == 1)
	    return os << x.num;
	else
	    return os << '(' << x.num << '/' << x.den << ')';
    }
};
struct monkey {
    string name;
    // a*'humn'+b
    rnum<int64_t> coeff, number;
    char op;
    pair<string,unsigned> deps[2];
    vector<unsigned> rdeps;
    unsigned ndeps;
    bool hdep;
};
int main(int ac, const char *av[]) {
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
    monkeys[u["root"]].op = '-';
    monkeys[u["humn"]].hdep = true;
    monkeys[u["humn"]].coeff = 1;
    monkeys[u["humn"]].number = 0;
    // X*coeff + number
    for (unsigned e = 0; e < q.size(); e++) {
	auto &m = monkeys[q[e]];
	switch (m.op) {
	    case '+': // (a*X+b) + (c*X+d) = (a+c)*X + (b+d)
		m.coeff = monkeys[m.deps[0].second].coeff + monkeys[m.deps[1].second].coeff;
		m.number = monkeys[m.deps[0].second].number + monkeys[m.deps[1].second].number;
	       	break;
	    case '-': // (a*X+b) - (c*X+d) = (a-c)*X + (b-d)
		m.coeff = monkeys[m.deps[0].second].coeff - monkeys[m.deps[1].second].coeff;
		m.number = monkeys[m.deps[0].second].number - monkeys[m.deps[1].second].number;
		break;
	    case '*':
		// (a*X+b) * (c*X+d) = (a*c)*X^2 + (a*d + b*c)*X + (b*d)
		// monkeys ain't too smart: no X^2 or above: either c or a is 0
		assert(!(monkeys[m.deps[0].second].coeff && monkeys[m.deps[1].second].coeff));
		m.coeff = monkeys[m.deps[0].second].coeff*monkeys[m.deps[1].second].number + monkeys[m.deps[1].second].coeff*monkeys[m.deps[0].second].number;
		m.number = monkeys[m.deps[0].second].number * monkeys[m.deps[1].second].number;
		break;
	    case '/':
		// (a*X+b)/(0*X+d) = (a/d)*X + (b/d)
		// ... and no dividion by X either
		assert(!monkeys[m.deps[1].second].coeff);
		m.coeff = monkeys[m.deps[0].second].coeff / monkeys[m.deps[1].second].number;
		m.number = monkeys[m.deps[0].second].number / monkeys[m.deps[1].second].number;
	       	break;
	    default:
		// do nothing
		break;
	}
	if (m.hdep) { clog << '?' << monkeys[m.deps[0].second].hdep << m.op << monkeys[m.deps[1].second].hdep << ':'; }
	clog << m.name << '=' << m.coeff << "*X+" << m.number << endl;
	for (auto r: m.rdeps) {
	    monkeys[r].hdep = monkeys[r].hdep || m.hdep;
	    if (0 == --monkeys[r].ndeps)
		q.push_back(r);
	}
    }
    clog << monkeys[u["root"]].coeff << "*humn" << '+' << monkeys[u["root"]].number << " == 0" << endl;
    cout << (-monkeys[u["root"]].number) / monkeys[u["root"]].coeff << endl;
    return 0;
}
