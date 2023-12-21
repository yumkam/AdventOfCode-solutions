#include <bits/stdc++.h>
using namespace std;
struct node;
struct node {
    vector<tuple<string, node*, unsigned>> out;
    uint8_t bit = 0;
    uint8_t ninput = 0;
    char type = 0;
};
typedef uint32_t ulem;
static constexpr size_t ulb = sizeof(ulem)*8;
static constexpr ulem ulone = 1;
static constexpr ulem ulzero = 0;
static void dfs(node *v, unsigned &offset) {
    if (v->bit != 0xff)
	return;
    if (v->type == 0)
	return;
    uint32_t bits = v->type == '%' ? 1 : /*v->type == '&' ?*/ v->ninput;
    // flip-flop state is one bit (regardless of number of inputs)
    if  ((offset + bits - 1)/ulb != (offset / ulb))
	offset = (offset + ulb - 1) & ~(ulb - 1);
    v->bit = offset;
    offset += bits;
    for (auto &[name,ptr,idx]: v->out) {
	dfs(ptr, offset);
    }
}
int main() {
    unordered_map<string, node*> u;
    string s;
    for (;;) {
	auto ch = cin.peek();
	if (ch == '\n') {
	    cin.get();
	    continue;
	}
	if (ch == -1)
	    break;
	char type = 0;
	if (ch == '&' || ch == '%')
	    type = cin.get();
	cin >> s;
	//clog << s << '>' << endl;
	auto i = u.try_emplace(s).first;
	if (i->second == nullptr)
	    i->second = new node();
	i->second->type = type;
	cin >> s;
	for (;;) {
	    cin >> s;
	    bool last = s.back() != ',';
	    if (!last)
		s.pop_back();
	    //clog << '[' << s << ']' << endl;
	    auto j = u.try_emplace(s).first;
	    if (j->second == nullptr)
		j->second = new node();
	    i->second->out.emplace_back(s, nullptr, j->second->ninput++);
	    if (last)
		break;
	}
    }
    for (auto &[_, v]: u)
	for (auto &[name,ptr,idx]: v->out)
	    ptr = u.find(name)->second;
    auto broadcast = u.find(string("broadcaster"))->second;
    auto rx = u.find(string("rx"))->second;
    // we assumes:
    // graph can be split into independent parts;
    // each part connected to output via single conjuctor node;
    // each part states form a loop;
    // high output signal is generated once at final step of loop
    // each loop lengths are coprime
    assert(rx->ninput == 1);
    decltype(rx) lv = nullptr;
    for (auto &[name, v]: u)
	if (v->out.size() == 1 && get<1>(v->out[0]) == rx) {
	    assert(lv == nullptr);
	    clog << "final conjuctor: " << name << endl;
	    lv = v;
	}
    assert(lv);
    assert(lv->type == '&');
    deque<tuple<node *, uint8_t, uint8_t>> q;
    //array<uint32_t,2> cnt {};
    clog.imbue(locale("en_US.UTF-8"));
    vector<uint32_t> state;
    map<decltype(state), unsigned> memo;
    vector<uint64_t> looplen;
    for (auto &[srcname,srcptr,srcidx]: broadcast->out) {
	clog << "src = " << srcname << endl;
	for (auto [_, v]: u) // mark every state first bit as invalid
	    v->bit = 0xff;
	unsigned offset = 0;
	dfs(srcptr, offset); // reassign state bits
#if 0
	for (auto [name, v]: u) {
	    if (v->bit == 0xff)
		continue;
	    uint32_t bits = v->type == '%' ? 1 : /*v->type == '&' ?*/ v->ninput;
	    clog << name << '<' << (int)v->bit << '@' << bits << endl;
	}
#endif
	clog <<'='<<offset<< endl;
	state.clear();
	state.resize((offset + ulb - 1)/ulb, ~ulzero);
	memo.clear();
	vector<uint64_t> trigger;
	for (uint64_t step = 0;; ++step) {
	    if (auto j = memo.emplace(state, step); !j.second) {
		auto mu = j.first->second;
		auto lambda = step - j.first->second;
		clog << step << ' ' << lambda << ' ' << mu << endl;
		assert(mu == 1);
		assert(trigger.size() == 1);
		assert(trigger[0] == lambda - 1);
		for (auto l: looplen) // everything is coprime
		    assert(gcd(l, lambda) == 1);
		looplen.push_back(lambda);
		break;
	    }
	    if (!(step & 0xffffff)) 
		clog << '\r' << step << ' ' << flush;
	    q.emplace_back(srcptr, srcidx, 0);
	    while(!q.empty()) {
		//clog << '\r' << "len = " << q.size() << ' ' << flush;
		auto [v, iidx, value] = q.front();
		//++cnt[value];
		if (v == lv && value) {
		    trigger.push_back(step);
		    clog << step << '=' << (int)value << endl;
		}
		q.pop_front();
		//clog <<'T'<< v->type << (int)value<<endl;
		switch (v->type) {
		    case '%':
			if (value == 1)
			    continue;
			assert(v->bit < offset);
			value = !!(state[v->bit / ulb] & (ulone<<(v->bit % ulb)));
			state[v->bit / ulb] ^= ulone<<(v->bit % ulb);
			break;
		    case '&':
			{
			    uint8_t bit = v->bit + iidx;
			    //clog << '&' << (int)bit << ' ' << (int)v->bit << '/' << (int)v->ninput << ' ' << ((state[v->bit / ulb] >> (v->bit % ulb)) & ((ulone<<v->ninput) - 1)) << endl;
			    if (value)
				state[bit / ulb] &= ~(ulone<<(bit % ulb));
			    else
				state[bit / ulb] |= ulone<<(bit % ulb);
			    //clog << '&' << (int)v->bit << '/' << (int)v->ninput << ' ' << ((state[v->bit / ulb] >> (v->bit % ulb)) & ((ulone<<v->ninput) - 1)) << endl;
			    value = ((state[v->bit / ulb] >> (v->bit % ulb)) & ((ulone<<v->ninput) - 1)) != 0;
			    break;
			}
		}
		//clog << '>' << (int)value << endl;
		for (auto &[_,out,outidx]: v->out) {
		    //clog << _ << ' ' << outidx << endl;
		    q.emplace_back(out,outidx,value);
		}
	    }
	}
    }
    uint64_t res = 1;
    for (auto l: looplen) res *= l;
    cout << res << endl;
    return 0;
}
