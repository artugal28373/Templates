int sortedarr[maxn], arr[maxn];
int cnt[maxn];
int lft[maxn], rgt[maxn];
int ind[maxn];
int block;
bool cmp(int i, int j) {
    if(lft[i]/block==lft[j]/block) return (rgt[i]/block < rgt[j]/block);
    return (lft[i]/block < lft[j]/block);
}
int a[maxn];
void solve() {
    int n;
    cin >> n;
    block=1;
    while((block+1)*(block+1)<=n) block++;
    for(int i=1; i<=n; i++) {
        cin >> arr[i];
        sortedarr[i] = arr[i];
    }
    sort(sortedarr+1, sortedarr+1+n);
    for(int i=1; i<=n; i++) {
        arr[i]= (lower_bound(sortedarr+1, sortedarr+1+n, arr[i])-sortedarr);
    }
    int m;
    cin >> m;
    for(int i=1; i<=m; i++) {
        //cin >> lft[i] >> rgt[i];
        ind[i] = i;
    }
    sort(ind+1, ind+1+m, cmp);
    int l=0, r=0, ans = 0;
    for(int j=1; j<=m; j++) {
        int i=ind[j];
        while(l+1<lft[i]) {
            l++;
//            int r = arr[l];
//            cnt[r]--;
//            if(cnt[r]!=0) ans^=sortedarr[r];
        }
        while(l>=lft[i]) {
//            int r = arr[l];
//            if(cnt[r]!=0) ans^=sortedarr[r];
//            cnt[r]++;
            l--;
        }
        while(r+1<=rgt[i]) {
            r++;
//            int rr = arr[r];
//            if(cnt[rr]!=0) ans^=sortedarr[rr];
//            cnt[rr]++;
        }
        while(r>rgt[i]) {
//            int rr = arr[r];
//            cnt[rr]--;
//            if(cnt[rr]!=0) ans^=sortedarr[rr];
            r--;
        }
       // a[i] = ans;
    }
  //  for(int i=1; i<=m; i++) cout << a[i]<<"\n";

}
