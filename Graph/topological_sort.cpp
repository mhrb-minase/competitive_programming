#include<vector>
using namespace std;

bool topological_sort(const vector< vector<int> >& g, vector<int>& res){
    const int v = (int)g.size();
    res.clear();

    vector<int> deg(v, 0);
    for(int i = 0 ; i < v ; ++i){
        for(auto to : g[i]){
            ++deg[to];
        }
    }

    vector<int> st;
    for(int i = 0 ; i < v ; ++i){
        if(deg[i] == 0){
            st.emplace_back(i);
        }
    }

    while(!st.empty()){
        int k = st.back();
        st.pop_back();
        res.emplace_back(k);
        for(auto to : g[k]){
            --deg[to];
            if(deg[to] == 0){
                st.emplace_back(to);
            }
        }
    }

    return (int)res.size() == v;
}

/*

verify:https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/GRL_4_B/judge/3847231/C++14
       https://atcoder.jp/contests/nikkei2019-qual/submissions/7331843
       https://atcoder.jp/contests/abc139/submissions/7331888

*/
