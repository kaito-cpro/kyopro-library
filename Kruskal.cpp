#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class Cap>
class Kruskal {
public:
    struct edge {
        int from, to;
        Cap cost;
    };

    Kruskal(int n) : N(n) {}

    void add_edge(int _from, int _to, Cap _cost) {
        G.push_back(edge{_from, _to, _cost});
        G.push_back(edge{_to, _from, _cost});
    }

    Cap kruskal() {
        MST_G.clear();
        sort(G.begin(), G.end(), [](edge& l, edge& r) {
            return l.cost < r.cost;
        });
        dsu uf(N);
        Cap mincost = 0;
        for (edge e : G) {
            if (uf.same(e.from, e.to)) continue;
            uf.merge(e.from, e.to);
            MST_G.push_back(e);
            mincost += e.cost;
        }
        return mincost;
    }
    
    vector<edge> MST() {
        kruskal();
        return MST_G;
    }

    vector<vector<edge>> edges() { return G; }

    void set_inf(Cap inf) { INF = inf; }
    Cap get_inf() { return INF; }

private:
    int N;
    Cap INF = numeric_limits<Cap>::max() / 2;
    vector<edge> G;
    vector<edge> MST_G;
};

int main() {
    int N;  cin >> N;
    Kruskal<int> g(N);
    g.add_edge(0, 1, 10);
    int mincost = g.kruskal();  // 最小全域木の最小コスト和
    auto mst_g = g.MST();       // 最小全域木の辺の集合 (from, to, cost)
}
