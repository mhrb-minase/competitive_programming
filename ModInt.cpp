#include<iostream>

template<long long modulus>
class ModInt{
    long long num;

    long long mod(long long n){
        if(n < 0LL){
            n = (n % modulus) + modulus;
        }
        return n % modulus;
    }

    long long ext_gcd(long long a, long long b, long long &x, long long &y){
        if(b == 0LL){
            x = 1;
            y = 0;
            return a;
        }

        long long d = ext_gcd(b, a % b, y, x);
        y -= a / b * x;

        return d;
    }

    long long get_inv(long long n){
        long long x, y;
        ext_gcd(n, modulus, x, y);
        return mod(x);
    }

public:
    ModInt(long long n = 0LL){
        num = mod(n);
    }

    long long get(void){
        return num;
    }

    ModInt &operator+=(const ModInt &rhs){
        num += rhs.num;
        if(num >= modulus){
            num -= modulus;
        }
        return *this;
    }

    ModInt &operator-=(const ModInt &rhs){
        if(num < rhs.num){
            num += modulus;
        }
        num -= rhs.num;
        return *this;
    }

    ModInt &operator*=(const ModInt &rhs){
        num = num * rhs.num % modulus;
        return *this;
    }

    ModInt &operator/=(const ModInt &rhs){
        long long inv = get_inv(rhs.num);
        num = num * inv % modulus;
        return *this;
    }

    template<typename T>
    ModInt &operator+=(const T &rhs){
        return *this += ModInt(rhs);
    }

    template<typename T>
    ModInt &operator-=(const T &rhs){
        return *this -= ModInt(rhs);
    }

    template<typename T>
    ModInt &operator*=(const T &rhs){
        return *this *= ModInt(rhs);
    }

    template<typename T>
    ModInt &operator/=(const T &rhs){
        return *this /= ModInt(rhs);
    }

    template<typename T>
    ModInt operator+(const T &rhs) const {
        return ModInt(*this) += ModInt(rhs);
    }

    template<typename T>
    ModInt operator-(const T &rhs) const {
        return ModInt(*this) -= ModInt(rhs);
    }

    template<typename T>
    ModInt operator*(const T &rhs) const {
        return ModInt(*this) *= ModInt(rhs);
    }

    template<typename T>
    ModInt operator/(const T &rhs) const {
        return ModInt(*this) /= ModInt(rhs);
    }

    ModInt &operator=(const ModInt &rhs){
        num = rhs.num;
        return *this;
    }

    template<typename T>
    ModInt &operator=(const T &rhs){
        num = mod(rhs);
        return *this;
    }

    bool operator<(const ModInt &rhs) const {
        return num < rhs.num;
    }
};

template<long long modulus>
std::istream &operator>>(std::istream &lhs, ModInt<modulus> &rhs){
    long long val;
    lhs >> val;
    rhs = val;
    return lhs;
}

template<long long modulus>
std::ostream &operator<<(std::ostream &lhs, ModInt<modulus> rhs){
    lhs << rhs.get();
    return lhs;
}

/*

verify:https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/NTL_1_B/judge/3897900/C++14
       https://atcoder.jp/contests/abc055/submissions/7793608
       https://atcoder.jp/contests/arc009/submissions/7722387
       https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/ALDS1_14_B/judge/3898066/C++14
       https://atcoder.jp/contests/abc141/submissions/7734650

*/
