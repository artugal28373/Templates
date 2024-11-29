
///////////////////////
#include<bits/stdc++.h>
using namespace std;
const int mxn = 2e5+4;
vector<int> g[mxn], bridgeTree[mxn];
int componentID[mxn], icomponentID[mxn];
int low[mxn], disc[mxn];
int isBridge[mxn*10];
struct oneEdge {
    int ed1, ed2;
    oneEdge(int e1=0, int e2=0): ed1(e1), ed2(e2) {}
    int ed(int u) {
        return u^ed1^ed2;
    }
};
vector<oneEdge> edges, bedges;
int timer = 0;
void dfs(int u, int edno) {
    disc[u] = low[u] = ++timer;
    for(int &x: g[u]) {
        int v = edges[x].ed(u);
        if(x!=edno) {
            if(disc[v] == 0) {
                dfs(v, x);
                low[u] = min(low[u], low[v]);
                if(disc[u] < low[v]) isBridge[x] = 1;
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
}
void dfs1(int u, int edno, int c) {
    componentID[u] = c;
    icomponentID[c] = u;
    for(int &x: g[u]) {
        int v = edges[x].ed(u);
        if(x!=edno) {
            if(componentID[v]==0 && isBridge[x]==0) {
                dfs1(v, x, c);
            }
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        g[u].push_back(i);
        g[v].push_back(i);
        edges.push_back(oneEdge(u, v));
    }

    for(int i=1; i<=n; i++) {
        if(disc[i] == 0) {
            dfs(i, -1);
        }
    }
    int c = 0;
    for(int i=1; i<=n; i++) {
        if(componentID[i]==0) {
            dfs1(i, -1, ++c);
        }
    }
//    for(int i=0; i<m; i++) {
//        if(isBridge[i]==1) {
//            bridgeTree[ componentID[edges[i].ed1] ].push_back(bedges.size());
//            bridgeTree[ componentID[edges[i].ed2] ].push_back(bedges.size());
//            bedges.push_back(edges[i]);
//        }
//    }
    vector<vector<int>> g(c+1);
    for(int i=1; i<=n; i++) {
        g[ componentID[i] ].push_back(i);
    }
    cout << c<< "\n";
    for(int i=1; i<=c; i++) {
        cout << g[i].size() << " ";
        for(int &x: g[i]) cout << x- 1 << " ";
        cout << "\n";
    }

}
