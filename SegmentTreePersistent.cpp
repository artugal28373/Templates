// https://codeforces.com/problemset/problem/588/E

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
int st[24*100002];
int lftchild[24*100002];
int rgtchild[24*100002];
int id;
vector<int> points;
int build(int l, int r) {
    int root = id++;
    if(l==r) {
        st[root] = 0;
        return  root;
    }
    int m= (l+r)/2;
    lftchild[root] =build(l,m);
    rgtchild[root] = build(m+1, r);
    return root;
}
int updt(int previousroot, int l, int r, int s, int t, int v) {
    if(t<l || r<s) return previousroot;
    int root = id++;
    if(s<=l && r<=t) {
        st[root] = v;
        return root;
    }
    int m = (l+r)/2;
    int c = updt(lftchild[previousroot], l, m, s, t, v);
    int d = updt(rgtchild[previousroot], m+1, r, s, t, v);
    st[root] = st[c]+st[d];
//    cout << st[root]<<" "<<l<<" "<<r<<endl;
    lftchild[root] = c;
    rgtchild[root] = d;
    return root;
}
//int _find(int root1, int l, int r, int s, int t) {
//
//    if(r<s || t<l) return 0;
//    if(s<=l &&  r<=t) return st[root1];
//    int m = (l+r)/2;
//    return _find(lftchild[root1], l, m, s, t)+_find(rgtchild[root1], m+1, r, s, t);
//}
int _find(int root,int l, int r,int k) {
//    cout << st[root]<<" "<<l<<" "<<r<<endl;
    if(l==r) {
        if(st[root]<=k) return l-1;
        return l;
    }
    int m = (l+r)/2;
    int c ;
    if(st[rgtchild[root]]>k) {
        c= _find(rgtchild[root], m+1, r, k);
    } else {
        c= _find(lftchild[root], l, m, k-st[rgtchild[root]]);
    }
    return c;
}
vector<int> ress, roots;
int n;
int cl(int i) {
    int lst = n-1, res = 0;
    while(lst>=0) {
        lst = _find(roots[lst],0, n-1, i);
        res++;
//           cout << lst<<endl;
    }
    return res;
}
void nxt(int l, int r) {
    int rr;
    if((rr=cl(l))==cl(r)) {
        for(int i=l; i<=r; i++) ress[i] = rr;
        return;
    }
    int m = (l+r)/2;
    nxt(l, m);
    nxt(m+1, r);
}
void solve() {
    cin >> n;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    id =0;
//    vector<int> sorted(v.begin(), v.end());
//    sort(sorted.begin(), sorted.end());
    int low =0, high =n-1;
    for(int i=0; i< n; i++) {
//        v[i] = lower_bound(sorted.begin(), sorted.end(), v[i]) - sorted.begin();
        v[i]--;
    }
    points.push_back(build(low, high));
//    vector<int> roots(n, 0);
    vector<int> lst(n, -1);
    roots = vector<int>(n, 0);
    for(int i=0; i<n; i++) {
        if(lst[v[i]]>=0) {
            points.push_back(updt(points.back(), low, high, lst[v[i]], lst[v[i]], 0));
        }
        points.push_back(updt(points.back(),low, high, i, i, 1));
        lst[v[i]] = i;
        roots[i] = points.back();
//        cout << _find(points.back(), low, high, 0, i)<<endl;
    }
    bool ok = 0;
    int tt ;
    for(int i=1; i*i<=n; i++) {

        int lst = n-1, res = 0;
        while(lst>=0) {
            lst = _find(roots[lst],low, high, i);
            res++;
//           cout << lst<<endl;
        }

        cout << res<<" ";
        tt = i+1;

    }
    ress = vector<int>(n+1, 0);
    nxt(tt, n);
    for(int i=tt; i<=n; i++) cout << ress[i]<<" ";
}

int main() {
    fastIO();
    int t=0;
//    cout <<"ses";
//    for(cin >> t; t; t--)
    solve();

    return 0;
}
/*
























*/
