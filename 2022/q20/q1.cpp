#include <bits/stdc++.h>
using namespace std;
struct DLL {
    int val;
    DLL *prev;
    DLL *next;
    DLL(int val = 0, DLL *prev = nullptr, DLL *next = nullptr):val{val}, prev{prev}, next{next} {}
};
int main(int ac, const char *av[]) {
    int i;
    DLL head;
    auto tail = &head;
    vector<DLL *> ap;
    while(cin >> i) {
	tail = tail->next = new DLL(i, tail);
	ap.push_back(tail);
    }
    head.next->prev = tail;
    tail->next = head.next;
    const int n = ap.size();
    for (auto v: ap) {
	auto t = v->val;
	if (t == 0)
	    continue;
	auto newpos = v;
	if (t > 0) {
	    t %= n - 1;
	    while(t-- > 0) {
		newpos = newpos->next;
		if (newpos == v) newpos = newpos->next;
	    }
	    //assert(newpos != v);
	    if (newpos == v) {
		newpos = newpos->next;
		//continue;
	    }
	    v->prev->next = v->next;
	    v->next->prev = v->prev;
	    v->next = newpos->next;
	    v->prev = newpos;
	    newpos->next = v;
	    v->next->prev = v;
	} else {
	    t %= n - 1;
	    while(t++ < 0) {
		newpos = newpos->prev;
		if (newpos == v) newpos = newpos->prev;
	    }
	    //assert(newpos != v);
	    if (newpos == v) {
		newpos = newpos->prev;
		//continue;
	    }
	    v->prev->next = v->next;
	    v->next->prev = v->prev;
	    v->prev = newpos->prev;
	    v->next = newpos;
	    newpos->prev = v;
	    v->prev->next = v;
	}
    }
    vector<int> r;
    r.reserve(n);
    for (auto h = head.next; ;) {
	clog << h->val << ' ';
	r.push_back(h->val);
	h = h->next;
	if (h == head.next)
	    break;
    }
    clog << endl;
    int ret = 0;
    auto z = find(r.begin(), r.end(), 0) - r.begin();
    for (int t = 1000; t <= 3000; t += 1000) {
	clog << r[(z + t) % n] << endl;
	ret += r[(z + t) % n];
    }
    cout << ret << endl;
    return 0;
}
