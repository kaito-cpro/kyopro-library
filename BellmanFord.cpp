#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class Cap>
class Bellman_Ford {
public:
    struct edge {
        int from, to;
        Cap cost;
    };

    Bellman_Ford(int n) : N(n) {
        prev.resize(n);
        fill(prev.begin(), prev.end(), -1);
    }

    void add_edge(int _from, int _to, Cap _cost) {
        G.push_back(edge{_from, _to, _cost});
    }

    vector<Cap> bellman_ford(int s) {
        vector<Cap> d(N, INF);
        d[s] = 0;
        fill(prev.begin(), prev.end(), -1);
        while (true) {
            bool update = false;
            for (edge e : G) {
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    prev[e.to] = e.from;
                    update = true;
                }
            }
            if (!update) break;
        }
        return d;
    }
    
    // グラフの中に負の閉路があるか(頂点 s から到達可能かどうかは関係なく)
    bool find_negative_loop() {
        vector<Cap> d(N, 0);
        int cnt = 0;
        while (++cnt) {
            bool update = false;
            for (edge e : G) {
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;
            if (cnt == N) return true;  // 負の閉路あり
        }
        return false;
    }
    
    // 頂点 s から到達可能な負の閉路があるか
    bool find_negative_loop(int s) {
        vector<Cap> d(N, INF);
        d[s] = 0;
        int cnt = 0;
        while (++cnt) {
            bool update = false;
            for (edge e : G) {
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;
            if (cnt == N) return true;  // 頂点 s から到達可能な負の閉路あり
        }
        return false;
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

    vector<edge> edges() { return G; }

    void set_inf(Cap inf) { INF = inf; }
    Cap get_inf() { return INF; }

private:
    int N;
    Cap INF = numeric_limits<Cap>::max() / 2;
    vector<edge> G;
    vector<int> prev;
};

int main() {
    int N;  cin >> N;
    int s;  cin >> s;  // 始点
    Bellman_Ford<int> g(N);
    auto d = g.bellman_ford(s);
}
