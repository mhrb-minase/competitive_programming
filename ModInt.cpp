#include<iostream>
#include<cmath>
using namespace std;

// 除算はmodulusと互いに素な数のみ対応
template<long long modulus>
class ModInt{
    long long num;

    long long mod(long long n){
        return (n % modulus + modulus) % modulus;
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
        init(n);
    }

    void init(long long n = 0LL){
        num = mod(n);
        return;
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
        num -= rhs.num;
        if(num < 0LL){
            num += modulus;
        }
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

    ModInt operator+(const ModInt &rhs) const {
        return ModInt(*this) += rhs;
    }

    ModInt operator-(const ModInt &rhs) const {
        return ModInt(*this) -= rhs;
    }

    ModInt operator*(const ModInt &rhs) const {
        return ModInt(*this) *= rhs;
    }

    ModInt operator/(const ModInt &rhs) const {
        return ModInt(*this) /= rhs;
    }

    ModInt &operator=(const ModInt &rhs){
        num = rhs.num;
        return *this;
    }

    bool operator<(const ModInt &rhs) const {
        return num < rhs.num;
    }
};

template<long long modulus>
ostream &operator<<(ostream &lhs, ModInt<modulus> &rhs){
    lhs << rhs.get();
    return lhs;
}

template<long long modulus>
istream &operator>>(istream &lhs, ModInt<modulus> &rhs){
    long long val;
    lhs >> val;
    rhs.init(val);
    return lhs;
}

// 使用例
// 標準入力から2つの整数を受け取り、様々な演算結果を mod 23 で出力
int main(){
    ModInt<23> a, b;
    cin >> a >> b;
    cout << a << " " << b << endl;
    a = a + b;
    cout << a << " " << b << endl;
    a += b;
    cout << a << " " << b << endl;
    a = a - b;
    cout << a << " " << b << endl;
    a -= b;
    cout << a << " " << b << endl;
    a = a * b;
    cout << a << " " << b << endl;
    a *= b;
    cout << a << " " << b << endl;
    a = a / b;
    cout << a << " " << b << endl;
    a /= b;
    cout << a << " " << b << endl;
    return 0;
}
