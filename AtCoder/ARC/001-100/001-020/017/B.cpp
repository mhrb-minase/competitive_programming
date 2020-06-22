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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for(int i = 0 ; i < n ; ++i){
        std::cin >> a[i];
    }
    a.emplace_back(-1);

    int ans = 0;
    int cnt = 1;
    for(int i = 0 ; i < n ; ++i){
        if(a[i] < a[i + 1]){
            ++cnt;
        }else{
            ans += std::max(cnt - k + 1, 0);
            cnt = 1;
        }
    }

    std::cout << ans << std::endl;
}