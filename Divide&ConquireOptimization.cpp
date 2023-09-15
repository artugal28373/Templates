
int b[mxn][mxn], cost[mxn][mxn];
int newcost[mxn];
int dp[mxn], cur_dp[mxn];
int n, k;
int costfun(int i, int j){
  return cost[j][j] - cost[i-1][j];
}
//main part D&C optimixation
void compute(int l, int r, int opl, int opr){
   if(l>r) return;
   int m = (l+r)/2;
   pair<int, int> best{LLONG_MAX, -1};
   // for some i < m, optimal point opl -- assume
   // for some i > m, optimal point opr -- assume
   // O(mnlg(n))
   // costFunction O(1) must
   // n, m are idependent, m represent number of segment & n represents number of element are consired
  // opt(i, j)<=opt(i, j+1)  must hold, opt(i, j) means where the last segment start.
   for(int i=opl; i<=min(m, opr); i++){
           best = min(best, {dp[i-1]+costfun(i, m), i});
   }
   cur_dp[m] = best.first;
   int op = best.second;
   compute(l, m-1, opl,op);
   compute(m+1, r, op, opr);
}
void solve() {
    cin >> n >> k;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> b[i][j];
            if(i>=j) b[i][j]=0;
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cost[i][j] += cost[i-1][j]+b[i][j];
        }
    }
    for(int j=1; j<=n; j++){
        for(int i=1; i<=n; i++){
            cost[i][j]+=cost[i][j-1];
        }
    }
    for(int i=1; i<=n; i++) dp[i] = 1e12;
    for(int i=1; i<=k; i++){
        compute(1, n, 1, n);
        copy(cur_dp, cur_dp+1+n, dp);
    }
    cout << dp[n];
}

