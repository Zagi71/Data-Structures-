#include <iostream>
#include "BigInteger.h"

int main() {
    BigInteger x("12345");
    BigInteger x2("-4839275");
    BigInteger x3("-000542540000642600");
    BigInteger x4("-000000000");

    BigInteger a("355797");
    BigInteger b("149082");
    BigInteger c("999999");
    BigInteger one("1");
    std::cout << x.to_string() << std::endl;
    std::cout << x2.to_string() << std::endl;
    std::cout << x3.to_string() << std::endl;
    std::cout << x4.to_string() << std::endl;
    BigInteger sum = a.add(b);
    BigInteger sum2 = c.add(one);
    std::cout << sum.to_string() << std::endl;
    std::cout << sum2.to_string() << std::endl;

    BigInteger y1("-996");
    BigInteger y2("997");
    std::cout << y1 << std::endl;
    std::cout << y2 << std::endl;
    std::cout << y1+y2 << std::endl;
    std::cout << y2-y1 << std::endl;

    BigInteger z1("5832759701674937286978432976891076481768741348376894307684785974901384938296");
    BigInteger z2("85934075927395791383592589382957328278957827857482795028395");
    std::cout << (z1>=z2) << std::endl;
    BigInteger z3 = z1*z2;
    std::cout << z3 << std::endl;
    z1 *= z2;
    std::cout << z1 << std::endl;
    std::cout << (z1==z3) << std::endl;
    z1.makeZero();
    std::cout << z1 << std::endl;

    BigInteger l(-459021);
    std::cout << l << std::endl;
    return 0;
}
