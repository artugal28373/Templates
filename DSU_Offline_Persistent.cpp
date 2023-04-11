#include<bits/stdc++.h>

using namespace std;

const int mxn = (1e5)+5;
vector<int> p, sx,
beingf[mxn], // time to be f
childof[mxn], // father of ith at time j
beingc[mxn], // time to be child of i father
sixeof[mxn], // sixe of connected component of ith at time j
fatherof[mxn]; // father of ith at time j
int n;
void DSU(int _n) {
    n = _n;
    p = vector<int>(_n+2, 0);
    sx = vector<int>(_n+2, 1);
    for(int i=1; i<=_n; i++) p[i] = i;
    for(int i=1; i<=n; i++) {
        beingf[i].push_back(0);
        childof[i].push_back(i);
        fatherof[i].push_back(i);
        beingc[i].push_back(0);
        sixeof[i].push_back(1);
        sx[i] = 1;
    }
}
int f(int c) {
    if(c==p[c]) return c;
    return p[c] = f(p[c]);
}
int cl(int f, int t) {
   return sixeof[f][upper_bound(beingf[f].begin(), beingf[f].end(), t) - beingf[f].begin()-1]; 
  // find the sixe of f less or eual time and close to time m 
  // last changed has been already recorded.
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m;
    cin >> n >> m;
    DSU(n);
    for(int i=1; i<=m; i++) {
        int u, v;
        cin >> u >> v;
        int c = f(u), d = f(v);
        if(c==d) continue;
        if(sx[c]<sx[d]) swap(c, d);
        p[d] = c;
        sx[c] = sx[c]+sx[d];
        beingf[c].push_back(i); // c has been expanded at time i
        sixeof[c].push_back(sx[c]); // c has been expanded at time i with sixe sx[c]
        for(int j=0; j<childof[d].size(); j++){
            int e = childof[d][j];
            childof[c].push_back(e); // keep track child after ith time
            beingc[e].push_back(i); // e has been child of c at time i
            fatherof[e].push_back(c); // e hsa been child of c at time i
        }
        childof[d].clear();
    }
    int p;
    cin >> p;
    while(p--){
        int x, y, w;
        cin >> x >> y >> w;
        int l = 1, h = m;
        int res = 0;

        while(l<=h){
            int m = (l+h)/2;
            int xf = fatherof[x][upper_bound(beingc[x].begin(), beingc[x].end(), m ) - beingc[x].begin() - 1]; 
           // find time less tan or equal and close to time m which has been father of x 
            int yf = fatherof[y][upper_bound(beingc[y].begin(), beingc[y].end(), m ) - beingc[y].begin() - 1];
            int tot = cl(xf, m);
            if(xf^yf) tot = tot + cl(yf, m);
            if(tot >= w) res = m, h = m-1;
            else l = m+1;
        }
        cout << res<<"\n";
    }

}


