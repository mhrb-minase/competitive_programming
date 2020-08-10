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

int main(){
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for(int i = 0 ; i < n ; ++i){
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());

    auto check = [&](long long mid){
        std::vector< std::vector<bool> > dp(n + 1, std::vector<bool>(k, false));
        dp[0][0] = true;

        for(int i = 0 ; i < n ; ++i){
            for(int j = 0 ; j < k ; ++j){
                dp[i + 1][j] = dp[i + 1][j] || dp[i][j];
                if(i != mid && j + a[i] < k){
                    dp[i + 1][j + a[i]] = dp[i + 1][j + a[i]] || dp[i][j];
                }
            }
        }

        for(int j = std::max(0, k - a[mid]) ; j < k ; ++j){
            if(dp[n][j]){
                return true;
            }
        }

        return false;
    };

    long long ans = meguru_search(n, -1, check);

    std::cout << ans << std::endl;

    return 0;
}