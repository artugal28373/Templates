// https://atcoder.jp/contests/agc002/tasks/agc002_d
// div & con idea


#include<bits/stdc++.h>
#define xx first
#define yy second
#define mxn 100005
#define push_back emplace_back
using namespace std;
vector<int>e1[mxn], comp[mxn], e2[mxn], sz[mxn], vec[mxn];
int par[mxn], ss[mxn];
int union_find(int x)
{
    if(x==par[x])return x;
    else return par[x]= union_find(par[x]);
}
int func(int c, int m)
{
    return sz[c][ upper_bound(e2[c].begin(), e2[c].end(), m)-e2[c].begin()-1 ];
}
int main()
{
    int n, m, x, y, z;
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; i++)par[i]= i;
    for(int i=1; i<=n; i++)
    e1[i].push_back(0), comp[i].push_back(i), vec[i].push_back(i),
    e2[i].push_back(0), sz[i].push_back(1), ss[i]= 1;
    for(int i=1; i<=m; i++)
    {
        scanf("%d %d", &x, &y);
        int a= union_find(x);
        int b= union_find(y);
        if(a!=b)
        {
            if(ss[a]<ss[b])swap(a, b), swap(x, y);
            par[b]= a;
            e2[a].push_back(i);
            ss[a]+= ss[b];
            sz[a].push_back(ss[a]);
            for(int j=0; j<vec[b].size(); j++)
            {
                z= vec[b][j];
                vec[a].push_back(z);
                e1[z].push_back(i);
                comp[z].push_back(a);
            }vec[b].clear();
        }
    }
    int q;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d %d %d", &x, &y, &z);
        int lo= 1, hi= m, res;
        while(lo<=hi)
        {
            int mid= (lo+hi)/2;
            int cx= comp[x][ upper_bound(e1[x].begin(), e1[x].end(), mid)-e1[x].begin()-1 ];
            int cy= comp[y][ upper_bound(e1[y].begin(), e1[y].end(), mid)-e1[y].begin()-1 ];
            int tot= func(cx, mid);
            if(cx!=cy)tot+= func(cy, mid);
            if(tot>=z)res= mid, hi= mid-1;
            else lo= mid+1;
        }
        printf("%d\n", res);
    }
    return 0;
}
