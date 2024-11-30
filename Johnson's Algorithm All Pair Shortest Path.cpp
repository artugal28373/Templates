#include<bits/stdc++.h>
using namespace std;
const int mxn = 2e5+5;
// https://vjudge.net/problem/Gym-101498L
// https://brilliant.org/wiki/johnsons-algorithm/
// v^2log(v) + V*E
#define int long long
const int inf = LLONG_MAX/2;
bellmenford(int n, int s, vector<vector<int>>& edges, vector<int> &d) {
    d = vector<int>(n+1, inf);
    d[s] = 0;
    for(int i=0; i<=n; i++) {
        int flag = 0;
        for(vector<int> &e: edges) {
            if(d[e[0]]+e[2]<d[e[1]]) {
                flag = 1;
                d[e[1]] = d[e[0]]+e[2];
            }
        }
        if(flag == 0) return 1; // no negative cycle
    }
    return 0; // has negative cycle
}
void dijkstra(int n, int s, vector<vector<int>> &edges, vector<int> &h, vector<int> &d) {
    vector<pair< int, int>> g[n+1];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    for(vector<int> &e: edges) {
        // weight re-weighted to remove negative weight by adding h[u]-h[v]
        g[ e[0] ].push_back({ e[1], e[2]+h[ e[0] ] - h[ e[1] ] });
    }
    d = vector<int>(n+1, inf);
    vector<int> vis(n+1, 0);
    q.push({0, s});
    d[s] = 0;
    while(!q.empty()) {
        int w = q.top().first;
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(pair<int, int> &v: g[u]) {
            if(d[u]+v.second < d[v.first]) {
                d[v.first] = d[u]+v.second;
                q.push({d[v.first], v.first });
            }
        }
    }
    for(int i=1; i<=n; i++) {
        if(d[i]!=inf)
            // remove re-weight let's s->i a path is s->u->v->i = h[s]-h[u]+h[u]-h[v]+h[v]-h[i] = h[s]-h[i]
            d[i]-=h[s]-h[i];
    }
}
vector<vector<int>> d;
int johnson(int n, vector<vector<int>> edges) {
    for(int i=1; i<=n; i++) edges.push_back({0, i, 0});
    vector<int> potential;
    int flag = bellmenford(n, 0, edges, potential);
    if(flag == 0) return 0;
    for(int i=1; i<=n; i++) edges.pop_back();
    d.assign(n+1, {});
    for(int i=1; i<=n; i++) {
        dijkstra(n, i, edges, potential, d[i]);
    }
    return 1;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        int mn = inf;
        for(int i=0; i<m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            edges.push_back({u, v, c});
            mn = min(mn, c);

        }
        // find the shortest path among all possible pairs
        for(int i=1; i<=n; i++) edges.push_back({0, i, 0});
        vector<int> d;
        int flag = bellmenford(n, 0, edges, d);
        if(flag == 0) {
            cout <<"-inf\n";
            continue;
        }
        for(int i=1; i<=n; i++) {
            if(d[i]<0)
                mn = min(mn, d[i]);
        }
        cout << mn<<"\n";
    }
}
