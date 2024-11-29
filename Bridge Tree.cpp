#include<bits/stdc++.h>
using namespace std;
const int mxn = 2e5+4;
vector<pair<int, int>> g[mxn];
vector<int> bridgeTree[mxn];
int componentID[mxn], icomponentID[mxn];
int low[mxn], disc[mxn];
int isBridge[mxn];
int timer = 0, c=0;
vector<int> stk;
void dfs(int u, int edno) {
    stk.push_back(u);
    low[u] = disc[u] = ++timer;
    for(pair<int, int> &e: g[u]) {
        if(e.second != edno) {
            if(disc[e.first] == 0) {
                int track = timer;
                dfs(e.first,e.second);
                // e.first = node, e.second = edge number
                if(low[e.first] > disc[u]) {
                    isBridge[ e.second ] = 1;
                    c++;
                    //track =  dfs time before going e.first
                    // all elements after track is under same component
                    while( disc[stk.back()] > track) {
                        componentID[ stk.back() ] = c;
                        icomponentID[ c ] = stk.back();
                        stk.pop_back();
                    }
                }
                low[u] = min(low[u], low[e.first]);
            } else {
                low[u] = min(low[u], disc[e.first]);
            }
        }
    }
    if(edno == -1) {
        // rest of the element are all in same component group
        c++;
        while(!stk.empty()) {
            componentID[stk.back()] = c;
            icomponentID[c] = stk.back();
            stk.pop_back();
        }
    }
}

int d[2][mxn];
pair<int, int> dfs2(int u, int p, int w) {
    pair<int, int> mx = {d[w][u], u};
    for(int &v: bridgeTree[u]) {
        if(v!=p) {
            d[w][v]=d[w][u]+1;
            mx = max(dfs2(v, u, w), mx);
        }
    }
    return mx;
}
int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    for(int i=1; i<=n; i++) {
        if(disc[i] == 0) {
            dfs(i, -1);
        }
    }
//    cout << c<< endl;
    for(int i=1; i<=n; i++) {
        for(pair<int, int> &e: g[i]) {
            if(isBridge[e.second] == 1) {
                bridgeTree[ componentID[i] ].push_back(componentID[e.first]);
            }
        }
    }

    int mx = 0, cx=1, cy=1;
    for(int i=1; i<=c; i++) {
        if(d[0][i] == 0) {
            pair<int, int> a = dfs2(i, i, 0);
            pair<int, int> b = dfs2(a.second, a.second, 1);
            if(b.first+1>mx) {
                mx = b.first+1;
                cy = a.second;
                cx = b.second;
            }
        }
    }
    cout << icomponentID[cx] << " " << icomponentID[cy];

}









//#include<bits/stdc++.h>
//using namespace std;
//const int mxn = 2e5+4;
//vector<int> g[mxn], bridgeTree[mxn];
//int componentID[mxn], icomponentID[mxn];
//int low[mxn], disc[mxn];
//int isBridge[mxn];
//struct oneEdge {
//    int ed1, ed2;
//    oneEdge(int e1=0, int e2=0): ed1(e1), ed2(e2) {}
//    int ed(int u) {
//        return u^ed1^ed2;
//    }
//};
//vector<oneEdge> edges, bedges;
//int timer = 0;
//void dfs(int u, int edno) {
//    disc[u] = low[u] = ++timer;
//    for(int &x: g[u]) {
//        int v = edges[x].ed(u);
//        if(x!=edno) {
//            if(disc[v] == 0) {
//                dfs(v, x);
//                low[u] = min(low[u], low[v]);
//                if(disc[u] < low[v]) isBridge[x] = 1;
//            } else {
//                low[u] = min(low[u], disc[v]);
//            }
//        }
//    }
//}
//void dfs1(int u, int edno, int c) {
//    componentID[u] = c;
//    icomponentID[c] = u;
//    for(int &x: g[u]) {
//        int v = edges[x].ed(u);
//        if(x!=edno) {
//            if(componentID[v]==0 && isBridge[x]==0) {
//                dfs1(v, x, c);
//            }
//        }
//    }
//}
//int d[2][mxn];
//pair<int, int> dfs2(int u, int p, int w) {
//    pair<int, int> mx = {d[w][u], u};
//    for(int &x: bridgeTree[u]) {
//        int v = bedges[x].ed(u);
//        if(v!=p) {
//            d[w][v]=d[w][u]+1;
//            mx = max(dfs2(v, u, w), mx);
//        }
//    }
//    return mx;
//}
//int main() {
////    freopen("input.txt", "r", stdin);
////    freopen("output.txt", "w", stdout);
//    int n, m;
//    cin >> n >> m;
//    for(int i=0; i<m; i++) {
//        int u, v;
//        cin >> u >> v;
//        g[u].push_back(i);
//        g[v].push_back(i);
//        edges.push_back(oneEdge(u, v));
//    }
//
//    for(int i=1; i<=n; i++) {
//        if(disc[i] == 0) {
//            dfs(i, -1);
//        }
//    }
//    int c = 0;
//    for(int i=1; i<=n; i++) {
//        if(componentID[i]==0) {
//            dfs1(i, -1, ++c);
//        }
//    }
//    for(int i=0; i<m; i++) {
//        if(isBridge[i]==1) {
//            bridgeTree[ componentID[edges[i].ed1] ].push_back(bedges.size());
//            bridgeTree[ componentID[edges[i].ed2] ].push_back(bedges.size());
//            bedges.push_back(oneEdge(componentID[ edges[i].ed1 ], componentID[ edges[i].ed2 ]));
//        }
//    }
//    int mx = 0, cx=1, cy=1;
//    for(int i=1; i<=c; i++){
//        if(d[0][i] == 0){
//            pair<int, int> a = dfs2(i, i, 0);
//            pair<int, int> b = dfs2(a.second, a.second, 1);
//            if(b.first+1>mx){
//                mx = b.first+1;
//                cy = a.second;
//                cx = b.second;
//            }
//        }
//    }
//    cout << icomponentID[cx] << " " << icomponentID[cy];
//
//}
