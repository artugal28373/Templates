
//! https://codeforces.com/problemset/problem/600/E
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
vector<int> g[maxn];
int color[maxn], big[maxn];
int freq[maxn], sz[maxn], mxc[maxn];
long long  bsum[maxn];
int getsz(int u, int p) {
    sz[u] = 1;
    int mx = 0;
    for(int &x: g[u]) {
        if(x!=p) {
            sz[u]+=getsz(x, u);
            if(sz[x]>mx) {
                mx = sz[x];
                big[u] = x;//Bigclid
            }
        }
    }
    return sz[u];
}
void add(int node, int p,int v,  int&mx, long long &sum) {  //Add function
    freq[color[node]]+=v;

    if(freq[color[node]]>mx) {
        mx = freq[color[node]];
        sum = 0;
    }
    if(freq[color[node]] == mx) {
        sum+=color[node];
    }
    for(int&x: g[node]) {
        if(x!=p && (big[node]!=x)) add(x, node, v, mx, sum);
    }

}

void dfs(int n, int p, int keep) {
    int bigchild = big[n], mx = -1;

    for(int &x: g[n]) {
        if(x!=p && x!=bigchild) {
            dfs(x, n, 0);
        }
    }
    long long sum = 0;
    mx = 0;
    if(bigchild) {
        dfs(bigchild, n, 1);
        mx = mxc[bigchild], sum = bsum[bigchild];//Big child information
    }
    add(n, p, 1, mx, sum);
    mxc[n] = mx;
    bsum[n] = sum;
    big[n] = 0;// N is done;
    if(keep==0) {
        int mx;
        long long sum;
        add(n, p, -1,mx, sum);
    }
    return;
}




int main() {
    int n;
    cin >> n;
    for(int i=1; i<=n; i++) cin >> color[i];
    int u,v;
    for(int i=1; i<n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    getsz(1, 0);
    dfs(1, 0, 1);//! 1 means Bigchild ) means Light child
    for(int i=1; i<=n; i++) cout << bsum[i]<<" ";

}





































