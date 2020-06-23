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
    long double A, B, C;
    std::cin >> A >> B >> C;

    auto f = [&](long double t){
        return A * t + B * std::sin(C * t * M_PI);
    };

    long double ans = bi_search(0.0, 1000.0, [&](long double t){ return f(t) < 100.0; }, 1000);
    std::cout << std::fixed << std::setprecision(10) << ans << std::endl;

    return 0;
}