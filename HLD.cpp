#include<bits/stdc++.h>
using namespace std;
// a
#define int long long
const int mxn = 3e5+2;
long long segmentTree[4*mxn];
long long lxy[4*mxn];
const long long mod = (119<<23)+1;
// 0 based
vector<int> g[mxn];
int parent[mxn], chain_head[mxn], sx[mxn];
int start[mxn], finish[mxn], big[mxn], height[mxn];
int timer, numberOfNode;
#define Left u*2+1
#define Right Left+1
void prop(int u, int l, int r) {
    if(lxy[u]==-1) return;
    lxy[Left]=lxy[u];
    lxy[Right]=lxy[u];
    int m = (l+r)/2;
    segmentTree[Left]=((m-l+1)*lxy[u])%mod;
    segmentTree[Right]=((r-m)*lxy[u])%mod;
    lxy[u] = -1;
}
void upd(int u, int l, int r,  int s, int t, long long vl) {
    if(s<=l && r<=t) {
        lxy[u] = vl;
        segmentTree[u] = (vl*(r-l+1))%mod;
        return;
    }
    if(r<s || t<l) return;
    int m = (l+r)/2;
    prop(u, l, r);
    upd(Left,l, m, s, t, vl);
    upd(Right,m+1, r, s, t, vl);
    segmentTree[u] = (segmentTree[Left]+segmentTree[Right])%mod;
}
long long _segmentreeF(int u, int l, int r, int s, int t) {
    if(s<=l && r<=t) return segmentTree[u];
    if(r<s || t<l) return 0ll;
    int m = (l+r)/2;
    prop(u, l, r);
    return (_segmentreeF(Left, l, m, s, t)+_segmentreeF(Right, m+1, r, s, t))%mod;
}
#undef Right
#undef Left
void constructor(int n) {
    for(int i=0; i<=n; i++) {
        g[i].clear();
        big[i] = -1;
        height[i] = 0;
    }
    for(int i=0; i<=4*n; i++) segmentTree[i] = 0, lxy[i] = -1;
    timer=0;
    numberOfNode = n;
}
void destructor(int n) {
    for(int i=0; i<=n; i++) {
        g[i].clear();
    }
}
void dfs0(int u, int p) {
    sx[u]=1;
    for(int &x: g[u]) {
        if(x^p) {
            dfs0(x, u);
            sx[u]+=sx[x];
            if(big[u]==-1) big[u] = x;
            if(sx[x]>sx[big[u]]) big[u] = x;
        }
    }
}
void decompose(int u, int p, int chainHead,  int lvl) {
    parent[u] = p;
    chain_head[u] = chainHead;
    height[u] = lvl;
    start[u] = timer++;
    if(~big[u]) {
        decompose(big[u], u, chainHead, lvl+1);
    }
    for(int &x: g[u]) {
        if(x^big[u]) {
            if(x^p) {
                decompose(x, u, x, lvl+1);
            }
        }
    }
    finish[u] = timer;
}

int lca(int u, int v) {
    while(chain_head[u]^chain_head[v]) {
        if(height[chain_head[u]] > height[chain_head[v]]) {
            swap(u, v);
        }
        v = chain_head[v];
        v = parent[v];
    }
    if(height[u]>height[v]) swap(u, v);
    return u;
}
long long _HLDF(int u, int v) {
    long long sum = 0;
    while(chain_head[u]^chain_head[v]) {
        if(height[chain_head[u]] > height[chain_head[v]]) {
            swap(u, v);
        }
        sum= (sum+_segmentreeF(0, 0, numberOfNode,start[chain_head[v]], start[v]))%mod;
        v = chain_head[v];
        v = parent[v];
    }
    if(height[u]>height[v]) swap(u, v);
    sum=(sum+_segmentreeF(0, 0, numberOfNode, start[u], start[v]))%mod;
    return sum;
}
void _HLDU(int u, int v, long long vl) {
    while(chain_head[u]^chain_head[v]) {
        if(height[chain_head[u]] > height[chain_head[v]]) {
            swap(u, v);
        }
        upd(0, 0, numberOfNode,start[chain_head[v]], start[v], vl);
        v = chain_head[v];
        v = parent[v];
    }
    if(height[u]>height[v]) swap(u, v);
    upd(0, 0, numberOfNode, start[u], start[v], vl);
}

int32_t main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for(int tc=0; tc<t; tc++) {
        string b, c;
        cin >> b >> c;
        int nb = b.length();
        int nc = c.length();
        b = "#"+b+"#"+c;
        vector<int> kmp(b.length()+10);
        int node = 0;
        kmp[1] = node;
        for(int i=2; i<b.length(); i++) {
            while(node && b[node+1]!=b[i]) node = kmp[node];
            if(b[node+1]==b[i]) node++;
            kmp[i] = node;
        }
        constructor(nb);
        for(int i=1; i<=nb; i++) {
            g[kmp[i]].push_back(i);
        }
        dfs0(0, 0);
        decompose(0, 0, 0, 0);
        for(int i=b.length()-1; nc; i--, nc--) {
            long long sum = (segmentTree[0]+1)%mod;
            _HLDU(0, kmp[i], sum);
            _HLDU(0, 0, 0);
        }
        cout << segmentTree[0]<<"\n";
        destructor(nb);
    }


}


// a


















