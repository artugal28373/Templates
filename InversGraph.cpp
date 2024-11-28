#include<bits/stdc++.h>
using namespace std;

// https://judge.yosupo.jp/problem/connected_components_of_complement_graph
// choose random two nodes and if there are no forbidden and join them using some ds.
// can choose one that has less number of forbidden edges; 

int32_t main() {

    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<vector<int>> g(n);
    for(int i=0; i<m; i++) {
        int a, b;
        cin >> a>> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> adj(n);
    vector<int> unused;
    for(int i=0; i<n; i++) {
        unused.push_back(i);
    }
    int c = 0;
    vector<vector<int>> connected;
    while(!unused.empty()) {
        c++;
        connected.emplace_back();
        queue<int> q;
        q.push(unused.back());
        unused.pop_back();
        while(!q.empty()) {
            int u = q.front();
            connected.back().push_back(u);
            vector<int>nxt_it;
            q.pop();
            for(int &x: g[u]) {
                adj[x]=1;
            }
            // since forbidden edges are not more than m, it quickly reduces size of unused
            for(int &x: unused) {
                if(adj[x]==0) {
                    q.push(x);
                } else {
                    nxt_it.push_back(x);
                }
            }
            unused = nxt_it;
            for(int &x: g[u]) {
                adj[x]=0;
            }
        }
    }
    cout << c <<"\n";
    for(vector<int> &vec: connected) {
        cout << vec.size() << " ";
        for(int &x: vec) cout << x << " ";
        cout << "\n";
    }
}
