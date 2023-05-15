// Shanto vai
    struct Hash {
    int len, base; long long mod; vector <int> p, h;
    Hash(int len, int base, int mod) : len(len), base(base), mod(mod) {
        p.resize(len + 1, 0); h.resize(len + 1, 0); p[0] = 1;
        for(int i = 1; i <= len; i++) {
            p[i] = (1LL * p[i - 1] * base) % mod;
        }
    }
    void init(string &str){
        for(int i = 1; i <= len; i++) {
            h[i] = (1LL * h[i - 1] * base + (int)str[i - 1]) % mod;
        }
    }
    int substr(int l, int r) {
        return (h[r] - (1LL * h[l - 1] * p[r - l + 1]) % mod + mod) % mod;
    }
};
 
// end Shanto vai



//My own
//T
struct Hash {
    int mod, base;
    vector<int> v;
    vector<int> vbase;
    vector<int> invbase;
    int add(int a, int b) {
        long long c = 0LL+a+b;
        if(c>=mod) c-=mod;
        if(c<0) c+=mod;
        return int(c);
    }
    int sub(int a, int b) {
        return add(a, -b);
    }
    int mul(int a, int b) {
        return int((1LL*a*b)%(1LL*mod));
    }
    int bigmod(int b, int p) {
        int res = 1;
        while(p) {
            if(p%2) res = mul(res, b);
            b = mul(b, b);
            p/=2;
        }
        return res;
    }
    Hash(int b, int mod, string s = "") {
        this->base = b;
        this->mod = mod;
        if(s.length()) set(s);
    }
    int set(string s) {
        v.clear();
        vbase.clear();
        int sum = 0;
        int b = 1;
        for(int i= 0; i<s.length(); i++) {
            int r = s[i] - 'a'+1;
            r = mul(r, b);
            sum = add(sum, r);
            v.push_back(sum);
            vbase.push_back(b);
            b = mul(b, base);

        }
        invbase.push_back(bigmod(vbase.back(),mod-2));
        for(int i=v.size()-2; i>=0; i--) invbase.push_back(mul(invbase.back(), base));
        reverse(invbase.begin(), invbase.end());
        return sum;
    }
    int FullHash() {
        if(v.empty()) return 0;
        else return v.back();
    }
    int RangeHash(int i, int j) {
        int r = v[j];
        if(i>0) r = sub(r, v[i-1]);

        return mul(r, invbase[i]);
    }
};



//*****************************************************************************************************************************************************************//
//*****************************************************************************************************************************************************************//



// Tkers from other 
#include <bits/stdc++.h>


using namespace std;

mt19937 rnd(42);
unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();

const int MOD = 998244353;
const int K = 3;

int add(int x, int y, int mod = MOD)
{
    x += y;
    while(x >= mod) x -= mod;
    while(x < 0) x += mod;
    return x;
}

int sub(int x, int y, int mod = MOD)
{
    return add(x, -y, mod);
}

int mul(int x, int y, int mod = MOD)
{
    return (x * 1ll * y) % mod;
}

int binpow(int x, int y, int mod = MOD)
{
    int z = 1;
    while(y > 0)
    {
        if(y % 2 == 1) z = mul(z, x, mod);
        y /= 2;
        x = mul(x, x, mod);
    }
    return z;
}

bool prime(int x)
{
    for(int i = 2; i * 1ll * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}

int get_base()
{
    int x = rnd() % 10000 + 4444;
    while(!prime(x)) x++;
    return x;
}

int get_modulo()
{
    int x = rnd() % int(1e9) + int(1e8);
    while(!prime(x)) x++;
    return x;
}

typedef array<int, K> hs;

hs base, modulo;

void generate_hs()
{
    for(int i = 0; i < K; i++)
    {
        base[i] = get_base();
        modulo[i] = get_modulo();
    }
}

hs operator+(const hs& a, const hs& b)
{
    hs c;
    for(int i = 0; i < K; i++)
    {
        c[i] = add(a[i], b[i], modulo[i]);
    }
    return c;
}

hs operator-(const hs& a, const hs& b)
{
    hs c;
    for(int i = 0; i < K; i++)
    {
        c[i] = sub(a[i], b[i], modulo[i]);
    }
    return c;
}

hs operator*(const hs& a, const hs& b)
{
    hs c;
    for(int i = 0; i < K; i++)
    {
        c[i] = mul(a[i], b[i], modulo[i]);
    }
    return c;
}

hs operator^(const hs& a, const hs& b)
{
    hs c;
    for(int i = 0; i < K; i++)
    {
        c[i] = binpow(a[i], b[i], modulo[i]);
    }
    return c;
}

hs char_hash(char c)
{
    hs res;
    for(int i = 0; i < K; i++)
        res[i] = c - 'A' + 1;
    return res;
}

const int N = 18;
const int V = 1 << N;
string s;
hs vertex_hash[V + 43];



void rec(int x)
{

}

int main()
{
    generate_hs();
    vertex_hash[0] = char_hash(s[0]);

}   
