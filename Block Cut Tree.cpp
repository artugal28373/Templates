// problem -> https://cses.fi/problemset/task/1705/

#include<bits/stdc++.h>
using namespace std;
const int mxn = 1e5+4;
vector<pair<int, int>> g[mxn];
vector<int> blockTree[2*mxn];
int isCut[mxn],low[mxn], disc[mxn], timer = 0;
int atComponent[mxn];
vector<int> stk;
vector<vector<int>> components;
void dfs(int u, int edno) {
    low[u] = disc[u] = ++timer;
    stk.push_back(u);
    int child = 0;
    for(pair<int, int> &e: g[u]) {
        if(e.second != edno) {
            if(disc[e.first] == 0) {
                child++;
                dfs(e.first, e.second);
                if(low[e.first]>=disc[u]) {
//                    isCut[u] = (disc[u] > 1 || disc[e.first]>2);
                    isCut[u] = (edno != -1 || child != 1);
                    components.push_back({u});
                    while(components.back().back() != e.first) {
                        components.back().push_back(stk.back());
                        atComponent[ stk.back() ] = components.size();
                        stk.pop_back();
                    }
                }
                low[u] = min(low[u],low[e.first]);
            } else {
                low[u] = min(low[u], disc[e.first]);
            }
        }
    }
    if(edno==-1) {
        // care full about single node graph
        if(child == 0) {
            components.push_back({});
            while(stk.size()) {
                components.back().push_back(stk.back());
                atComponent[ stk.back() ] = components.size();
                stk.pop_back();
            }
        } else {
            stk.clear();
        }
    }
}
void buildTree(int n) {
    int curNode = components.size();
    for(int i=1; i<=n; i++) {
        if(isCut[i]) {
            atComponent[i] = ++curNode;
        }
    }

    for(int i=0; i<components.size(); i++) {
        for(int &x: components[i]) {
            if(isCut[x]) {
                    // add edge between a cut vertex and a component
                blockTree[ atComponent[x] ].push_back( i+1 );
                blockTree[i+1].push_back( atComponent[x] );
            }
        }
    }

}
int sp[20][2*mxn];
int height[2*mxn];
void buildDfs(int u, int p) {
    sp[0][u]=p;
    for(int i=0; i<18; i++) {
        if(sp[i][u]==-1) sp[i+1][u]=-1;
        else sp[i+1][u] = sp[i][ sp[i][u] ];
    }
    for(int &x: blockTree[u]) {
        if(x!=p) {
            height[x] = height[u]+1;
            buildDfs(x, u);
        }
    }
}

int lca_query(int u, int v) {
    if(height[u] > height[v]) swap(u, v);
    for(int i=18; i>=0; i--) {
        if(height[v] - (1<<i) >= height[u]) v = sp[i][v];
    }
    if(u==v) return u;
    for(int i=18; i>=0; i--) {
        if(sp[i][u] != sp[i][v]) v= sp[i][v], u = sp[i][u];
    }
    return sp[0][u];
}



int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m, q;
    cin >> n >> m >> q;
    for(int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
//        u++, v++;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    for(int i=1; i<=n; i++) {
        if(disc[i] == 0) {
            dfs(i, -1);
        }
    }
    buildTree(n);
    buildDfs(1, -1);
    while(q--) {
        int a, b, c;
        cin >> a>> b >> c;
        if(a==c || b==c) {
            cout << "NO\n";
            continue;
        }
        if(isCut[c] == 0) {
            cout << "YES\n";
            continue;
        }
        a = atComponent[a];
        b = atComponent[b];
        c = atComponent[c];

        int lca = lca_query(a, b);
        int lca1 = lca_query(a, c);
        int lca2 = lca_query(b, c);
        // c is on the path a and b;
        if((lca==c) || (lca1==lca && lca2==c) || (lca2==lca && lca1==c)) {
            cout << "NO\n";
        } else cout << "YES\n";
    }

}
