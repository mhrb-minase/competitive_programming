#include<iostream>
#include<vector>
using namespace std;

template<class T>
class BinaryIndexedTree{
    int n;
    vector<T> bit;

public:
    BinaryIndexedTree(int _n = 0){
        init(_n);
    }

    BinaryIndexedTree(const vector<T> &v){
        build(v);
    }

    void init(int _n = 0){
        n = _n;
        bit.clear();
        bit.resize(n + 1);
        return;
    }

    void build(const vector<T> &v){
        int _n = v.size();
        init(_n);

        for(int i = 0 ; i < _n ; ++i){
            add(i + 1, v[i]);
        }

        return;
    }

    bool add(int i, T x){
        if(i <= 0 || n < i){
            return false;
        }

        while(i <= n){
            bit[i] += x;
            i += i & -i;
        }

        return true;
    }

    bool update(int i, T x){
        T _x = x - sum(i - 1, i);
        return add(i, _x);
    }

    T sum(int i){
        T s = T(0);
        while(i > 0){
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    T sum(int l, int r){
        return sum(r) - sum(l);
    }

    int lower_bound(T x){
        int i = 1, res = 0;
        while((i << 1) <= n){
            i <<= 1;
        }

        while(i > 0){
            if(res + i <= n && bit[res + i] < x){
                x -= bit[res + i];
                res += i;
            }
            i >>= 1;
        }

        return res + 1;
    }

    int upper_bound(T x){
        int i = 1, res = 0;
        while((i << 1) <= n){
            i <<= 1;
        }

        while(i > 0){
            if(res + i <= n && bit[res + i] <= x){
                x -= bit[res + i];
                res += i;
            }
            i >>= 1;
        }

        return res + 1;
    }
};

int main(){
    BinaryIndexedTree<int> bit(10);
    bit.add(2, 1);
    bit.add(5, 1);
    cout << bit.sum(1) << " " << bit.sum(3) << " " << bit.sum(5) << " " << bit.sum(1, 4) << " " << bit.sum(2, 3) << endl;
    cout << bit.lower_bound(1) << " " << bit.upper_bound(1) << endl;

    vector<int> a = {1, 3, 7, 2};
    BinaryIndexedTree<int> bit2(a);
    cout << bit2.sum(2, 4) << endl;
    cout << bit2.lower_bound(4) << " " << bit2.upper_bound(4) << endl;
    bit2.update(1, 5);
    cout << bit2.sum(4) << endl;
    return 0;
}
