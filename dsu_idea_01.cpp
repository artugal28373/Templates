// https://www.codechef.com/problems/CHEFCOMP 

#include <bits/stdc++.h>
using namespace std;
//#include<ext/pb_ds/tree_policy.hpp>
//#include<ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
//template<typename temp>
//using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;

//#define long long long int
const int mxn = (2e5)+5;

using pii = pair<long long int, long long int>;

vector<long long int>  g[mxn], e[mxn], dsu[mxn];

long long int pp[mxn], t[mxn];

long long int p[mxn], sx[mxn], pr[mxn], b[mxn], f[mxn], tim[mxn], s[mxn];
bool ist[mxn];
long long int n, m;
stack<pii> st;
long long int union_find(long long int u) {
    return (u==p[u]? u : union_find(p[u]));
}
void solve() {

    cin >> n;
    while(st.size()) st.pop();
    for(long long int i=1; i<=n; i++) {
        sx[i] = 1;
        p[i] = i;
        tim[i] = (1e6);
        s[i] = 0;
        pp[i] = 0;
        t[i] = 0;

    }
    for(long long int i=1; i< n; i++) {
        long long int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(long long int i=1; i<=n; i++) cin >> pr[i];
    for(long long int i=1; i<=n; i++) cin >> b[i];
    for(long long int i=1; i<=n; i++) cin >> f[i];

    for(long long int i=n; i>=1; i--) {
        long long int r = pr[i];
        ist[r] = 1;
        for(long long int&x: g[r]) {
            if(ist[x]==1) {
                long long int c = union_find(x);
                long long int d = union_find(r);
                if(sx[d]>sx[c]) swap(c, d);
                st.push({c, d});
                p[d] = c;
                sx[c] += sx[d];
            }
        }
    }


    for(long long int i=1; i<=n; i++) {
        long long int r = pr[i];
        ist[r] = 0;
        long long int rr;
        s[rr=union_find(r)]+=b[r];
        e[rr].push_back(i);
        dsu[rr].push_back(s[rr]);

        for(long long int j=g[r].size()-1; j>=0; j--) {
            long long int x = g[r][j];
            if(ist[x]==1) {
                long long int c = st.top().first, d = st.top().second;
                st.pop();
                s[d]+=s[c];
                p[c] = c;
                p[d] = d;
                sx[c]-=sx[d];
                pp[d] = c;
                t[d] = i;


            }
        }
    }
    for(long long int i=1; i<=n; i++) {
        tim[i] = (1e6);

        long long int node = i;
        long long int tt = n+1;
        while(node) {

            if(dsu[node].size()){

            long long int rr = lower_bound(dsu[node].begin(), dsu[node].end(), f[i]) - dsu[node].begin();
            if(rr<dsu[node].size())

                if(e[node][rr]<tim[i] && e[node][rr]<=tt) tim[i] = e[node][rr];
            }
            tt = t[node];
            node = pp[node];
        }
        if(tim[i]==(1e6)) tim[i] = -1;
    }
    for(long long int i=1; i<=n; i++)
        cout << tim[i]<<" ", dsu[i].clear(), g[i].clear(), e[i].clear();

    cout <<"\n";


}

int main() {

    ios_base :: sync_with_stdio(0);
    cin.tie(0);

    int tc, t;
    for(cin >> tc, t = 1; t<=tc; t++)

    {
//        cout << "Case "<<t<<":\n";
        solve();
    }
    return 0;
}
/*
a
z
q
!
~
`
*/
