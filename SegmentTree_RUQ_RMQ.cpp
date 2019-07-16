#include<vector>
#include<limits>
using namespace std;

// 区間更新区間max
template<class T>
class SegmentTree{
    int n;
    vector<T> node, upd;
    vector<bool> flag;

    void evaluate(int k, int l, int r){
        if(flag[k]){
            node[k] = upd[k];
            flag[k] = false;
            if(r - l > 1){
                upd[k * 2 + 1] = upd[k];
                flag[k * 2 + 1] = true;
                upd[k * 2 + 2] = upd[k];
                flag[k * 2 + 2] = true;
            }
        }
        return;
    }

    void update(int a, int b, int k, int l, int r, T x){
        evaluate(k, l, r);
        if(b <= l || r <= a){
            return;
        }
        if(a <= l && r <= b){
            upd[k] = x;
            flag[k] = true;
            evaluate(k, l, r);
            return;
        }

        update(a, b, k * 2 + 1, l, (l + r) / 2, x);
        update(a, b, k * 2 + 2, (l + r) / 2, r, x);

        node[k] = max(node[k * 2 + 1], node[k * 2 + 2]);

        return;
    }

    T get(int a, int b, int k, int l, int r){
        evaluate(k, l, r);
        if(b <= l || r <= a){
            return numeric_limits<T>::min();
        }
        if(a <= l && r <= b){
            return node[k];
        }

        T vl = get(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = get(a, b, k * 2 + 2, (l + r) / 2, r);

        return max(vl, vr);
    }

public:
    // 要素数または配列でコンストラクト
    SegmentTree(int siz = 0){
        init(siz);
    }

    SegmentTree(const vector<T> v){
        build(v);
    }

    // 指定された要素数で初期化
    void init(int siz){
        n = 1;
        while(n < siz){
            n <<= 1;
        }

        node.resize(n * 2 - 1);
        fill(node.begin(), node.end(), numeric_limits<T>::min());

        upd.resize(n * 2 - 1);

        flag.resize(n * 2 - 1);
        fill(flag.begin(), flag.end(), false);

        return;
    }

    // 指定された配列で初期化
    void build(const vector<T> v){
        init((int)v.size());

        for(int i = 0, i_len = (int)v.size() ; i < i_len ; ++i){
            node[i + n - 1] = v[i];
        }

        for(int i = n - 2 ; i >= 0 ; --i){
            node[i] = max(node[i * 2 + 1], node[i * 2 + 2]);
        }

        return;
    }

    // [a, b)をxに更新
    void update(int a, int b, T x){
        update(a, b, 0, 0, n, x);
        return;
    }

    // [a, b)の取得
    T get(int a, int b){
        return get(a, b, 0, 0, n);
    }
};
