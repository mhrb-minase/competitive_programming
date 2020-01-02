#include<vector>
#include<algorithm>
#include<functional>

template<typename T>
class LazySegmentTree{
    int n;
    std::vector<T> node;
    std::vector<T> lazy;
    std::vector<int> length;
    int height;

    using F = std::function<T(T, T)>;
    using S = std::function<T(T, int)>;

    F f;
    F g;
    F h;
    S s;
    T id1;
    T id2;

    void evaluate(int k){
        if(lazy[k] == id2){
            return;
        }

        node[k] = g(node[k], s(lazy[k], length[k]));

        if(k < n){
            lazy[k << 1] = h(lazy[k << 1], lazy[k]);
            lazy[(k << 1) | 1] = h(lazy[(k << 1) | 1], lazy[k]);
        }

        lazy[k] = id2;

        return;
    }

    void evaluate(int l, int r){
        for(int i = height ; 0 < i ; --i){
            evaluate(l >> i);
            evaluate(r >> i);
        }

        return;
    }

public:
    LazySegmentTree(int n_, F f_, F g_, F h_, T id1_, T id2_, S s_ = [](T x, int len){ return x; }){
        init(n_, f_, g_, h_, id1_, id2_, s_);
    }

    LazySegmentTree(std::vector<T>& dat, F f_, F g_, F h_, T id1_, T id2_, S s_ = [](T x, int len){ return x; }){
        build(dat, f_, g_, h_, id1_, id2_, s_);
    }

    void init(int n_, F f_, F g_, F h_, T id1_, T id2_, S s_ = [](T x, int len){ return x; }){
        n = 1;
        height = 0;
        while(n < n_){
            n <<= 1;
            ++height;
        }

        f = f_;
        g = g_;
        h = h_;
        id1 = id1_;
        id2 = id2_;
        s = s_;

        node.assign(n << 1, id1);
        lazy.assign(n << 1, id2);

        length.assign(n << 1, 1);
        fill(length.begin() + n + n_, length.end(), 0);
        for(int i = n - 1 ; 0 < i ; --i){
            length[i] = length[i << 1] + length[(i << 1) | 1];
        }

        return;
    }

    void build(std::vector<T>& dat, F f_, F g_, F h_, T id1_, T id2_, S s_ = [](T x, int len){ return x; }){
        int n_ = (int)dat.size();

        init(n_, f_, g_, h_, id1_, id2_, s_);

        for(int i = 0 ; i < n_ ; ++i){
            node[i + n] = dat[i];
        }
        for(int i = n - 1 ; 0 < i ; --i){
            node[i] = f(node[i << 1], node[(i << 1) | 1]);
        }

        return;
    }

    void update(int l, int r, T x){
        l += n;
        r += n - 1;

        int L = l;
        int R = r;

        evaluate(l, r);

        ++r;

        while(l < r){
            if(r & 1){
                --r;
                lazy[r] = h(lazy[r], x);
            }
            r >>= 1;

            if(l & 1){
                lazy[l] = h(lazy[l], x);
                ++l;
            }
            l >>= 1;
        }

        while(L >>= 1, R >>= 1, L){
            evaluate(L << 1);
            evaluate((L << 1) | 1);
            node[L] = f(node[L << 1], node[(L << 1) | 1]);

            evaluate(R << 1);
            evaluate((R << 1) | 1);
            node[R] = f(node[R << 1], node[(R << 1) | 1]);
        }

        return;
    }

    T get(int l, int r){
        l += n;
        r += n - 1;

        evaluate(l, r);

        ++r;

        T res = id1;
        while(l < r){
            if(r & 1){
                --r;
                evaluate(r);
                res = f(res, node[r]);
            }
            r >>= 1;

            if(l & 1){
                evaluate(l);
                res = f(res, node[l]);
                ++l;
            }
            l >>= 1;
        }

        return res;
    }
};

/*

verify:https://onlinejudge.u-aizu.ac.jp/recent_judges/DSL_2_G/judge/4085400/mhrb_minase/C++14
       https://onlinejudge.u-aizu.ac.jp/recent_judges/DSL_2_G/judge/4085401/mhrb_minase/C++14
       https://onlinejudge.u-aizu.ac.jp/recent_judges/DSL_2_H/judge/4085402/mhrb_minase/C++14
       https://onlinejudge.u-aizu.ac.jp/recent_judges/DSL_2_I/judge/4085403/mhrb_minase/C++14
       https://atcoder.jp/contests/abc128/submissions/9281982
       https://atcoder.jp/contests/past201912-open/submissions/9282099

*/
