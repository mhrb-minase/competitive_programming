#include<algorithm>
#include<bitset>
#include<cmath>
#include<deque>
#include<functional>
#include<iomanip>
#include<iostream>
#include<map>
#include<numeric>
#include<queue>
#include<set>
#include<string>
#include<unordered_map>
#include<utility>
#include<vector>

constexpr int IINF = (1 << 30) - 1;
constexpr long long LLINF = 1LL << 61;

template<typename T>
bool chmax(T& a, T b){
    if(a < b){
        a = b;
        return true;
    }
    return false;
}

template<typename T>
bool chmin(T& a, T b){
    if(b < a){
        a = b;
        return true;
    }
    return false;
}

long long meguru_search(long long ok, long long ng, std::function<bool(long long)> check){
    while(1 < std::abs(ok - ng)){
        long long mid = (ok + ng) >> 1;
        if(check(mid)){
            ok = mid;
        }else{
            ng = mid;
        }
    }
    return ok;
}

long double bi_search(long double ok, long double ng, std::function<bool(long double)> check, int loop = 100){
    for(int i = 0 ; i < loop ; ++i){
        long double mid = (ok + ng) * 0.5;
        if(check(mid)){
            ok = mid;
        }else{
            ng = mid;
        }
    }
    return ok;
}

int main(){
    long long R, B, x, y;
    std::cin >> R >> B >> x >> y;

    auto check = [&](long long mid){
        if(R < mid || B < mid){
            return false;
        }
        return (R - mid) / (x - 1) + (B - mid) / (y - 1) >= mid;
    };

    long long ans = meguru_search(0, LLINF, check);
    std::cout << ans << std::endl;

    return 0;
}