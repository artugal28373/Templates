#include<bits/stdc++.h>
using namespace std;
const int mxn = 2e5+4;
vector<pair<int, int>> g[mxn];
vector<int> blockTree[2*mxn];
int isCut[mxn],low[mxn], disc[mxn], timer = 0;
int atComponent[mxn], iatComponent[mxn];
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
                        iatComponent[ components.size() ] = stk.back();
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
                iatComponent[ components.size() ] = stk.back();
                stk.pop_back();
            }
        } else {
            stk.clear();
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
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    for(int i=1; i<=n; i++) {
        if(disc[i] == 0) {
            dfs(i, -1);
        }
    }
    cout << components.size() << "\n";
    for(auto &x: components) {
        cout << x.size() << " ";
        for(int &y: x) {
            cout << y - 1<< " ";
        }
        cout << "\n";
    }

}
