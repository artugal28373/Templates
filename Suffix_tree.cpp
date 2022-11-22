#include<bits/stdc++.h>
using namespace std;
#define maxn 1000350
#define long long long


long POW(long n, long p, long mod) {
    long res = 1;
    while(p) {
        if(p%2) res = (res*n)%mod;
        n = (n*n)%mod;
        p/=2;
    }
    return res;
}
int p[maxn], pn[maxn], cnt[maxn], id;
int c[2][maxn];
string s;
int lg;
void build(string s) {

    int n = s.length();
    for(int i=0; i<=300; i++) cnt[i] = 0;
    for(char &x: s)cnt[x]++;;
    for(long i=1; i<=n+300 ; i++) cnt[i]+=cnt[i-1];
    for(int i=n-1; i>=0; i--) {
        p[--cnt[s[i]]] = i;

    }
    int cls = 0;
    for(int i=0; i< n; i++) {
        if(i>0 && s[p[i]]!= s[p[i-1]]) cls++;
        c[id][p[i]] = cls;
    }

    for(int h=0; (1<<h)<n; h++) {
        for(int i=0; i<n; i++) {
            pn[i] = p[i] - (1<<h);
            if(pn[i]<0) pn[i]+=n;
        }
        fill(cnt, cnt+2+n,0);
        for(int i=0; i<n; i++) {
            cnt[c[id][pn[i]]]++;
        }
        for(int i=1; i<=n; i++)
            cnt[i]+=cnt[i-1];
        for(int i= n-1; i>=0; i--) {
            p[--cnt[c[id][pn[i]]]] = pn[i];
        }

        cls = 0;
        c[id^1][p[0]] = 0;
        for(int i=1; i< n; i++) {

            pair<int, int>  a = {c[id][p[i]], c[id][(p[i] + (1 << h)) % n]};
            pair<int, int>  b = {c[id][p[i-1]], c[id][(p[i-1] + (1 << h)) % n]};
            if(a!=b) cls++;
            c[id^1][p[i]] = cls;
        }
        id^=1;
        lg = h+1;
    }
}
int lcp[maxn], rnk[maxn];
void lcp_construction(string const& s) {
    int n = s.size();

    for (int i = 0; i < n; i++)
        rnk[p[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++) {
        if (rnk[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rnk[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rnk[i]] = k;
        if (k)
            k--;

    }
    return;
}
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        build(s);
        int n = s.length();
        int ans = p[0];
        for(int i=1; i<n; i++) {
            if(c[id][p[i]]==c[id][p[i-1]]) ans = min(ans, p[i]);
            else break;
        }
        cout << ans+1<<"\n";
    }
}

