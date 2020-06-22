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
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    std::map<int, int> cnt;
    for(int i = 0 ; i < n ; ++i){
        std::cin >> a[i];
        ++cnt[a[i]];
    }

    std::sort(a.rbegin(), a.rend());

    int ans = 0;
    for(int i = 0 ; i < n ; ++i){
        for(int d = 30 ; d >= 0 ; --d){
            int k = meguru_search(-1, n, [&](int j){ return a[j] >= (1 << d) - a[i]; });
            if(k >= 0 && a[i] + a[k] == (1 << d) && (a[i] == a[k] && cnt[a[i]] >= 2 || a[i] != a[k] && cnt[a[i]] >= 1 && cnt[a[k]] >= 1)){
                ++ans;
                --cnt[a[i]];
                --cnt[a[k]];
                break;
            }
        }
    }

    std::cout << ans << std::endl;
}