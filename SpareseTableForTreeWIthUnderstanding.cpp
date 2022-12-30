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
int  tc = 0;
#define maxn 400005

long p[20][maxn];
long fp[20][maxn];
long sum[20][maxn];
long mx[20][maxn];
long d[maxn];
long dd[maxn];
long arr[maxn];
pair<long, long> findmx(long node, long len) {
    long m = -1;
    for(long i=0;  i<20; i++) {
        if((1LL<<i)&len) {
            m = max(m, mx[i][node]);
            node  = p[i][node];
        }
    }
    return {m, node};
}
long querysum(long node, long len) {
    long m = arr[node]; // including node if need
    if(!len) return m;
    for(long i=0;  i<20; i++) {
        if((1LL<<i)&len) {
            m+=sum[i][node];// sum of ancestor excluding node value
            node  = fp[i][node];
        }
    }
    return m;

}

void add(long node, long parent, long w) {
    arr[node] = w;
    p[0][node] = parent;
    mx[0][node] = arr[parent];
    d[node] = d[parent]+1;
    for(long i=1; i<20; i++) {

        p[i][node] = p[i-1][p[i-1][node]];// ancestor excludign node
        if(p[i][node]==-1) break;
        mx[i][node] = max(mx[i-1][node], mx[i-1][p[i-1][node]]);//maximun of ancestor excluding node value
    }
    long a = -1;
    long l = 1, h = d[node];
    while(l<=h) {
        long m = (l+h)/2;
        auto help = findmx(node, m);
        if(help.first>=w) {
            a = help.second;
            h = m-1;
        } else l = m+1;
    }
    if(a!=-1) {
        dd[node] = dd[a]+1;
        fp[0][node] = a;
        sum[0][node] = arr[a];
        for(long i=1; i<20; i++) {
            fp[i][node] = fp[i-1][fp[i-1][node]];
            if(fp[i][node]==-1) break;
            sum[i][node] = sum[i-1][node] + sum[i-1][fp[i-1][node]]; // sum of ancestor excluding node value
        }
    }
}


void solve() {
    memset(p, -1, sizeof p);
    memset(sum, -1, sizeof sum);
    memset(mx, -1, sizeof mx);
    memset(fp, -1, sizeof fp);
    sum[0][1] = 0;
    mx[0][1] = 0;

    long q;
    cin >> q;
    long last = 0;
    long cnt = 1;
    while(q--) {
        long op;
        cin >> op;
        long r, w;
        cin >>r >> w;
        r^=last;
        w^=last;
        if(op==1) {
            add(++cnt, r, w);
        } else {

            long l = 0,a=-1, h = dd[r], m;
            while(l<=h) {
                m = (l+h)/2;
//                cout << querysum(r, m)<<" df "<<m<<endl;
                if(querysum(r, m)<=w) {
                    l =m+1;
                    a = m;
                } else h = m-1;
            }
            cout <<a+1<<"\n";
            last = a+1;
        }
    }
}

int main() {
    fastIO();

    long t=0;
//    for(cin >> t; t; t--)
    solve();

    return 0;
}
/*
https://codeforces.com/contest/932/problem/D























*/
