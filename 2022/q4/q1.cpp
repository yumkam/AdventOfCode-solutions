#include <bits/stdc++.h>
using namespace std;
int main(int ac, const char *av[]) {
	//if (ac > 1 && av[1][0])
	//	maxs = atoi(av[1]);
	int ret = 0;
	int a, b, c, d;
	char ch;
	while(cin >>a>>ch>>b>>ch>>c>>ch>>d) {
	    ret += a <= c && d <= b || c <= a && b <= d;
	}
	cout << ret << endl;
	return 0;
}
