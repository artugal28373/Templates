vector<vector<int>>g, vg;
int st[mxn], ed[mxn], height[mxn];
int sp[20][mxn];
int importantOrg[mxn], importantVirtual[mxn];
int timer = 0;
int rnk[mxn];
void dfs(int u, int p=0, int h=0) {
    st[u] = ++timer;
    sp[0][u] = p;
    height[u] = h;
    for(int i=1; i<20; i++) sp[i][u] = sp[i-1][sp[i-1][u]];
    for(int &x: g[u]) if(x^p) dfs(x, u, h+1);
    ed[u] = timer;
}
bool dfs_time_compare(const int u, const int v) {
    return st[u]<st[v];
}
int is_anc(int u, int v) {
    return st[u]<=st[v] && ed[v]<=ed[u];
}
void virtulConstruction(vector<int>&orgNodes) {
    for(int &x: orgNodes) importantOrg[x]=1;
    int n = orgNodes.size();
    sort(begin(orgNodes), end(orgNodes), dfs_time_compare);
    for(int i=1; i<n; i++) {
        orgNodes.push_back(sp[0][orgNodes[i]]);
    }
    n = orgNodes.size();
    sort(begin(orgNodes), end(orgNodes), dfs_time_compare);
    for(int i=1; i<n; i++) {
        orgNodes.push_back(find_lca(orgNodes[i-1], orgNodes[i]));
    }
    sort(begin(orgNodes), end(orgNodes), dfs_time_compare);
    orgNodes.resize(unique(begin(orgNodes), end(orgNodes))-begin(orgNodes));
    vg.clear();
    vg.resize(orgNodes.size()+1);
    vector<int> s;
    s.push_back(0);
    n = orgNodes.size();
    for(int i=1; i<n; i++) {
//    cout << "Debug"<<endl;
//        cout << orgNodes[i] <<" vge "<<orgNodes[s.back()]<<endl;
        while(is_anc(orgNodes[s.back()], orgNodes[i])==0) s.pop_back();
        vg[s.back()+1].push_back(i+1);
        vg[i+1].push_back(s.back()+1);
        s.push_back(i);
    }
    for(int i=0; i<n; i++) {
        importantVirtual[i+1] = importantOrg[orgNodes[i]];
//        cout << orgNodes[i]<<" -> "<<i+1<<endl;
    }
}
