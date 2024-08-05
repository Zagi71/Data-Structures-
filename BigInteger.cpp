#include "BigInteger.h"
#include "List.h"
#include <ostream>
#include <string>

static constexpr int power = 9;
static constexpr long base = 1'000'000'000;

// ----- Helper Functions ----- 

// to make both lists same num of digits
static void padList(List &l, int n) {
    for(l.moveBack(); n > 0; n--) {
        l.insertBefore(0);
    }
}

void sumList(List &res, List& l1, List&l2) {
    l1.moveFront();
    l2.moveFront();
    int carry = 0;
    for (; l1.position() < l1.length(); l1.moveNext(), l2.moveNext()) {
        long s = l1.peekNext() + l2.peekNext() + carry;
        if (s/base != 0) { carry = 1; s = s%base; }
        else carry = 0;
        res.insertBefore(s);
    }
    if (carry == 1) res.insertBefore(1);
}

void mulList(List &res, List &l, ListElement n) {
    ListElement rem = 0;
    for(l.moveFront(); l.position() < l.length(); l.moveNext()) {
        ListElement p = n*l.peekNext() + rem;
        res.insertBefore(p%base);
        rem = p/base;
    }
    if (rem != 0) res.insertBefore(rem);
}

void shiftList(List &l, int p) {
    for(l.moveFront(); p > 0; p--) {
        l.insertAfter(0);
    }
}

static void unpadList(List &l) {
    for(l.moveBack(); l.length() > 0;) {
        if(l.peekPrev() == 0) l.eraseBefore();
        else break;
    }
}

static void increment(List &l) {
    int carry = 0;
    for(l.moveFront(); l.position() < l.length(); l.moveNext()) {
        ListElement v = l.peekNext();
        ListElement newv = (v+1)%base;
        l.setAfter(newv);
        if ((v+1)/base == 0) { carry = 0; break; }
        else carry = 1;
    }
    if (carry == 1) l.insertBefore(1);
}

// the (base-1)'s compliment
// eg. 76201 in base 10, just flip the digits to 9's compliment: 
// 76201 -> 23798
static void complementList(List &l) {
    for(l.moveBack(); l.position() > 0; l.movePrev()) {
        l.setBefore((base - 1) - l.peekPrev());
    }
}
// ---------------------------------------


BigInteger::BigInteger() : signum(0), digits() {}

BigInteger::BigInteger(long x) {
    signum = x < 0 ? -1 : (x > 0 ? 1 : 0);
    if (x < 0) x = -x;
    digits = List();
    for(; x != 0; x /= base) {
        digits.insertBefore(x%base);
    }
}

BigInteger::BigInteger(std::string s) : BigInteger() {
    if (s.empty()) { return; }
    if (s[0] == '-' || s[0] == '+') {
        signum = s[0] == '-' ? -1 : 1; s[0] = '0';
    }
    int d = 0;
    for(int i = s.length()-1, r = 1; i >= 0; i--) {
        d += r*(s[i]-'0');
        r *= 10;
        if (r == base || i == 0) {
            digits.insertBefore(d);
            d = 0; r = 1;
        }
    }
    // removing leading 0s:
    digits.moveBack();
    for(; digits.length() > 0;) {
        if (digits.peekPrev() == 0) { digits.eraseBefore(); }
        else break;
    }
    if (digits.length() == 0) signum = 0;
    else if (signum == 0) signum = 1;
}

BigInteger::BigInteger(const BigInteger& N) : 
    signum(N.signum), digits(N.digits) {}

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger &N) const {
    BigInteger diff = this->sub(N);
    return diff.signum;
}

void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    if (signum == 0) return;
    signum = -signum;
}

BigInteger BigInteger::add(const BigInteger& N) const {
    List l1 = digits;
    List l2 = N.digits;
    if (signum == 0 || N.signum == 0) {
        BigInteger res;
        if (signum == 0) { res.signum = N.signum; res.digits = l2; }
        else { res.signum = signum; res.digits = l1; }
        return res;
    }
    int max_dig = l1.length() > l2.length() ? l1.length() : l2.length();
    padList(l1, max_dig - l1.length());
    padList(l2, max_dig - l2.length());
    
    if (signum == N.signum) {
        List l3;
        sumList(l3, l1, l2);
        BigInteger res;
        res.signum = signum;
        res.digits = l3;
        return res;
    }
    
    if (signum < 0) complementList(l1);
    else if (N.signum < 0) complementList(l2);

    List l3;
    BigInteger res;
    sumList(l3, l1, l2);
    if(l3.length() > max_dig) { 
        l3.moveBack(); l3.eraseBefore();
        increment(l3);
        unpadList(l3);
        res.signum = 1;
    }
    else { 
        complementList(l3);
        unpadList(l3);
        res.signum = (l3.length() == 0)? 0 : -1;
    }
    res.digits = l3;
    return res;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger n = N;
    n.negate();
    return this->add(n);
}

BigInteger BigInteger::mult(const BigInteger & N) const {
    List l1 = digits;
    List l2 = N.digits;
    int max_dig = l1.length() > l2.length() ? l1.length() : l2.length();
    List l3;
    int shift = 0;
    for(l1.moveFront(); l1.position() < l1.length(); l1.moveNext()) {
        List l4, l5;
        l5 = l3;
        l3.clear();
        mulList(l4, l2, l1.peekNext());
        shiftList(l4, shift);
        padList(l4, 2*max_dig-l4.length());
        padList(l5, 2*max_dig-l5.length());
        sumList(l3, l4, l5);
        shift++;
    }
    unpadList(l3);
    BigInteger res;
    res.signum = signum*N.signum;
    res.digits = l3;
    return res;
}

std::string BigInteger::to_string() {
    // std::cout << signum << ", " << digits << std::endl;
    std::string s = "";
    if (signum == 0) return "0";
    if (signum == -1) s += '-';
    digits.moveBack();
    s += std::to_string(digits.peekPrev());
    digits.movePrev();
    for(; digits.position() > 0; digits.movePrev()) {
        std::string digit(power, '0');
        long d = digits.peekPrev();
        for(int i = power-1; d != 0; d /= 10, i--) {
            digit[i] = '0' + (d%10);
        }
        s += digit;
    }
    return s;
}

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}

bool operator==(const BigInteger &A, const BigInteger &B) {
    return (A.compare(B) == 0);
}

bool operator<(const BigInteger &A, const BigInteger &B) {
    return (A.compare(B) == -1);
}

bool operator<=(const BigInteger &A, const BigInteger &B) {
    return (A.compare(B) < 1);
}

bool operator>(const BigInteger &A, const BigInteger &B) {
    return (A.compare(B) == 1);
}

bool operator>=(const BigInteger &A, const BigInteger &B) {
    return (A.compare(B) > -1);
}

BigInteger operator+(const BigInteger &A, const BigInteger &B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger &A, const BigInteger &B) {
    A = A+B;
    return A;
}

BigInteger operator-(const BigInteger &A, const BigInteger &B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger &A, const BigInteger &B) {
    A = A-B;
    return A;
}

BigInteger operator*(const BigInteger &A, const BigInteger &B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger &A, const BigInteger &B) {
    A = A*B;
    return A;
}
