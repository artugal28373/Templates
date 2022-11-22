
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
