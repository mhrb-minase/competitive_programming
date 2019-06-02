#include<vector>
#include<algorithm>
#include<climits>
#include<utility>

class UnionFind{
    template<typename T>
    using vector = std::vector<T>;

    vector<int> par;
    vector<long long> wei;
    int groupCount;

public:
    void init(int n = 0){
        par.resize(n);
        fill(par.begin(), par.end(), -1);

        wei.resize(n);
        fill(wei.begin(), wei.end(), 0LL);

        groupCount = n;

        return;
    }

    UnionFind(int n = 0){
        init(n);
    }

    int root(int x){
        if(par[x] < 0){
            return x;
        }
        int r = root(par[x]);
        wei[x] += wei[par[x]];
        return par[x] = r;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }

    int size(int x){
        return -par[root(x)];
    }

    long long weight(int x){
        root(x);
        return wei[x];
    }

    long long diff(int x, int y){
        if(!same(x, y)){
            return LLONG_MIN;
        }
        return weight(y) - weight(x);
    }

    bool unite(int x, int y, long long w = 0){
        w += weight(x) - weight(y);

        x = root(x);
        y = root(y);

        if(x == y){
            return false;
        }

        if(size(x) < size(y)){
            std::swap(x, y);
            w = -w;
        }

        par[x] += par[y];
        par[y] = x;
        wei[y] = w;
        --groupCount;

        return true;
    }

    int number_of_group(void){
        return groupCount;
    }
};
