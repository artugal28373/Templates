#include<bits/stdc++.h>
using namespace std;
const int mxn = 2e5+5;
vector<int> g[mxn], rg[mxn], dTree[mxn], bucket[mxn];
int dsu[mxn], who[mxn], dfsTime[mxn], label[mxn];
int  idom[mxn], sdom[mxn], par[mxn];
int timer = 0;
/*
   find a undirected tree of a directed graph with a source.
   where for each node u all it ancestor v are dominator node.
   that means removing one of these node v disconnected u form source.

   g -> orginal graph, rg -> reverse graph
   dTree -> dominator tree, bucket -> nodes with 'sdom' equal i

   dfsTime ->  reach time while running dfs, who -> nodes with dfsTime with i
   par -> keep parent of ith node in dfs tree.

   idom -> deepest dominator node of i.(it is an ancestor of node i in dfs tree)
   sdom -> the furthest node that can reach node i in a alternative path
           using only nodes that's reach later than i.(sdom is also ancestor of i).

   label -> keep the label of minimum sdom from root to v in forest.

   complexity -> O((n+m)lg(n+m))

   sdom(w)  = min of v, (v, w), v<w or sdom(u), u > w and (v, w), u is anc of v.

   all cross & back edge node's sdom calculated previously and froward edge
   sdom is v itself.

*/

// run dfs with source node.
void dfs0(int u) {
    ++timer;
    dfsTime[u] = timer, who[timer] = u;
    label[timer] = timer, dsu[timer] = timer;
    sdom[timer] = timer, idom[timer] = timer;

    for(int &v: g[u]) {
        if(!dfsTime[v]) {
            dfs0(v);
            par[dfsTime[v]]=dfsTime[u];
        }
        rg[dfsTime[v]].push_back(dfsTime[u]);
    }

}
int Find(int u, int x=0) {
    // if only one node the result is root.
    // otherwise root is not consider in query.
    // (root, v] minimum sdom among these nodes.
    // x positive mean more than one node.
    if(u==dsu[u]) return (x ? -1 : u);
    int v = Find(dsu[u], x+1);
    // determine last node is root and not considered.
    if(v < 0) return u;

    //label track which node is minimum sdom for (root, u].
    if(sdom[label[dsu[u]]] < sdom[label[u]])
        label[u] = label[dsu[u]];

    dsu[u] = v;// path compression
    // if x == 0 then we return node that has minimum sdom form (root, u].
    //else return current root node to compress path.
    // v is root node.
    return (x? v : label[u]);
}
void Union(int u,int v) {
    // v was root some tree and now it merge with tree that
    // contains node u.
    // here u is parent and v is child.
    dsu[v] = u;
}
void dominatorTreeBuild(int root, int n) {
    for(int i=0; i<=n; i++) {
        rg[i].clear();
        dTree[i].clear();
        bucket[i].clear();
    }
    timer = 0;
    dfs0(root);
    n = timer;
    for(int i=n; i>=1; i--) {
        for(int &x: rg[i]) {
            // find minimum sdom for node i
            // mainly for forward, cross and back edges.
            sdom[i] = min(sdom[i], sdom[Find(x)]);
        }

        if(i > 1) bucket[sdom[i]].push_back(i);

        for(int &w: bucket[i]) {
            // find minimum sdom for (sdom(w), w].
            int v = Find(w);
            //  sdom for nodes (sdom(w), w) is less than sdom(w)
            //  then idom[w] = u, u is the node of minimum node.
            // other wise sdom(w) is idom(w)
            if(sdom[w] == sdom[v]) idom[w] = sdom[w];
            else idom[w] = v;// it is nt real idom....it just keep the
            // node that find idom...the idom(v) is idom(w) now.
            // since idom is calculated when we process the corresponding
            // sdom, the sdom is not processed yet bcz less.
        }

        if(i > 1) Union(par[i], i);
    }
    // calculate idom of not calculated idom.
    for(int i=2; i<=n; i++) {
        // later case.
        if(sdom[i]!=idom[i]) idom[i] = idom[idom[i]];
//        dTree[ who[i] ].push_back( who[ idom[i] ] );
//        dTree[ who[ idom[i] ] ].push_back(who[i]);
    }
    memset(par, -1, sizeof par);
    par[root] = root;
    for(int i=2; i<=n; i++)
        par[ who[i] ] = who[ idom[i] ];
}

int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);

    int s, n, m;
    cin >>  n >> m >> s;
    for(int i=1; i<=m; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    dominatorTreeBuild(s, n);

    for(int i=0; i<n; i++) {
        cout << par[i] << " ";
    }
}
