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

/*
verify
https://atcoder.jp/contests/abc120/submissions/14630147
https://atcoder.jp/contests/abc126/submissions/14630074
https://atcoder.jp/contests/arc090/submissions/14630041
*/