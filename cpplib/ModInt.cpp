template <long long modulus>
class ModInt{
    long long num;

    constexpr long long mod(long long x) const noexcept {
        x %= modulus;
        if(x < modulus){
            x += modulus;
        }
        return x;
    }

    constexpr long long inv(long long x) const noexcept {
        long long y = modulus, u = 1, v = 0;
        while(y){
            long long t = x / y;
            x -= t * y;
            std::swap(x, y);
            u -= t * v;
            std::swap(u, v);
        }
        return mod(u);
    }

public:
    constexpr ModInt(const long long x = 0) noexcept : num(mod(x)) {}

    constexpr long long &value() noexcept { return num; }

    constexpr const long long &value() const noexcept { return num; }

    constexpr ModInt operator+(const ModInt rhs) const noexcept {
        return ModInt(*this) += rhs;
    }

    constexpr ModInt operator-(const ModInt rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }

    constexpr ModInt operator*(const ModInt rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }

    constexpr ModInt operator/(const ModInt rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    constexpr ModInt &operator+=(const ModInt rhs) noexcept {
        num += rhs.num;
        if (num >= modulus){
            num -= modulus;
        }
        return *this;
    }

    constexpr ModInt &operator-=(const ModInt rhs) noexcept {
        if (num < rhs.num){
            num += modulus;
        }
        num -= rhs.num;
        return *this;
    }

    constexpr ModInt &operator*=(const ModInt rhs) noexcept {
        num = num * rhs.num % modulus;
        return *this;
    }

    constexpr ModInt &operator/=(const ModInt rhs) noexcept {
        num = num * inv(rhs.num) % modulus;
        return *this;
    }

    template<typename T>
    constexpr ModInt operator+(const T rhs) const noexcept {
        return ModInt(*this) += rhs;
    }

    template<typename T>
    constexpr ModInt operator-(const T rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }

    template<typename T>
    constexpr ModInt operator*(const T rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }

    template<typename T>
    constexpr ModInt operator/(const T rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    template<typename T>
    constexpr ModInt &operator+=(const T rhs) noexcept {
        num = mod(num + rhs);
        return *this;
    }

    template<typename T>
    constexpr ModInt &operator-=(const T rhs) noexcept {
        num = mod(num - rhs);
        return *this;
    }

    template<typename T>
    constexpr ModInt &operator*=(const T rhs) noexcept {
        num = num * mod(rhs) % modulus;
        return *this;
    }

    template<typename T>
    constexpr ModInt &operator/=(const T rhs) noexcept {
        num = num * inv(mod(rhs)) % modulus;
        return *this;
    }

    bool &operator<(const ModInt rhs) const noexcept {
        return num < rhs.num;
    }

    bool &operator==(const ModInt rhs) const noexcept {
        return num == rhs.num;
    }

    ModInt &operator=(const ModInt rhs) const noexcept {
        num = rhs.num;
        return *this;
    }

    template<typename T>
    ModInt &operator=(const T rhs) const noexcept {
        num = mod(rhs);
        return *this;
    }
};

template <long long modulus>
std::istream &operator>>(std::istream &lhs, ModInt<modulus> &rhs){
    long long val;
    lhs >> val;
    rhs = val;
    return lhs;
}

template <long long modulus>
std::ostream &operator<<(std::ostream &lhs, ModInt<modulus> rhs){
    lhs << rhs.get();
    return lhs;
}

using mint = ModInt<1000000007>;