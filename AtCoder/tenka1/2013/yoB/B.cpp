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

void solve(void){
    int Q;
    long long L;
    std::cin >> Q >> L;

    std::vector< std::pair<long long, int> > st;
    long long sz = 0;

    while(Q--){
        std::string q;
        std::cin >> q;

        long long N;
        int M;
        if(q == "Push"){
            std::cin >> N >> M;
            if(sz + N > L){
                std::cout << "FULL" << std::endl;
                return;
            }
            sz += N;
            st.emplace_back(N, M);
        }else if(q == "Pop"){
            std::cin >> N;
            if(sz < N){
                std::cout << "EMPTY" << std::endl;
                return;
            }
            sz -= N;
            while(N > 0){
                long long t = st.back().first;
                if(t > N){
                    st.back().first -= N;
                    N = 0;
                }else{
                    N -= t;
                    st.pop_back();
                }
            }
        }else if(q == "Top"){
            if(sz == 0){
                std::cout << "EMPTY" << std::endl;
                return;
            }
            std::cout << st.back().second << '\n';
        }else{
            std::cout << sz << '\n';
        }
    }

    std::cout << "SAFE" << std::endl;

    return;
}

int main(){
    solve();

    return 0;
}