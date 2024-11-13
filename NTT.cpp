#include<bits/stdc++.h>
using namespace std;
#define int long long
// a
namespace NTT {
const int mod = 998244353;
const int root = 102292;
const int root_1 = 116744195;
const int root_pw = (1 << 23);

int generator (int mod) {
    // (log2(mod)^6) iteration at most
    vector<int> fact;
    int phi = mod-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=mod; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= (bigmod(res, phi / fact[i], mod) != 1);
        if (ok)  return res;
    }
    return -1;
}

void ntt(vector<int> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        int n_1 = 1, p = mod-2;
        for(; p; p/=2, n = (n*n)%mod){
            if(p&1){
                n_1 = (n_1*n)%mod;
            }
        }
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}
vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    while(n < a.size() + b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for(int i=0; i<n; ++i) {
        a[i] = 1ll * a[i] * b[i] % mod;
    }
    ntt(a, true);
    return a;
}
};
vector<int>f, fi;
int mod = 998244353;
int bigMod(int b, int p) {
    int res = 1;
    for(; p; p/=2, b=(b*b)%mod) {
        if(p&1) {
            res = (res * b)%mod;
        }
    }
    return res;
}
int ncr(int n, int r) {
    if(r>n) return 0;
    return (f[n]*((fi[r]*fi[n-r])%mod))%mod;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    f.resize(n+1);
    fi.resize(n+1);
    f[0] = 1;
    for(int i=1; i<=n; i++) {
        f[i] = (f[i-1]*i)%mod;
    }
    fi[n] = bigMod(f[n], mod-2);
    for(int i=n-1; i>=0; i--) {
        fi[i] = (fi[i+1]*(i+1))%mod;
    }
    vector<int> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
    }
    vector<int> buf(n+1);
    for(int bit = 0; bit<30; bit++) {
        int cntone = 0, cntxero = 0;
        for(int i=0; i<n; i++) {
            if((v[i]>>bit)&1) {
                cntone++;
            } else {
                cntxero++;
            }
        }
        vector<int>bsone(n+1), bsxero(n+1);

        for(int i=0; i<=n; i++) {
            bsxero[i] = ncr(cntxero, i);
            if(i&1) {
                bsone[i] = ncr(cntone, i);
            }
        }
        bsone = NTT::multiply(bsone, bsxero);
        for(int i=1; i<=n; i++) {
            int r = (1<<bit)%mod;
            r = (r * bsone[i])%mod;
            buf[i] = (buf[i]+r)%mod;
        }
    } 
    for(int i=1; i<=n; i++){
        buf[i] = (buf[i]+buf[i-1])%mod;
    }
    int p;
    cin >> p;
    while(p--) {
        int m;
        cin >> m;
       cout << buf[m] <<"\n";
    }

    return 0;
}
