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

int main(){
    int n;
    std::cin >> n;

    std::vector<int> d(n);
    for(int i = 0 ; i < n ; ++i){
        std::cin >> d[i];
    }
    d.emplace_back(0);
    std::sort(d.begin(), d.end());

    std::deque<int> deq;
    for(int i = 0 ; i < n + 1 ; ++i){
        if(i & 1){
            deq.push_back(d[i]);
        }else{
            deq.push_front(-d[i]);
        }
    }

    int ans = abs(deq[0] + 24 - deq[n]);
    for(int i = 0 ; i < n ; ++i){
        chmin(ans, deq[i + 1] - deq[i]);
    }

    std::cout << ans << std::endl;
}