// let's we have N forest
//  for each forest find mimimum distance other forest traversing each edge
//  join each forest with its neasrest forest
// average iteration log(E) times
// complexity O(Elog(E))
// It takes more time than other spanning tree algorithms.
#include<bits/stdc++.h>
using namespace std;
const int mxn = 2e5+5;
vector<pair<int, int>> g[mxn];
vector<vector<int>> edges;
int dsu[mxn];
int findp(int u) {
    if(dsu[u]<0)return u;
    return dsu[u]=findp(dsu[u]);
}
bool join(int u, int v) {
    u = findp(u), v = findp(v);
    if(u==v)return 0;
    if(dsu[u]>dsu[v]) swap(u, v);
    dsu[u]+=dsu[v];
    dsu[v]=u;
    return 1;
}
vector<int> spaningTree;
void boruvka(int n, vector<vector<int>> &edges) {
    for(int i=1; i<=n; i++) {
        dsu[i]=-1;
    }
    int cnt = n-1;
    vector<int> used(edges.size());
    int it = 40;
    while(cnt) {
        if(it==0) assert(0);
        it--;
        vector<int> e(n+1, -1);
        for(int i=0; i<edges.size(); i++) {
            if(used[i]) continue;
            int u=edges[i][0], v = edges[i][1], w = edges[i][2];
            u = findp(u);
            v = findp(v);
            if(u==v) {
                used[i]=1;
            }
          // Find the nearest forest for forest u and forest v
            if(e[u] == -1 || edges[ e[u] ][2] > w) e[u] = i;
            if(e[v] == -1 || edges[ e[v] ][2] > w) e[v] = i;
        }
        for(int i=1; i<=n; i++) {
            if(e[i]!=-1) {
              // add each forest with its nearest forest
                if(join( edges[ e[i] ][0], edges[ e[i] ][1] )) {
                    spaningTree.push_back(e[i]);
                    used[ e[i] ] = 1 ;
                    cnt--;
                }
            }
        }
    }
}
int32_t main() {
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u++, v++;
        edges.push_back({u, v, c});
    }
    boruvka(n, edges);
    long long sum = 0;
    for(int &x: spaningTree) sum += edges[x][2];
    cout << sum << "\n";
    for(int &x: spaningTree) cout << x<< " ";

}
