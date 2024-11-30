#include<bits/stdc++.h>
using namespace std;
const int mxn = 5e3+5;
int d[mxn];
int vis[mxn];
vector<pair<int, int>>  g[mxn];
bool spfa(int u) {
    vis[u] = 1;
    for (pair<int, int> &e : g[u]) {
        if (d[u] + e.second < d[e.first]) {
            if (vis[e.first]) return false; // Negative cycle detected
            d[e.first] = d[u] + e.second;
            if (!spfa(e.first)) return false;
        }
    }
    vis[u] = 0;
    return true;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
}
