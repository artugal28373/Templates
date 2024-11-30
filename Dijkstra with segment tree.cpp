// https://codeforces.com/contest/786/problem/B
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mxn = 1e5+5;
int n, s;
vector<pair<int, int>> g[9*mxn];
void add_edge(int u, int v, int w) {
    g[u].push_back({v, w});
//    cout << u << " " << v<< " "<<w<<"  \n";
}
int type2, type3;
void build(int u, int l, int r) {
    if(l==r) {
         add_edge(u+type2, l, 0);
         add_edge(l, u+type3, 0);
    } else {
        int m=(l+r)/2;
        add_edge(u+type2, u*2+type2, 0);
        add_edge(u+type2, u*2+1+type2, 0);
        add_edge(u*2+type3, u+type3, 0);
        add_edge(u*2+1+type3, u+type3, 0);
        build(u*2, l,m);
        build(u*2+1, m+1, r);
    }
}
void update(int u, int l, int r, int s, int t, int v, int w, int type) {
    if(s<=l && r<=t) {
        if(type<=2) add_edge(v, u+type2, w);
        else add_edge(u+type3, v, w);
        return;
    }
    if(r<s || t<l) return;
    int m = (l+r)/2;
    update(u*2, l, m, s, t, v, w, type);
    update(u*2+1, m+1, r, s, t, v, w, type);
}

int d[9*mxn];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> n >> q >> s;
    type3 = 5*n;
    type2 = n;
    build(1, 1, n);
    while(q--) {
        int op;
        cin >> op;
        if(op==1) {
            int u, v, w;
            cin >> u >> v >> w;
            add_edge(u, v, w);
        } else {
            if(op==2) {
                int u, l, r, w;
                cin >> u >> l >> r >> w;
                update(1, 1, n, l, r, u, w, 2);
            } else {
                int l, r, u, w;
                cin >> u >> l >> r >> w;
                update(1, 1, n, l, r, u, w, 3);
            }
        }
    }
    for(int i=0; i<=9*n; i++) {
        d[i] = LLONG_MAX;
    }
    d[s]=0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    while(!pq.empty()) {
        int  u= pq.top().second;
        int  w = pq.top().first;
        pq.pop();
        if(d[u] != w) continue;
        for(pair<int, int> &x: g[u]) {
            int v = x.first,we = x.second;
            if(w+we < d[v]) {
                d[v]=w+we;
                pq.push({d[v], v});
            }
        }
    }
    for(int i=1; i<=n; i++) {
        if(d[i] == LLONG_MAX) d[i] = -1;
        cout << d[i] << " ";
    }
}
