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

class UnionFind{
    using Weight = long long;

    int n;
    std::vector<int> par;
    std::vector<Weight> weight;
    int siz;

public:
    UnionFind(int n_ = 0){
        init(n_);
    }

    void init(int n_ = 0){
        n = n_;
        par.assign(n, -1);
        weight.assign(n, 0);
        siz = n;
        return;
    }

    int find(int x){
        if(par[x] < 0){
            return x;
        }
        int root = find(par[x]);
        weight[x] += weight[par[x]];
        return par[x] = root;
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    Weight get_weight(int x){
        find(x);
        return weight[x];
    }

    bool unite(int x, int y, Weight w = 0){
        w += get_weight(x) - get_weight(y);

        x = find(x);
        y = find(y);

        if(x == y){
            return false;
        }

        if(par[x] < par[y]){
            std::swap(x, y);
            w = -w;
        }

        par[x] += par[y];
        par[y] = x;
        weight[y] = w;
        --siz;

        return true;
    }

    Weight diff(int x, int y){
        return get_weight(y) - get_weight(x);
    }

    int size_of_set(int x){
        return -par[find(x)];
    }

    int count_set(void){
        return siz;
    }
};

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(m), b(m);
    for(int i = 0 ; i < m ; ++i){
        std::cin >> a[i] >> b[i];
        --a[i];
        --b[i];
    }

    UnionFind uf(n);
    std::vector<long long> ans(m);
    ans[m - 1] = (long long)n * (n - 1) / 2;

    for(int i = m - 1 ; i > 0 ; --i){
        int sa = uf.size_of_set(a[i]);
        int sb = uf.size_of_set(b[i]);

        ans[i - 1] = ans[i];

        if(uf.unite(a[i], b[i])){
            ans[i - 1] -= (long long)sa * sb;
        }
    }

    for(int i = 0 ; i < m ; ++i){
        std::cout << ans[i] << std::endl;
    }

    return 0;
}