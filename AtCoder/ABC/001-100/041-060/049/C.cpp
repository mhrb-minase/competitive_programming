
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
    std::string s;
    std::cin >> s;

    std::reverse(s.begin(), s.end());

    const int n = (int)s.size();

    bool flg = true;
    for(int i = 0 ; i < n ; ){
        if(s.substr(i, 7) == "remaerd"){
            i += 7;
        }else if(s.substr(i, 6) == "resare"){
            i += 6;
        }else if(s.substr(i, 5) == "maerd" || s.substr(i, 5) == "esare"){
            i += 5;
        }else{
            flg = false;
            break;
        }
    }

    if(flg){
        std::cout << "YES" << std::endl;
    }else{
        std::cout << "NO" << std::endl;
    }
}