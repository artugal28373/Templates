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
/*********************************************************************************************************************************************************************/

/*
  link: https://codeforces.com/problemset/problem/617/E
*/

int arr[maxn], ind[maxn], l[maxn], r[maxn];
long ans[maxn];
long mp[(1<<20)+1];
int n, m, k, block;
void solve() {
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++) {
        cin >> arr[i];
        arr[i]^=arr[i-1];
    }
    while(1) {
        block++;
        if(block*block>=n) break;
    }
    for(int i=1; i<=m; i++) {
        cin >> l[i] >> r[i];
        ind[i] = i;
    }

    sort(ind+1, ind+1+m, [](int a, int b) {
        if(l[a]/block==l[b]/block) return r[a]<r[b];
        return l[a]/block < l[b]/block;
    });
    int lft = -1, rgt = -1;
    long res = 0;

    for(int j=1; j<=m; j++) {
        int i= ind[j];
        while(rgt+1<=r[i]) {
            rgt++;
//            if(mp.find(arr[rgt]^k)!=mp.end())
            {
                res+=mp[arr[rgt]^k];
            }
            mp[arr[rgt]]++;
        }
        while(lft>=l[i]-1) {

//            if(mp.find(arr[lft]^k)!=mp.end())
            {
                res+=mp[arr[lft]^k];
            }
            mp[arr[lft]]++;
            lft--;
        }
        while(rgt>r[i]) {

            mp[arr[rgt]]--;
//            if(mp.find(arr[rgt]^k)!=mp.end())
            {
                res-=mp[arr[rgt]^k];
            }
            rgt--;

        }
        while(lft+1<l[i]-1) {
            lft++;
            mp[arr[lft]]--;
//            if(mp.find(arr[lft]^k)!=mp.end())
            {
                res-=mp[arr[lft]^k];
            }
        }
        ans[i] =  res;
    }
    for(int i=1;  i<=m; i++) cout << ans[i]<<"\n";
}
