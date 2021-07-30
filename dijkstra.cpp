#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class Cap>
class Dijkstra {
public:
    struct edge {
        int to;
        Cap cost;
    };

    Dijkstra(int n) : N(n) {
        G.resize(n);
        prev.resize(n);
        fill(prev.begin(), prev.end(), -1);
    }

    void add_edge(int _from, int _to, Cap _cost) {
        G[_from].push_back(edge{_to, _cost});
    }

    vector<Cap> dijkstra(int s) {
        vector<Cap> d(N, INF);
        d[s] = 0;
        fill(prev.begin(), prev.end(), -1);
        using P = pair<Cap, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.push(P(0, s));
        while (!que.empty()) {
            P p = que.top();  que.pop();
            int i = p.second;
            if (d[i] < p.first) continue;
            for (edge e : G[i]) {
                if (d[e.to] > d[i] + e.cost) {
                    d[e.to] = d[i] + e.cost;
                    prev[e.to] = i;
                    que.push(P(d[e.to], e.to));
                }
            }
        }
        return d;
    }

    vector<int> min_path(int s, int t) {
        vector<int> path{t};
        while (0 <= t && t < N && s != t) {
            path.push_back(prev[t]);
            t = prev[t];
        }
        if (t < 0 || t >= N) return vector<int>();
        reverse(path.begin(), path.end());
        return path;
    }

    vector<vector<edge>> edges() { return G; }

    void set_inf(Cap inf) { INF = inf; }
    Cap get_inf() { return INF; }

private:
    int N;
    Cap INF = numeric_limits<Cap>::max() / 2;
    vector<vector<edge>> G;
    vector<int> prev;
};

int main() {
    int N;  cin >> N;
    int s;  cin >> s;  // 始点
    Dijkstra<int> g(N);
    g.add_edge(0, 1, 10);
    auto dist = g.dijkstra(s);
    auto edges = g.edges();
    int t = N - 1;
    auto min_path = g.min_path(s, t);

    // ループがないグラフの最長経路を求めたいときは,
    // add_edge() の cost をすべて負にして, inf は触らなくて ok
    // dijkstra() で受け取った dist をすべて符号反転すれば最長経路になる
    // 到達不可能な頂点の dist は -INF になる
}
