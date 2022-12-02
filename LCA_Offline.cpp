#define maxn 100005
vector<int> g[maxn];
int start[maxn], finish[maxn], dist[maxn];
int subtreesize[maxn];
int timer =0;
int sp[20][maxn];
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
int query(int a, int b) {
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
init(int n){
  memset(sp, 0, sizeof sp);
  timer=0;
  for(int i=0; i<=n; i++){
    g[i].clear();
  }
}
void solve(){
  // take input a tree
  build(1, 0, 0);
}
