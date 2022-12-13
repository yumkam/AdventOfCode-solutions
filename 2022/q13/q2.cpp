#include <bits/stdc++.h>
using namespace std;
struct ListNode {
    ListNode *nested;
    ListNode *next;
    int val;
    ListNode(int val = 0):nested{nullptr},next{nullptr},val{val} {}
    //~ListNode() { if (nested != this) delete nested; delete next; }
    ~ListNode() { 
	if (nested) {
	    while(nested != this) {
		auto next = nested->next;
		delete nested;
		nested = next;
	    }
	}
    }
    static ListNode* parse(string_view s, size_t &next) {
	size_t pos = 0;
	if (s[0] == '[') {
	    auto res = new ListNode();
	    auto tailp = &(res->nested);
	    ++pos;
	    while(s[pos] != ']') {
		size_t snext;
	    	*tailp = parse(s.substr(pos), snext);
		tailp = &((*tailp)->next);
		pos += snext;
		if (s[pos] == ',') ++pos; else assert(s[pos] == ']');
	    }
	    *tailp = res;
	    next = pos + 1;
	    return res;
	} else {
	    auto res = new ListNode();
	    while(pos < s.length() && s[pos] >= '0' && s[pos] <= '9')
		(res->val *= 10) += s[pos++] - '0';
	    next = pos;
	    return res;
	}
    }
    static int compare(ListNode *a, ListNode *b) {
	    if (a->nested == nullptr && b->nested == nullptr) {
		if (a->val < b->val)
		    return -1;
		if (a->val > b->val)
		    return +1;
		return 0;
	    }
	    if (a->nested && b->nested) {
		auto a_end = a;
		auto b_end = b;
		a = a->nested;
		b = b->nested;
		for (;;) {
		    if (a == a_end)
			return b == b_end ? 0 : -1;
		    if (b == b_end)
			return +1;
		    auto res = compare(a, b);
		    if (res != 0)
			return res;
		    a = a->next;
		    b = b->next;
		}
	    }
	    if (a->nested) {
		ListNode temp;
		auto save = b->next;
		temp.nested = b;
		b->next = &temp;
		auto res = compare(a, &temp);
		temp.nested = nullptr;
		b->next = save;
		return res;
	    }
	    if (b->nested) {
		ListNode temp;
		auto save = a->next;
		temp.nested = a;
		a->next = &temp;
		auto res = compare(&temp, b);
		temp.nested = nullptr;
		a->next = save;
		return res;
	    }
	    assert(false);
	    return 0;
    }
};
ostream &operator << (ostream &os, ListNode *l) {
    if (l->nested) {
	auto l_end = l;
	os << '[';
	for (l = l->nested; l != l_end; l = l->next) {
	    os << l << ',';
	}
	os << ']';
    } else {
	os << l->val;
    }
    return os;
}
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	vector<string> grid;
	string s;
	vector<ListNode *> l;
	size_t next;
	auto div2 = ListNode::parse("[[2]]", next);
	auto div6 = ListNode::parse("[[6]]", next);
	l.emplace_back(div2);
	l.emplace_back(div6);
	while(cin) {
	    if (getline(cin, s) && s.length())
		l.emplace_back(ListNode::parse(s, next));
	}
	sort(l.begin(), l.end(), [](auto a, auto b) {
		return ListNode::compare(a, b) < 0;
		});
	auto ret = 1;
	for (unsigned i = 0; i < l.size(); i++) {
	    if (l[i] == div2 || l[i] == div6)
		ret *= i + 1;
	    delete l[i];
	}
	cout << ret << endl;
	return 0;
}
