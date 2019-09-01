#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

template<typename T, typename U>
class LazySegmentTree{
    int n;
    int height;
    vector<T> node;
    vector<U> lazy;
    vector<int> len;

    using F = function<T(T, T)>;
    using G = function<T(T, U)>;
    using H = function<U(U, U)>;
    using S = function<U(U, int)>;

    F f;
    G g;
    H h;
    S s;
    T en;
    U el;

    void evaluate(int k){
        if(lazy[k] == el){
            return;
        }

        if(k < n){
            lazy[k << 1] = h(lazy[k << 1], lazy[k]);
            lazy[(k << 1) | 1] = h(lazy[(k << 1) | 1], lazy[k]);
        }

        node[k] = g(node[k], s(lazy[k], len[k]));
        lazy[k] = el;

        return;
    }

    void evaluate(int l, int r){
        for(int i = height ; 0 < i ; --i){
            evaluate(l >> i);
            evaluate(r >> i);
        }

        return;
    }

    void update(int k){
        evaluate(k << 1);
        evaluate((k << 1) | 1);
        node[k] = f(node[k << 1], node[(k << 1) | 1]);
        return;
    }

public:
    LazySegmentTree(int n_, F f_, G g_, H h_, S s_, T en_, U el_){
        init(n_, f_, g_, h_, s_, en_, el_);
    }

    LazySegmentTree(const vector<T>& dat, F f_, G g_, H h_, S s_, T en_, U el_){
        build(dat, f_, g_, h_, s_, en_, el_);
    }

    void init(int n_, F f_, G g_, H h_, S s_, T en_, U el_){
        n = 1;
        height = 0;
        while(n < n_){
            n <<= 1;
            ++height;
        }
        f = f_;
        g = g_;
        h = h_;
        s = s_;
        en = en_;
        el = el_;

        node.resize(n << 1);
        fill(node.begin(), node.end(), en);
        lazy.resize(n << 1);
        fill(lazy.begin(), lazy.end(), el);
        len.resize(n << 1);
        fill(len.begin() + n, len.begin() + n + n_, 1);
        fill(len.begin() + n + n_, len.end(), 0);
        for(int i = n - 1 ; 0 < i ; --i){
            len[i] = len[i << 1] + len[(i << 1) | 1];
        }

        return;
    }

    void build(const vector<T>& dat, F f_, G g_, H h_, S s_, T en_, U el_){
        int n_ = (int)dat.size();

        init(n_, f_, g_, h_, s_, en_, el_);

        for(int i = 0 ; i < n_ ; ++i){
            node[i + n] = dat[i];
        }

        for(int i = n - 1 ; 0 < i ; --i){
            node[i] = f(node[i << 1], node[(i << 1) | 1]);
        }

        return;
    }

    void update(int l, int r, U x){
        l += n;
        r += n - 1;

        evaluate(l, r);

        int tl = l;
        int tr = r;

        ++r;
        while(l < r){
            if(l & 1){
                lazy[l] = h(lazy[l], x);
                evaluate(l++);
            }
            l >>= 1;
            if(r & 1){
                lazy[--r] = h(lazy[r], x);
                evaluate(r);
            }
            r >>= 1;
        }

        while(tl >>= 1, tr >>= 1, tl){
            if(lazy[tl] == el){
                update(tl);
            }
            if(lazy[tr] == el){
                update(tr);
            }
        }

        return;
    }

    T get(int l, int r){
        l += n;
        r += n - 1;

        evaluate(l, r);

        T res = en;
        ++r;
        while(l < r){
            if(l & 1){
                evaluate(l);
                res = f(res, node[l++]);
            }
            l >>= 1;
            if(r & 1){
                evaluate(--r);
                res = f(res, node[r]);
            }
            r >>= 1;
        }

        return res;
    }
};

/*

verify:https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/DSL_2_F/judge/3842338/C++14
       https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/DSL_2_G/judge/3842425/C++14
       https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/DSL_2_H/judge/3842434/C++14
       https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/DSL_2_I/judge/3842439/C++14
       https://atcoder.jp/contests/abc128/submissions/7245420

*/
