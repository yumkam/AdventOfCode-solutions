#ifndef INT128_HPP
#define INT128_HPP 1
#include <iostream>
#include <string>
#include <cassert>
namespace int128_impl {
    template <typename IS, typename T>
	void read_integer(IS &is, T &res) {
	    res = 0;
	    std::istream::sentry s(is);
	    int ch = is.peek();
	    T sign = 0;
	    if constexpr (((T)0) - 1 < 0) {
		if (ch == '+') {
		    is.get();
		    ch = is.peek();
		} else if (ch == '-') {
		    is.get();
		    ch = is.peek();
		    --sign;
		}
	    }
	    auto basef = is.flags() & std::ios_base::basefield;
	    int base = 0;
	    if (basef & std::ios_base::dec)
		// no prefix
		base = 10;
	    else if (basef & std::ios_base::hex) {
		base = 16;
		if (ch == '0') { // skip "0x" prefix if any
		    is.get();
		    ch = is.peek();
		    if (ch == 'x' || ch == 'X') {
			is.get();
			ch = is.peek();
		    }
		}
	    } else if (basef & std::ios_base::oct)
		// no need to skip 0 prefix if any
		base = 8;
	    if (base == 0) {
		if (ch == '0') {
		    is.get();
		    ch = is.peek();
		    if (ch == 'x' || ch == 'X') {
			is.get();
			ch = is.peek();
			base = 16;
		    } else if (ch == 'b' || ch == 'B') {
			is.get();
			ch = is.peek();
			base = 2;
		    } else {
			base = 8;
		    }
		} else {
		    base = 10;
		}
	    }
	    for(;;) {
		int d = ch >= '0' && ch <= '9' ? ch - '0' :
		    ch >= 'a' && ch <= 'z' ? ch - 'a' + 10 :
		    ch >= 'A' && ch <= 'Z' ? ch - 'A' + 10 :
		    base;
		if (d >= base)
		    break;
		res = res*base + ((d + sign) ^ sign);
		is.get();
		ch = is.peek();
	    }
	}
}
std::istream &operator >> (std::istream &is, __int128 &i) { int128_impl::read_integer(is, i); return is; }
std::istream &operator >> (std::istream &is, unsigned __int128 &i) { int128_impl::read_integer(is, i); return is; }
namespace int128_impl {
    template <typename T>
	char *integer_to_chars(char * const out, char * const limit, T val, int base = 10, char letter = 'a') {
	    const char sign = 0 - (val < 0);
	    auto p = out;
	    assert(base > 1);
	    for (; val; val /= base) {
		char d = ((char)(val % base) + sign) ^ sign;
		d += '0';
		if (d > '9') d += letter - ('9' + 1);
		assert(p != limit);
		*--p = d;
	    }
	    if (p == out) {
		assert(p != limit);
		*--p = '0';
	    }
	    if (sign) {
		assert(p != limit);
		*--p = '-';
	    }
	    return p;
	}
    template <typename OS, typename T>
	void print_int(OS &os, T val) {
	    char out[(sizeof(val)*8 + 3 - 1)/3 + 1]; // maximum size for base-8/octal string
	    std::streamsize width = 0;
	    if ((os.flags() & std::ios_base::showpos) && !(val < 0))
		    ++width;
	    if (os.flags() & std::ios_base::showbase) {
		if ((os.flags() & std::ios_base::oct) && val != 0)
		    width += 1;
		else if (os.flags() & std::ios_base::hex)
		    width += 2;
	    }
	    auto p = int128_impl::integer_to_chars(out + sizeof(out), out, val, os.flags() & std::ios_base::oct ? 8 : os.flags() & std::ios_base::hex ? 16 : 10, os.flags() & std::ios_base::uppercase ? 'A' : 'a');
	    width += out + sizeof(out) - p;
	    if (0 == (os.flags() & (std::ios_base::adjustfield ^ std::ios_base::right)))
		for (; width < os.width(); ++width)
		    os.put(os.fill());
	    if (val < 0)
		os.put('-'), ++p;
	    else if ((os.flags() & std::ios_base::showpos))
		os.put('+');
	    if (os.flags() & std::ios_base::showbase) {
		if ((os.flags() & std::ios_base::oct) && val != 0)
		    os.put('0');
		else if (os.flags() & std::ios_base::hex)
		    os.put('0').put('x');
	    }
	    if ((os.flags() & std::ios_base::internal))
		for (; width < os.width(); ++width)
		    os.put(os.fill());
	    os.write(p, out + sizeof(out) - p);
	    if ((os.flags() & std::ios_base::left))
		for (; width < os.width(); ++width)
		    os.put(os.fill());
	    os.width(0);
	}
    template <typename T>
	std::string to_string_impl(T val, int base) {
	    char out[sizeof(val)*8 + 1]; // maximum size for binary/base=2 string
	    auto p = int128_impl::integer_to_chars(out + sizeof(out), out, val, base);
	    return std::string(p, out + sizeof(out) - p);
	}
}
std::ostream &operator << (std::ostream &os, __int128 val) {
    int128_impl::print_int(os, val);
    return os;
}
std::ostream &operator << (std::ostream &os, unsigned __int128 val) {
    int128_impl::print_int(os, val);
    return os;
}
std::string to_string(__int128 val, int base = 10) {
    return int128_impl::to_string_impl(val, base);
}
std::string to_string(unsigned __int128 val, int base = 10) {
    return int128_impl::to_string_impl(val, base);
}
//__int128 abs(__int128 x) {
//    return x < 0 ? -x : x;
//}
//  template<> struct __is_integral_helper<signed __int128>: public true_type {};
//  template<> struct __is_integral_helper<unsigned __int128>: public true_type {};
//  template<> struct __make_unsigned<signed __int128> { typedef unsigned __int128 __type; };
//  template<> struct __make_signed<unsigned __int128> { typedef signed __int128 __type; };
#endif // INT128_HPP
#if INT128_TEST
#include <array>
#include <sstream>
#include <iomanip>
int main() {
    using namespace std;
    __int128 zero = 0;
    __int128 i128min = (((unsigned __int128)1)<<127);
    __int128 i128max = (((unsigned __int128)1)<<127) - 1;
    cout << dec << zero << endl << i128max << endl << i128min << endl;
    cout << hex << zero << endl << i128max << endl << i128min << endl;
    cout << oct << zero << endl << i128max << endl << i128min << endl;
    //cout << to_string(i128min, 2) << endl;
    //cout	<< to_string(i128max, 2) <<endl;
    cout << to_string(i128min, 2) << endl <<  to_string(i128max, 2) <<endl;
    unsigned __int128 uzero = 0;
    unsigned __int128 u128max = ((unsigned __int128)0) - 1;
    cout << dec << uzero << endl << u128max << endl;
    cout << hex << uzero << endl << u128max << endl;
    cout << oct << uzero << endl << u128max << endl;
    cout << dec << to_string(u128max, 2) << endl;
    for (auto x: array<__int128, 3> { zero, i128min, i128max} ) {
	stringstream ss;
	ss << ' ' << '\t' << '\n' << x << endl << x << endl << ' ' << showbase << hex << x << dec << endl << oct << x << endl << dec << x << endl;
	ss.seekg(0);
	decltype(x) y, z, tx, to, td;
	ss >> y >> z;
	cout << ss.str() << endl << y << endl;
	ss >> setbase(0);
	ss >> tx >> to >> td;
	assert(y == x);
	assert(z == x);
	assert(tx == x);
	assert(to == x);
	assert(td == x);
    }
    for (auto x: array<unsigned __int128, 2> { uzero, u128max} ) {
	stringstream ss;
	ss << ' ' << '\t' << '\n' << x << endl << x << ' ' << showbase << x << dec << endl << oct << x << endl << dec << x << endl << "0b" << to_string(x, 2) << endl;
	ss.seekg(0);
	decltype(x) y, z, tx, to, td, tb;
	ss >> y >> z;
	ss >> setbase(0);
	ss >> tx >> to >> td >> tb;
	cout << dec <<'t' << tx << "=0x" << hex << tx << dec << endl;
	cout <<'x' << x << endl;
	cout << ss.str() << endl << y << endl;
	assert(y == x);
	assert(z == x);
	assert(tx == x);
	assert(to == x);
	assert(td == x);
    }
    cout << showpos << setw(64) << u128max << endl;
    cout << showpos << setw(64) << i128max << endl;
    cout << showpos << setw(64) << i128max << endl;
    cout << showpos << setw(64) << i128min << endl;
    cout << showbase << hex;
    cout << showpos << setw(64) << u128max << endl;
    cout << showpos << setw(64) << i128max << endl;
    cout << showpos << setw(64) << i128max << endl;
    cout << showpos << setw(64) << i128min << endl;
    cout << '[' << left << setw(64) << i128min << ']' << endl;
    cout << '[' << internal << setw(64) << setfill('0') << i128min << ']' << endl;
    cout << '[' << internal << setw(64) << setfill('0') << hex << i128min << ']' << endl;
    cout << '[' << internal << setw(64) << setfill('0') << hex << i128max << ']' << endl;
    cout << noshowpos << '[' << internal << setw(64) << setfill('0') << hex << i128max << ']' << endl;
    cout << noshowpos << '[' << internal << setw(64) << setfill('0') << hex << i128min << ']' << endl;
    cout << right << noshowbase << dec;
    clog << noshowpos << showbase << setw(6) << hex << -123 << endl;
    clog << noshowpos << showbase << setw(6) << oct << 0 << endl;
    clog << noshowpos << showbase << setw(6) << oct << 1 << endl;
    clog << noshowpos << showbase << setw(6) << hex << 0 << endl;
    clog << noshowpos << showbase << setw(6) << hex << 1 << endl;
    clog << internal << setfill('0');
    clog << noshowpos << showbase << setw(6) << oct << 0 << endl;
    clog << noshowpos << showbase << setw(6) << oct << 1 << endl;
    clog << noshowpos << showbase << setw(6) << hex << 0 << endl;
    clog << noshowpos << showbase << setw(6) << hex << 1 << endl;
    return 0;
}
#endif
