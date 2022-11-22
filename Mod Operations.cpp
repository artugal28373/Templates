mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const long mod = 998244353;
int add(int a, int b) {
    long c = 0LL+a+b;
    if(c>=mod) c-=mod;
    if(c<0) c+=mod;
    return int(c);
}
int sub(int a, int b) {
    return add(a, -b);
}
int mul(int a, int b) {
    return int((1LL*a*b)%mod);
}
