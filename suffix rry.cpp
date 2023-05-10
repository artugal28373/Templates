#include<bits/stdc++.h>
using namespace std;
/*Persistent*/
int st[4*200010+40];
void up(int s, int t, int v, int u=0, int l = 0, int r = 200010) {
    if(t<l || r<s) return;
    if(s<=l && r<=t) {
        st[u] = max(st[u], v);
        return;
    }
    int m = (l+r)/2;
    up(s, t, v, u*2+1,l, m);
    up(s, t, v, u*2+2, m+1, r);
//    st[u] = max(st[u*2+2], st[u*2+1]);
}

int _find(int s, int t, int u =0, int l=0, int r = 200010) {
    if(t<l || r<s) return 0;
    if(s<=l && r<=t) return st[u];
    int m = (l+r)/2;
    int c = st[u];
    if(s<=m) return max(c, _find(s, t, u*2+1, l,m));
     return max(c, _find(s, t, u*2+2, m+1, r));
}
/*end persistent*/

/* Start Suffix array */
struct SA {
    int n;
    vector <int> lcp, sa, rank;
    vector <vector <int> > t;
    SA() {}
    SA(string str) : n(str.size()) {
        vector <int> p(n), c(n), cnt(max(1 << 8, n), 0);
        for(int i = 0; i < n; i++) cnt[str[i]]++;
        for(int i = 1; i < (1 << 8); i++) cnt[i] += cnt[i - 1];
        for(int i = 0; i < n; i++) p[--cnt[str[i]]] = i;
        int cc = 1;
        c[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            cc += str[p[i]] != str[p[i - 1]];
            c[p[i]] = cc - 1;
        }
        vector <int> pn(n), cn(n);
        for(int h = 0; (1 << h) < n; h++) {
            for(int i = 0; i < n; i++) pn[i] = (p[i] - (1 << h) + n) % n;
            fill(cnt.begin(), cnt.begin() + cc, 0);
            for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for(int i = 1; i < cc; i++) cnt[i] += cnt[i - 1];
            for(int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
            cc = 1;
            cn[p[0]] = 0;
            for(int i = 1; i < n; i++) {
                pair <int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]}, prv = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                cc += (prv != cur);
                cn[p[i]] = cc - 1;
            }
            c.swap(cn);
        }
        sa = p;
        rank.resize(n);
        lcp.resize(n, 0);
        for(int i = 0; i < n; i++) rank[sa[i]] = i;
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[rank[i] + 1];
            while(i + k < n && j + k < n && str[i + k] == str[j + k] && isalpha(str[j+k])) ++k;
            lcp[rank[i]] = k;
            if(k) --k;
        }
    }
    void build_rmq() {
        int l = 32 - __builtin_clz(n);
        t = vector <vector <int> > (l, vector <int> (n, 0));
        for(int i = 0; i < n; i++) t[0][i] = lcp[i];
        for(int i = 1; i < l; i++) {
            for(int j = 0; j + (1 << i) - 1 < n; j++) {
                t[i][j] = min(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int query(int l, int r) {
        int h = 31 - __builtin_clz(r - l + 1);
        return min(t[h][l], t[h][r - (1 << h) + 1]);
    }
    int find_left(int i, int k) {
        int l = 1, r = rank[i] - 1, j = rank[i];
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(query(mid, rank[i] - 1) >= k) j = mid, r = mid - 1;
            else l = mid + 1;
        }
        return j;
    }
    int find_right(int i, int k) {
        int l = rank[i] + 1, r = n - 1, j = rank[i];
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(query(rank[i], mid - 1) >= k) j = mid, l = mid + 1;
            else r = mid - 1;
        }
        return j;
    }
} ;

using sy = SA;
/* End Suffix Array */



void solve() {
//    freopen("inputTXT.txt", "r", stdin);
    string s, temp;
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<int> len(n, 0);
    if(k==1) {
        for(int i=0; i< n; i++) {
            cin >> temp;
            long r = temp.length();
            cout << r*(r+1)/2<<" ";
        }
        return;
    }
    vector<int> sesind(n, 0);
    for(int i=0; i<n; i++) {
        cin >> temp;
        len[i] = (int)temp.length();
        if(s.length()) s = s+"&"+temp;
        else s = temp;
        sesind[i] = s.length();
    }
    s+="$";
    sy b(s);
    b.build_rmq();
    int cnt = 0;
    vector<int> Cnt(s.length()+2, -1);
    for(int i=0; i<s.length(); i++) { // labeling
        int r = b.rank[i];
        if(isalpha(s[i])) {
            Cnt[r] = cnt;
        } else {
            Cnt[r] = -1;
            cnt++;
        }
    }

    {
        vector<int> cnt(n+2, 0);
        int d  =0;
        int lft =-1;

        for(int i=0; i<s.length(); i++) {  // two pointer
            if(Cnt[i]==-1) continue;
            cnt[Cnt[i]]++;
            if(cnt[Cnt[i]]==1) d++;
            while(lft+1<i && d>=k && (Cnt[lft+1]==-1 || cnt[Cnt[lft+1]]>1 || d-1>=k)) {
                lft++;
                if(Cnt[lft]>-1) {
                    d =  ((--cnt[Cnt[lft]])==0? d-1:d);

                    up(lft, i, b.query(lft, i-1));
                }

            }
            if(d>=k && lft+1<=i-1) up(lft+1, i, b.query(lft+1, i-1));

        }
    }
    vector<long> res(n+1, 0);

    for(int i= 0; i< s.length(); i++) {
        if(Cnt[i]==-1) continue;
        res[Cnt[i]]+= 1LL*_find(i, i);
    }


    for(int i=0; i<n; i++) cout << res[i]<<" ";
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
//    cin >> t;
    while(t--) {
        solve();

    }
    return 0;
}
