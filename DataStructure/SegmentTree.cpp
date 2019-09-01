#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

template<typename T, typename U>
class SegmentTree{
    int n;
    vector<T> node;

    using F = function<T(T, T)>;
    using G = function<T(T, U)>;

    F f;
    G g;
    T en;

public:
    SegmentTree(int n_, F f_, G g_, T en_){
        init(n_, f_, g_, en_);
    }

    SegmentTree(const vector<T>& dat, F f_, G g_, T en_){
        build(dat, f_, g_, en_);
    }

    void init(int n_, F f_, G g_, T en_){
        n = 1;
        while(n < n_){
            n <<= 1;
        }
        f = f_;
        g = g_;
        en = en_;

        node.resize(n << 1);
        fill(node.begin(), node.end(), en);

        return;
    }

    void build(const vector<T>& dat, F f_, G g_, T en_){
        int n_ = (int)dat.size();

        init(n_, f_, g_, en_);

        for(int i = 0 ; i < n_ ; ++i){
            node[i + n] = dat[i];
        }

        for(int i = n - 1 ; 0 < i ; --i){
            node[i] = f(node[i << 1], node[(i << 1) | 1]);
        }

        return;
    }

    void update(int k, U x){
        k += n;
        node[k] = g(node[k], x);

        while(k >>= 1){
            node[k] = f(node[k << 1], node[(k << 1) | 1]);
        }

        return;
    }

    T get(int l, int r){
        l += n;
        r += n;

        T res = en;
        while(l < r){
            if(l & 1){
                res = f(res, node[l++]);
            }
            l >>= 1;
            if(r & 1){
                res = f(res, node[--r]);
            }
            r >>= 1;
        }

        return res;
    }
};

/*

verify:https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/DSL_2_A/judge/3842253/C++14
       https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/DSL_2_B/judge/3842259/C++14
       https://atcoder.jp/contests/abc127/submissions/7244283

*/
