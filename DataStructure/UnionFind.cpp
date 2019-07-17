#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

class UnionFind{
    vector<int> par;
    vector<long long> wei;
    int groupCount;

public:
    UnionFind(int n = 0){
        init(n);
    }

    // n要素で初期化
    void init(int n = 0){
        par.resize(n);
        fill(par.begin(), par.end(), -1);

        wei.resize(n);
        fill(wei.begin(), wei.end(), 0LL);

        groupCount = n;

        return;
    }

    // xが属する集合の根を求める
    int root(int x){
        if(par[x] < 0){
            return x;
        }
        int r = root(par[x]);
        wei[x] += wei[par[x]];
        return par[x] = r;
    }

    // xとyが同じ集合に属するか調べる
    bool same(int x, int y){
        return root(x) == root(y);
    }

    // xが属する集合の大きさを調べる
    int size(int x){
        return -par[root(x)];
    }

    // xの根との重みの差を調べる
    long long weight(int x){
        root(x);
        return wei[x];
    }

    // xとyの重みの差を調べる
    long long diff(int x, int y){
        return weight(y) - weight(x);
    }

    // xが属する集合とyが属する集合を、xとyの重みの差がwになるように繋げる
    // 既に繋がっていた場合はfalseを返す
    bool unite(int x, int y, long long w = 0){
        w += weight(x) - weight(y);

        x = root(x);
        y = root(y);

        if(x == y){
            return false;
        }

        if(par[y] < par[x]){
            swap(x, y);
            w = -w;
        }

        par[x] += par[y];
        par[y] = x;
        wei[y] = w;
        --groupCount;

        return true;
    }

    // 集合の個数を調べる
    int size(void){
        return groupCount;
    }
};

/*

verify:https://atcoder.jp/contests/abc120/submissions/6417856
      :https://atcoder.jp/contests/abc126/submissions/6417867
      :https://atcoder.jp/contests/abc087/submissions/6417899

*/
