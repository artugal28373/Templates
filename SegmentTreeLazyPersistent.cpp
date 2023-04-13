//  https://www.spoj.com/problems/TTM/en/

/**So..a**/
#include<bits/stdc++.h>
using namespace std;

//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
////find_by_order()->kth largest element
////order_of_key()->number of item smaller than
#define fastIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define long long long
#define line "\n"
#define __lcm(a, b) (a/__gcd(a, b)*b)
#define PI acos(-1)
#define error cout <<"Line is print"<<endl
#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
template<class A, class B>
A POW(A b, B p, A mod) {
    A res = 1;
    while(p) {
        if(p%2==1)
            res = (res*b)%mod;
        b = (b*b)%mod, p = p/2;
    }
    return res;
}
long  tc = 0;
const long mod = 998244353;
long add(long a, long b) {
    a+=b;
    if(a>=mod) a-=mod;
    if(a<0) a+=mod;
    return a;
}
long sub(long a, long b) {
    return add(a, -b);
}
long mul(long a, long b) {
    return (a*b)%mod;
}
#define maxn 100005
#define int long
int st[24*100002];
int lftchild[24*100002];
int rgtchild[24*100002];
int brr[100005];
int lxy[24*100002];
int id;
vector<int> points;
int build(int l, int r) {
    int root = id++;
    if(l==r) {
        st[root] = brr[l];
        return  root;
    }
    int m= (l+r)/2;
    lftchild[root] =build(l,m);
    rgtchild[root] = build(m+1, r);
    st[root] = st[lftchild[root]] + st[rgtchild[root]];
    return root;
}


int updt(int previousroot, int l, int r, int s, int t, int v) {
    if(t<l || r<s) return previousroot;
    int root = id++;
    lxy[root] = lxy[previousroot];
    if(s<=l && r<=t) {

        st[root] = st[previousroot]+v*(r-l+1);
        lxy[root] = lxy[previousroot]+v;
        lftchild[root] = lftchild[previousroot];
        rgtchild[root] = rgtchild[previousroot];
        return root;
    }
    int m = (l+r)/2;
    int c = updt(lftchild[previousroot], l, m, s, t, v);
    int d = updt(rgtchild[previousroot], m+1, r, s, t, v);
    st[root] = st[c]+st[d]+lxy[root]*(r-l+1);
    lftchild[root] = c;
    rgtchild[root] = d;
    return root;
}
int tt;
int _find(int root, int l, int r, int s, int t) {

//    if(tt==1) cout << st[root1]<<" tytr";
    if(r<s || t<l) return 0;
    if(s<=l &&  r<=t) return st[root];
    int m = (l+r)/2;
    return  (min(r, t)-max(l, s)+1)*lxy[root]+_find(lftchild[root], l, m, s, t)+_find(rgtchild[root], m+1, r, s, t);
}
void solve() {
    int n;
    cin >> n;
    int op;
    cin >> op;
//    vector<int> v(n), retrive(n);
//    for(int &x: v) cin >> x;
    for(int i=1; i<=n; i++) cin >> brr[i];
    id =0;
//    vector<int> sorted(v.begin(), v.end());
//    sort(sorted.begin(), sorted.end());
//    int low =0, high =n-1;
//    for(int i=0; i< n; i++) {
//        retrive[i] = v[i];
//        v[i] = lower_bound(sorted.begin(), sorted.end(), v[i]) - sorted.begin();
//    }

    int low= 1, high = n;
    points.push_back(build(low, high));
    while(op--) {
        string s;
        cin >> s;
        if(s=="C") {
            int l, r, v;
            cin >> l >> r >> v;
            points.push_back(updt(points.back(), low, high,l, r, v));
        } else if(s=="Q") {
            int l, r;
            cin >> l >> r;
            cout << _find(points.back(), low, high, l, r)<<"\n";
        } else if(s=="H") {
            int l, r, t;
            cin >> l >> r >> t;
            cout << _find(points[t], low, high, l, r)<<"\n";
        } else {
            int t;
            cin >> t;
            while(points.size()>t+1) points.pop_back();
        }
    }


}

int32_t main() {
    fastIO();
    int t=0;
//    cout <<"ses";
//    for(cin >> t; t; t--)
    solve();

    return 0;
}
/*







a
















*/
