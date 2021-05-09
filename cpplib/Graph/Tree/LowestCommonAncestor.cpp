class LowestCommonAncestor{
    int V;
    int n;
    std::vector< std::vector<int> > graph;
    std::vector< std::vector<int> > parent;
    std::vector<int> depth;

    void dfs(int v, int p, int d){
        parent[0][v] = p;
        depth[v] = d;

        for(auto u : graph[v]){
            if(u != p){
                dfs(u, v, d + 1);
            }
        }

        return;
    }

    void init(const std::vector< std::vector<int> >& graph_, int root = 0){
        V = (int)graph_.size();
        for(int i = 30 ; i >= 0 ; --i){
            if(V >> i & 1){
                n = i + 1;
                break;
            }
        }
        graph = graph_;
        parent.assign(n, std::vector<int>(V, -1));
        depth.resize(V);

        dfs(root, -1, 0);

        for(int i = 0 ; i < n - 1 ; ++i){
            for(int v = 0 ; v < V ; ++v){
                if(parent[i][v] != -1){
                    parent[i + 1][v] = parent[i][parent[i][v]];
                }
            }
        }

        return;
    }

public:
    LowestCommonAncestor(const std::vector< std::vector<int> >& graph_, int root = 0){
        init(graph_, root);
    }

    int lca(int u, int v){
        if(depth[u] < depth[v]){
            std::swap(u, v);
        }

        for(int i = 0 ; i < n ; ++i){
            if((depth[u] - depth[v]) >> i & 1){
                u = parent[i][u];
            }
        }

        if(u == v){
            return u;
        }

        for(int i = n - 1 ; i >= 0 ; --i){
            if(parent[i][u] != parent[i][v]){
                u = parent[i][u];
                v = parent[i][v];
            }
        }

        return parent[0][u];
    }

    int dist(int u, int v){
        int l = lca(u, v);
        return depth[u] + depth[v] - depth[l] * 2;
    }
};