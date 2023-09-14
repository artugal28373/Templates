struct CRT {
#define ll long long
    vector<ll> v, p;
    ll x, y, gcd, tempx, tempy,n;
    CRT(vector<ll> _v, vector<ll> _p): v(_v), p(_p) {
        n = _v.size();
    }
    ll ex_GCD(ll b, ll c, ll &x, ll &y) {
        if(c==0) {
            x = 1, y = 0;
            return b;
        }
        gcd = ex_GCD(c, b%c, x, y);
        tempx = x, tempy = y;
        x = tempy;
        y = tempx - b/c*tempy;
        return gcd;
    }
    ll get() {
        ll res = v[0], lcm = p[0];
        for(ll i=1; i<n; i++) {
            gcd = ex_GCD(lcm, p[i], x, y);
            if((v[i]-res)%gcd) {
                return -1;
            }
            res = (res + x*(v[i]-res)/gcd%(p[i]/gcd)*lcm)%(lcm*p[i]/gcd);
            if(res < 0) res+=(lcm*p[i]/gcd);
            lcm = lcm * p[i]/gcd;
        }
        return res;
    }
};
