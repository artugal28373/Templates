#include<bits/stdc++.h>
using namespace std;
const int mxn = 155;
int d[mxn][mxn];
const int inf = 1e7;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q;
    while (cin >> n >> m >> q) {
        if (!n && !m && !q) return 0;

        // Initialize distance matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = (i == j ? 0 : inf);
            }
        }

        // Read edges
        for (int i = 0; i < m; i++) {
            int u, v, a;
            cin >> u >> v >> a;
            d[u][v] = min(d[u][v], a);
        }

        // Floyd-Warshall: Shortest paths
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (d[i][k] < inf && d[k][j] < inf) {
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    }
                }
            }
        }

        // Detect and propagate negative cycles
        for (int k = 0; k < n; k++) {
            if (d[k][k] < 0) { // Node k is in a negative cycle
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (d[i][k] < inf && d[k][j] < inf) {
                            d[i][j] = -inf;
                        }
                    }
                }
            }
        }

        // Handle queries
        while (q--) {
            int u, v;
            cin >> u >> v;
            if (d[u][v] == -inf) cout << "-Infinity\n";
            else if (d[u][v] == inf) cout << "Impossible\n";
            else cout << d[u][v] << "\n";
        }
        cout << "\n";
    }
}
