#include<bits/stdc++.h>
using namespace std;
const int mxn = (2e4)+5;
template<int Sixe=mxn>
struct segmentTree {
    int segment[4*Sixe+4];
//    int lxy[4*Sixe+4];
//    int mxi[4*Sixe+4];
//    bool mut[4*Sixe+4];
//    void mutt() {
//        mut[0] = 1;
//        mxi[0] = lxy[0] = 0;
//        segment[0] = Sixe;
//    }
//    void p(int u, int l, int r) {
//        int lft = u*2+1, rgt = u*2+2;
//        if(mut[u]) {
//            mxi[lft] = 0, mxi[rgt] = 0;
//            lxy[lft] = lxy[rgt] = 0;
//            segment[lft] = ((l+r)/2 - l+1);
//            segment[rgt] = (r - (l+r)/2);
//        }
//        mxi[lft]+=lxy[u];
//        mxi[rgt]+=lxy[u];
//        lxy[lft]+=lxy[u];
//        lxy[rgt]+=lxy[u];
//        mut[lft] = mut[u];
//        mut[rgt] = mut[u];
//        mut[u] = 0;
//        lxy[u] = 0;
//        return;
//    }
    void updt(int u, int s, int t, int v, bool pointupdt=0, int l= 0, int r = Sixe-1) {
        if(t<l || r<s) return;
        if(s<=l && r<=t) {
            if(pointupdt) {
                segment[u]  = v;
            } else {
                segment[u] = v;
            }
            return;
        }
//        p(u, l,r);
        int m = (l+r)/2;
        updt(u*2+1,s, t, v, pointupdt, l, m);
        updt(u*2+2,s, t, v, pointupdt, m+1, r);
        int lft = u*2+1;
        int rgt = lft+1;
        segment[u] =  max(segment[lft], segment[rgt]);
    }
    int _find(int u, int s, int t, int l = 0, int r = Sixe-1) {
        if(s<=l && r<=t) return segment[u];
        if(t<l || r<s) return -1;
//        p(u, l, r);
        int m = (l+r)/2;
        auto c = _find(u*2+1, s, t, l, m);
        auto d = _find(u*2+2, s, t, m+1, r);
        return max(c, d);
    }
};
vector<int> g[mxn];
template<int mx>
struct HLD {

    int timer;
    int hevy[mx+1], prent[mx+1], depth[mx+1], hed[mx], pos[mx];
    segmentTree<mx> segT;
    HLD() {
        fill(hevy, hevy+mx, -1);
        fill(prent, prent+mx, -1);
        fill(hed, hed+mx, -1);
        timer =0;

    }
    int dfs(int u, vector<int> g[]) {
        int sx = 1, mx_v_sx = 0;
        for(int &v: g[u]) {
            if(v==prent[u]) continue;
            prent[v] = u, depth[v] = depth[u]+1;
            int v_sx = dfs(v, g);
            sx+=v_sx;
            if(v_sx>mx_v_sx) {
                mx_v_sx = v_sx;
                hevy[u] =v;
            }

        }
        return sx;
    }
    void decompose(int u, int h, vector<int> g[]) {
        hed[u] = h;
        pos[u] = ++timer;
        if(hevy[u]>-1)
            decompose(hevy[u], h, g);
        for(int&v:g[u]) {
            if(v==prent[u] || v==hevy[u]) continue;
            decompose(v, v, g);
        }
    }
    int up(int a, int b) {
//       for range update
//        int res = 0;
//        for (; hed[a] != hed[b]; b = prent[hed[b]]) {
//            if (depth[hed[a]] > depth[hed[b]])
//                swap(a, b);
//            segT.updt(0, pos[hed[b]], pos[b], 1);
//
//        }
//        if (depth[a] > depth[b])
//            swap(a, b);
//        segT.updt(0, pos[a], pos[b], 1);

//      point update
        segT.updt(0, pos[a], pos[a], b);
        return 1;
    }
    int _find(int a, int b) {
        int res = 0;
        for (; hed[a] != hed[b]; b = prent[hed[b]]) {
            if (depth[hed[a]] > depth[hed[b]])
                swap(a, b);

            res = max(res, segT._find(0, pos[hed[b]], pos[b]));

        }
        if (depth[a] > depth[b])
            swap(a, b);
        res = max(res, segT._find(0, pos[a], pos[b]));

        return res;
    }

};

// LCP's code
int start[mxn], finish[mxn], dist[mxn];
int subtreesize[mxn];
int timer =0;
int sp[20][mxn];
void build(int n, int p, int d) {
    subtreesize[n] = 1;
    start[n]= ++timer;
    dist[n] = d;
    sp[0][n] = p;
    for(int i=1; i<20; i++) {
        sp[i][n] =  sp[i-1][sp[i-1][n]];
    }
    for(int &x: g[n]) {
        if(x!=p) {
            build(x, n, d+1);
            subtreesize[n]+=subtreesize[x];
        }
    }
    finish[n] = ++timer;
}
bool is_AanOfB(int a, int b) {
    if(!a) return 1;
    return (start[a]<=start[b] && finish[b]<=finish[a]);
}
int uery(int a, int b) {
    if(is_AanOfB(a, b)) return a;
    if(is_AanOfB(b, a)) return b;
    for(int i=19; i>=0; i--) {
        if(!is_AanOfB(sp[i][a], b)) a = sp[i][a];
    }
    return sp[0][a];

}
int cal_dist(int a, int b, int lca) {

    return dist[a]+dist[b] - 2*dist[lca];
}



int brr[mxn];
int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    cin >> t;
    for(int i=1; i<=t; i++) {
        int n;
        cin >> n;
        for(int i=1; i<=2*n; i++) g[i].clear();
        for(int i=1; i< n; i++) {
            int u, v;
            int w;
            cin >> u >> v >> w;
            brr[i+n] = w;
            g[u].push_back(i+n);
            g[v].push_back(i+n);
            g[i+n].push_back(u);
            g[i+n].push_back(v);
        }
        HLD<mxn> hld;
        build(1, 0, 0);
        hld.dfs(1, g);
        hld.decompose(1, 1, g);
        for(int i=n+1; i<2*n; i++){
            // orginal position value
            hld.up(i, brr[i]);
        }
        string s;
        while(cin >> s) {
            if(s=="DONE") break;
            int c, d;
            cin >> c >> d;
            if(s=="CHANGE") {
                hld.up(c+n, d);
            } else {
                // lowest common ancestor
                int lcp = uery(c, d);
                  // orginal node's value
                  cout << max(hld._find(c,lcp), hld._find(d, lcp))<<"\n";
            }
        }
    }
}





















