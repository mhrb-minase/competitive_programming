#include<vector>
#include<algorithm>
using namespace std;

// 辺を表す構造体
struct edge{
    int from, to;
    long long cost;
};

// v:=頂点数 es:=辺の集合 cost:=始点からの最短経路のコストを格納する配列
// s:=始点(指定しなければ頂点0) g:=終点(指定しなければ頂点v-1)
// 始点から到達可能で、かつ終点へ到達可能な負閉路が検出された場合falseを、それ以外の場合trueを返す
bool bellman_ford(int v, const vector<edge>& es, vector<long long>& cost, int s = 0, int g = -1){
    if(g == -1){
        g = v - 1;
    }

    const long long INF = 1LL << 61;

    cost.resize(v);
    fill(cost.begin(), cost.end(), INF);
    cost[s] = 0;

    for(int i = 0 ; i < v * 2 ; ++i){
        for(auto& e : es){
            if(cost[e.from] < INF && cost[e.from] + e.cost < cost[e.to]){
                if(i >= v - 1 && e.to == g){
                    return false;
                }else if(i >= v - 1){
                    cost[e.to] = -INF;
                }else{
                    cost[e.to] = cost[e.from] + e.cost;
                }
            }
        }
    }

    return true;
}

/*

verify:https://atcoder.jp/contests/abc137/submissions/7028138

*/
