#include<bits/stdc++.h>
using namespace std;
const int mxn = 1e5+5;
/*
   Undirected graph:
      all even degree -> Eulerian circuit
      exactly two node odd degree -> Eulerian path
      start from an odd degree node
   Directed graph:
      all nodes in-degree and out-degree are equal -> Eulerian circuit
      One nodes out-degree > in-degree and One node in-degree > out-degree -> Eulerian path
      start from the node where out-degree > in-degree

*/
vector<int> g[mxn], edge_no[mxn];
vector<int> deg,nodes_ord, ecount, vis_edge;
int start_node(int n) {
    for(int i=1; i<=n; i++) {
        if(deg[i]&1) return i;
    }
    return 1;
}
void eulerian_path(int u) {
    for(int &i = ecount[u]; i<g[u].size(); i++) {
        int v = g[u][i], e = edge_no[u][i];
        if(vis_edge[e]==0) {
            vis_edge[e] = 1;
            eulerian_path(v);
        }
    }
    nodes_ord.push_back(u);
}


int32_t main() {
    int n, m;
    cin >> n >> m;
    ecount = deg = vector<int>(n+1);
    vis_edge = vector<int>(m);
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >>v;
        g[u].push_back(v);
        g[v].push_back(u);
        edge_no[u].push_back(i);
        edge_no[v].push_back(i);
        deg[u]++;
        deg[v]++;
    }
    int odd = 0;
    for(int i=1; i<=n; i++) odd += (deg[i]&1);
    if(odd!=0 && odd!=2){
            // odd == 0 Eulerian circuit.
            // odd == 2 Eulerian Path.
        cout << "IMPOSSIBLE";
        return 0;
    }
    eulerian_path(start_node(n));
    for(int i=0; i<m; i++){
        if(vis_edge[i] == 0){
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    while(nodes_ord.size()) cout << nodes_ord.back() <<" ", nodes_ord.pop_back();


}
