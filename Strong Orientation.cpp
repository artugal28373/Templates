#include<bits/stdc++.h>
using namespace std;
const int mxn = 1e5+5;
vector<pair<int, int>> g[mxn], edges;
vector<int> low, disc;
int timer = 0;
int bridge = 0;
// can have any bridge in graph
// edges.first -> edges.second
void dfs(int u, int edno) {
    low[u] = disc[u] = ++timer;
    for(pair<int, int> &e: g[u]) {

        if(e.second != edno) {
            if(disc[e.first] == 0) {
                if(u ^ edges[e.second].first) swap(edges[e.second].first, edges[e.second].second);
                dfs(e.first, e.second);
                low[u] = min(low[u],low[e.first]);
                if(low[e.first] > disc[u]) {
                    bridge++;
                }
            } else {
             // disc[u] < disc[v] means forward edge
                if(disc[u] < disc[e.first]) continue;
                low[u] = min(low[u], disc[e.first]);
                if(u ^ edges[e.second].first) swap(edges[e.second].first, edges[e.second].second);
            }
        }
    }
}

int32_t main() {
    int n, m;
    cin >> n >> m;
    low = disc = vector<int>(n+1);
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    int forest = 0;
    for(int i=1; i<=n; i++) {
        if(disc[i] == 0) {
            forest++;
            dfs(i, -1);
        }
    }
    if(forest>1|| bridge>0) cout << "IMPOSSIBLE";
    else {
        for(auto &x: edges) {
            cout << x.first << " " << x.second << "\n";
        }
    }
}
