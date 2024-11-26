#include<bits/stdc++.h>
using namespace std;

int32_t main() {

    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<set<int>> g(n);
    for(int i=0; i<m; i++) {
        int a, b;
        cin >> a>> b;
//        a--, b--;
        g[a].insert(b);
        g[b].insert(a);
    }
    set<int> unused;
    for(int i=0; i<n; i++) {
        unused.insert(i);
    }
    int c = 0;
    vector<vector<int>> connected;
    while(!unused.empty()) {
        c++;
        connected.emplace_back();
        queue<int> q;
        q.push(*unused.begin());
        unused.erase(q.front());
        vector<int> deleted;
        while(!q.empty()) {
            int u = q.front();
            connected.back().push_back(u);
            q.pop();
            // since forbidden edges are not more than m, it quickly reduces size of unused
            for(const int &x: unused) {
                if(g[u].count(x)==0) {
                    q.push(x);
                    deleted.push_back(x);
                }
            }
            for(int &x: deleted) unused.erase(x);
        }
    }
    cout << c <<"\n";
    for(vector<int> &vec: connected){
        cout << vec.size() << " ";
        for(int &x: vec) cout << x << " ";
        cout << "\n";
    }
}
