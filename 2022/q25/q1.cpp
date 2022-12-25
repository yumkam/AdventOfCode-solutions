#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
    string s;
    int64_t sum = 0;
    while(getline(cin, s) && !s.empty()) {
	int64_t val = 0;
	for (unsigned j = 0; j < s.length(); j++) {
	    val *= 5;
	    switch(s[j]) {
		case '0': case '1': case '2':
		    val += s[j] - '0';
		    break;
		case '-':
		    val -= 1;
		    break;
		case '=':
		    val -= 2;
		    break;
		default:
		    assert(0);
	    }
	}
	clog << val << endl;
	sum += val;
    }
    clog << sum << endl;
    s.clear();
    while(sum) {
	int digit = sum % 5;
	int carry = 0;
	if (digit == 4) {
	    s += '-';
	    carry = 1;
	} else if (digit == 3) {
	    s += '=';
	    carry = 1;
	} else {
	    s += (char)(digit + '0');
	}
	sum /= 5;
	sum += carry;
    }
    reverse(s.begin(), s.end());
    cout << s << endl;
    return 0;
}
