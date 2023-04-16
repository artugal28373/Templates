#include<bits\stdc++.h>
using namespace std;
#define mxn 2*100000+5
vector<int> v[mxn];
int visit[mxn];
int parent[mxn];
int subsz[mxn];
void findsize(int node, int par)
{
    subsz[node] = 1;
    for(auto &x: v[node])
    {
        if(!visit[node] && x!=par)
        {
            findsize(x, node);
            subsz[node]+=subsz[x];
        }
    }
}
int findcentroid(int node, int par, int val)
{

    for(int &x: v[node])
    {
        if(!visit[x] && x!=par && subsz[x]>val/2)
        {
            return findcentroid(x,node, val);
        }
    }
    return node;
}
void centroidDecomposition(int node, int par)
{
    findsize(node, -1);
    int c = findcentroid(node, -1, subsz[node]);
    parent[c] = par;
    visit[c] = 1;
    for(int &x: v[c])
    {
        if(!visit[x]) centroid(x, c);
    }
}
int main()
{
    int n;
    cin >> n;
    for(int i= 1;  i<n; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
  centroidDecomposition(1, 0);
}
