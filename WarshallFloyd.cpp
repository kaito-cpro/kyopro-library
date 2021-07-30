#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

template <class Cap>
class Warshall_Floyd {
public:
    Warshall_Floyd(int n) : N(n) {
        d.resize(n, vector<Cap>(n, INF));
        for (int i = 0; i < n; ++i) d[i][i] = 0;
        prev.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; ++i) prev[i][i] = i;
    }

    void add_edge(int from, int to, Cap cost) {
        if (d[from][to] > cost) {
            d[from][to] = cost;
            prev[from][to] = from;
        }
    }

    vector<vector<Cap>> warshall_floyd() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) prev[i][j] = i;
                else prev[i][j] = -1;
            }
        }
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (d[i][k] != INF && d[k][j] != INF && d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        prev[i][j] = prev[k][j];
                    }
                }
            }
        }
        return d;
    }

    vector<int> min_path(int s, int t) {
        vector<int> path{t};
        while (0 <= t && t < N && s != t) {
            path.push_back(prev[s][t]);
            t = prev[s][t];
        }
        if (t < 0 || t >= N) return vector<int>();
        reverse(path.begin(), path.end());
        return path;
    }

    vector<vector<Cap>> edges() { return d; }

    void set_inf(Cap inf) { INF = inf; }
    Cap get_inf() { return INF; }

private:
    int N;
    Cap INF = numeric_limits<Cap>::max() / 2;
    vector<vector<Cap>> d;
    vector<vector<int>> prev;  // prev[i][j] := i から j への最短経路において, j のひとつ前
};

int main() {
    int N;  cin >> N;
    Warshall_Floyd<int> g(N);
    auto d = g.warshall_floyd();
}
