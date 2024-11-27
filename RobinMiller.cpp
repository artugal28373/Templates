#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vl __int128_t
int bigmod(int b, int p, int mod) {
    int res = 1;
    b %= mod;
    while(p) {
        if(p&1) res = vl(res)*b%mod;
        b = vl(b)*b%mod;
        p>>=1;
    }
    return res;
}
bool check_composite(int isPrime, int a, int odd, int twos) {
// a^d%n!=1 fail
// a^rd%n!=n-1 fail [0, s)
// then isPrime is composite
    int x = bigmod(a, odd,isPrime);
    if(x==1 || x==isPrime-1) return 0;
    for(int i=1; i<twos; i++) {
        x = vl(x)*x%isPrime;
        if(x==isPrime-1)
            return 0;
    }
    return 1;
}

bool MillerRabin(int n) {
    if(n<2) {
        return 0;
    }
    int twos = 0;
    int odd = n-1;
    while((odd&1)==0) {
        odd>>=1;
        twos++;
    }
    for(int a: {
                2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
            }) {
        if(n==a) return 1;
        if(check_composite(n, a, odd, twos))
            return 0;
    }
    return 1;
}


int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        int a;
        cin >>a;
        cout << (MillerRabin(a)?"Yes\n":"No\n");
    }
}
