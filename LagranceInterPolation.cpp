#include<bits/stdc++.h>
using namespace std;
#define int long long
int bigmod(int b, int p, int mod) {
    b=b%mod;
    int res = 1;
    for(; p; res=(p&1?(1ll*res*b)%mod:res),b=(1ll*b*b)%mod, p/=2);
//    for(; p; res=(p&1?(1ll*res*b):res),b=(1ll*b*b), p/=2);
    return res;
}
const int mod = 1e9+7;
int add(int a, int b) {
    return (a+b>=mod? a+b-mod:(a+b<0? a+b+mod : a+b));
}
int LagranceInterpolation(int x, vector<int>&y) {
    vector<int> pr(y.size());
    vector<int> suf(y.size());
    x=x%mod;
    for(int i=0; i<y.size(); i++) {
        pr[i] = (x - i-1 + mod)%mod;
        if(i) pr[i] =(pr[i-1] * pr[i])%mod;
    }
    for(int i=y.size()-1; i>=0; i--) {
        suf[i] = (x -  i-1 + mod)%mod;
        if(i+1<y.size()) suf[i] = (suf[i] * suf[i+1])%mod;
    }
    vector<int> fi(y.size());
    fi[0]=fi[1]=1;
    for(int i=2; i<y.size(); i++) {
        fi[i] = (mod - ( (mod/i)*fi[mod%i] )%mod);
    }
    for(int i=1; i<y.size(); i++) fi[i] = (fi[i] * fi[i-1])%mod;
    int sum = 0;
    for(int i=0; i<y.size(); i++) {
        int temp = 1;
        if(i) temp = (temp * pr[i-1])%mod;
        if(i+1<y.size()) temp = (temp * suf[i+1])%mod;
        temp = (temp * fi[i]%mod)%mod;
        temp = (temp * fi[y.size()-1-i])%mod;
        temp = (temp * y[i])%mod;
        if((y.size()-1-i)&1) temp = (mod-temp);

        sum = (sum + temp)%mod;
    }
    return sum;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--){
    int n,m, k;
    cin >> n >> m >> k;
    vector<int> y;
    int sum = 0;
    for(int i=1; i<=n+m+2; i++){
        int nn = (bigmod(i, n, mod) - bigmod(i-1, n, mod) + mod)%mod;
        int mm = (bigmod(i, m, mod) - bigmod(i-1, m, mod) + mod)%mod;
        sum = (sum + (nn*mm)%mod)%mod;
        y.push_back(sum);
    }
    cout << LagranceInterpolation(k, y)<<"\n";
    }


}
