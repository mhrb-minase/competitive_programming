template<typename Cost>
struct Edge{
    int u, v;
    Cost cost;

    bool operator<(const Edge& rhs) const {
        return cost < rhs.cost;
    }
};