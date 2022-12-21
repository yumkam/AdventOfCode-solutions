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
    friend rnum operator - (rnum a) { // unary minus
	rnum c(-a.num, a.den);
	//c.canonify();
	return c;
    }
    rnum &operator += (rnum b) {
	num = num*b.den + b.num*den;
	den *= b.den;
	canonify();
	return *this;
    }
    friend rnum operator + (rnum a, rnum b) {
	auto c = a; c += b; return c;
    }
    rnum &operator -= (rnum b) {
	num = num*b.den - b.num*den;
	den *= b.den;
	canonify();
	return *this;
    }
    friend rnum operator - (rnum a, rnum b) {
	auto c = a; c -= b; return c;
    }
    rnum &operator *= (rnum b) {
	num *= b.num;
	den *= b.den;
	canonify();
	return *this;
    }
    friend rnum operator * (rnum a, rnum b) {
	auto c = a; c *= b; return c;
    }
    rnum &operator /= (rnum b) {
	num *= b.den;
	den *= b.num;
	canonify();
	return *this;
    }
    friend rnum operator / (rnum a, rnum b) {
	auto c = a; c /= b; return c;
    }
    friend ostream &operator <<(ostream &os, rnum x) {
	if (x.den == 1)
	    return os << x.num;
	else
	    return os << '(' << x.num << '/' << x.den << ')';
    }
};
