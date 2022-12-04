int block;
int n, m;
int arr[maxn];
vector<int> v[1000];
int qurey(int s, int t, int c) {
    int res = 0;
    for(int i=0; !v[i].empty(); i++) {
        int start = i*block, finish = (i+1)*block-1;
        if(s<=start && finish<=t) {
            res += (v[i].size()-(lower_bound(v[i].begin(), v[i].end(), c) - v[i].begin()));
        } else if(start<=s && s<=finish) {
            for(int j=s; j<=min(t, finish); j++) {
                if(arr[j]>=c) res++;
            }
        } else if(start<=t && t<=finish) {
            for(int j=max(start, s); j<=t; j++) if(arr[j]>=c) res++;
        }
    }
    return res;
}
void update(int pos, int c) {
    int start = (pos/block)*block;
    int finish = ((pos/block)+1)*block -1;
    arr[pos] = c;
    v[pos/block].clear();
    for(int i=start; i<min(n,finish+1); i++) {
        v[i/block].push_back(arr[i]);
    }
    sort(v[pos/block].begin(), v[pos/block].end());
}
void solve() {
    cin >> n ;
    for(int i=0; i<n; i++) cin >> arr[i];
    block = int(sqrt(double(n)))+1;
    for(int i=0; i<n; i++) {
        v[i/block].push_back(arr[i]);
    }
    for(int i=0; !v[i].empty(); i++) {
        sort(v[i].begin(), v[i].end());
    }
    int op, l, r;
    int m;
    cin >> m;
    for(int i=1; i<=m; i++) {
        cin >> op >> l >> r;
        l--;
        if(!op) {
            r--;
            int c;
            cin >> c;
            cout << qurey(l, r, c)<<"\n";
        } else {

            update(l, r);
        }
    }
}
