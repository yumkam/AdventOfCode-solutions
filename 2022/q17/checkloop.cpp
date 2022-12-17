#include <bits/stdc++.h>
using namespace std;
/*
####

.#.
###
.#.

..#
..#
###

#
#
#
#

##
##
 */
enum class shape {
    first,
    minus = first,
    plus,
    angle,
    bar,
    square,
    max
};
int main(int ac, const char *av[]) {
    //if (ac > 1 && av[1][0])
    //	maxs = atoi(av[1]);
    deque<uint8_t> grid;
    const unsigned gridwidth = 7;
    uint8_t full = (1<<gridwidth) - 1;
    unsigned maxlevel = 1;
    unsigned sh = static_cast<unsigned>(shape::minus);
    string pattern;
    cin >> pattern;
    vector<unsigned> lps(pattern.size());
    for (unsigned i = 1, j = 0; i < pattern.size(); ) {
	if (pattern[i] == pattern[j]) {
	    lps[i++] = ++j;
	    if ((i % (i - j)) == 0) {
		cout << i << ' ' << (i - j)  << endl;
	    }
	} else if (j > 0) {
	    j = lps[j - 1];
	} else {
	    ++i;
	}
    }
    cout << pattern.length() << ' ' << lps.back() << endl;
    const unsigned shapewidth[] {
	4, 3, 3, 1, 2,
    };
    const unsigned shapeheight[] {
	1, 3, 3, 4, 2,
    };
    const unsigned shapemask[][4] { // from bottom to top, from left to right
	{ 15 }, { 2, 7, 2 }, { 7, 4, 4 }, {1,1,1,1}, {3,3},
    };
    unsigned gas = 0;
    unsigned ctr = 1;
    unsigned skip = 0;
    grid.push_back(full);
    while(ctr <= 2022*2) {
	unsigned xpos = 2;
	clog << maxlevel << ' ' << sh << ' ' << gas << ' ' << skip << ' ' << ctr << endl;
	unsigned ypos = maxlevel + 3;
	grid.resize(ypos + shapeheight[sh]);
	//assert(grid[0] == full);
	for (;;) {
	    auto movement = (pattern[gas++] == '>')*2 - 1;
	    if (gas == pattern.size()) gas = 0;
	    if (xpos + shapewidth[sh] + movement > gridwidth)
		movement = 0;
	    if (xpos + 1 + movement == 0)
		movement = 0;
	    if (movement)
		for (unsigned i = 0; i < shapeheight[sh]; i++) {
		    if (grid[ypos + i] & (shapemask[sh][i] << (xpos + movement))) {
			movement = 0;
			break;
		    }
		}
	    xpos += movement;
#if 0
	    clog << xpos << ' ' << ypos << endl;
#endif
	    assert(ypos > 0);
	    unsigned ynext = ypos - 1;
	    for (unsigned i = 0; i < shapeheight[sh]; i++) {
		if (grid[ynext + i] & (shapemask[sh][i] << xpos)) {
		    ynext = ypos;
		    break;
		}
	    }
	    if (ynext == ypos) {
		unsigned skipto = 0;
		for (unsigned i = 0; i < shapeheight[sh]; i++) {
		    grid[ypos + i] |= (shapemask[sh][i] << xpos);
#if 1
		    if ((grid[ypos + i] | (grid[ypos + i - 1])) == full) {
			skipto = ypos + i - 1;
			clog << '+' << skipto << endl;
		    }
#endif
		    if (grid[ypos + i] == full) {
			skipto = ypos + i;
			clog << '!' << skipto << endl;
		    }
		}
		maxlevel = max(maxlevel, ypos + shapeheight[sh]);
		while(skipto > 0) {
		    skip++;
		    maxlevel--;
		    grid.pop_front();
		    skipto--;
		}
		break;
	    }
	    ypos = ynext;
	}
	if (static_cast<shape>(++sh) == shape::max)
	    sh = static_cast<unsigned>(shape::first);
	++ctr;
#if 0
	for (unsigned i = 0; i < grid.size(); i++) {
	    for (unsigned j = 0, v = grid[i]; j < gridwidth; j++, v >>= 1)
		clog << ((v & 1) ? '#':'.');
	    clog << endl;
	}
#endif
    }
    cout << maxlevel + skip - 1 << endl;
    return 0;
}
