// ModInt.cpp ( https://github.com/mhrb-minase/competitive_programming/blob/master/ModInt.cpp ) が必要

#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>

constexpr long long mod1 = 2147483587LL;
constexpr long long mod2 = 3037000453LL;

class RollingHash{
    using mint1 = ModInt<mod1>;
    using mint2 = ModInt<mod2>;

    std::vector<mint1> hash1, power1;
    std::vector<mint2> hash2, power2;

    mint1 base1;
    mint2 base2;

    int n;

public:
    RollingHash(std::string s = ""){
        std::srand(time(nullptr));

        base1 = rand();
        if(base1.get() < 1024){
            base1 -= 1024;
        }
        base2 = rand();
        if(base2.get() < 1024){
            base2 -= 1024;
        }

        n = (int)s.size();

        hash1.assign(n + 1, mint1(0));
        hash2.resize(n + 1, mint2(0));
        power1.resize(n + 1, mint1(1));
        power2.resize(n + 1, mint2(1));
        for(int i = 0 ; i < n ; ++i){
            hash1[i + 1] = hash1[i] * base1 + s[i];
            hash2[i + 1] = hash2[i] * base2 + s[i];
            power1[i + 1] = power1[i] * base1;
            power2[i + 1] = power2[i] * base2;
        }
    }

    long long get(int l, int r) const {
        long long res = (hash1[r] - hash1[l] * power1[r - l]).get();
        res *= mod2;
        res += (hash2[r] - hash2[l] * power2[r - l]).get();
        return res;
    }

    int get_LCP(const RollingHash& b, int l1, int r1, int l2, int r2){
        int len = std::min(r1 - l1, r2 - l2);
        int low = -1, high = len;
        while(high - low > 1){
            int mid = (low + high) >> 1;
            if(get(l1, l1 + mid) == b.get(l2, l2 + mid)){
                low = mid;
            }else{
                high = mid;
            }
        }
        return low;
    }

    int size(void){
        return n;
    }
};

/*

verify:https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/ALDS1_14_B/judge/3898066/C++14
       https://atcoder.jp/contests/abc141/submissions/7734650

*/
