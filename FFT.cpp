// O(nlgn^2)
int dp[mxn], g[mxn];
// both are 1-based
// dp[i] = sun of dp[j]*g[i-j] where j>=1 && j<n
void mul(int i, int j, int l, int r){
     vector<int> a(j-i+1), b(r-l+1);
     for(int s=0; s<(j-i+1); s++){
         a[s] = dp[s+i];
         b[s] = g[s+l];
     }
     vector<int> c = FFT::multiply(a, b);
     for(int s=0; s<c.size(); s++){
         dp[i+l+s]+=c[s];
     }
}

void dc(int l, int r, int s, int t){

    if(l==r){
        mul(l , r, s, t);
        return;
    }
    int m1 = (l+r)/2;
    int m2 = (s+t)/2;
    dc(l, m1, s, m2);
    mul(l, m1, m2+1, t);
    dc(m1+1, r, s, m2);
    mul(m1+1, r, m2+1, t);
}
// Modifiedby me
namespace FFT {
#define PI acos(-1.0)
struct base {
    /** x = real, y = imagine **/
    double x,y;
    base(double a=0,double b=0):x(a),y(b) {}
    base operator+(base c) {
        return base(x+c.x,y+c.y);
    }
    base operator-(base c) {
        return base(x-c.x,y-c.y);
    }
    base operator*(base c) {
        return base(x*c.x-y*c.y,x*c.y+y*c.x);
    }
    base operator/(double d) {
        return base(x/d,y/d);
    }
    void operator*=(base c) {
        double a=x*c.x-y*c.y,b=x*c.y+y*c.x;
        x=a,y=b;
    }
    void operator/=(double d) {
        x/=d,y/=d;
    }
};
void fft(vector<base>&a,bool inv) {
    int n=a.size();
    for(int i=1,j=0; i<n; i++) {
        int bit=n>>1;
        for(; bit&j; bit>>=1) j^=bit;
        j^=bit;
        if(i<j)swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1) {
        double ang=2*PI/len*(inv?-1:1);
        base wlen(cos(ang),sin(ang));
        for(int i=0; i<n; i+=len) {
            base w(1);
            for(int j=0; j<len/2; j++) {
                base u=a[i+j],v=a[i+j+len/2]*w;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(inv)for(auto &x:a)x/=n;
}
void fft2D(vector<vector<base>>&a, bool inv) {
    for(auto &rows: a) {
        fft(rows, inv);
    }
    int col = a[0].size();
    int row = a.size();
    vector<base> temp(row);
    for(int j=0; j<col; j++) {
        for(int i=0; i<row; i++) {
            temp[i] = a[i][j];
        }
        fft(temp, inv);
        for(int i=0; i<row; i++) {
            a[i][j] = temp[i];
        }
    }
}
vector<int> multiply(vector<int>&a,vector<int>&b) {
    /**a^0+a^1+a^2+a^3+... format**/
    int sz=a.size()+b.size();
    int n=1;
    while(n<sz)n<<=1;
    vector<base>fa(a.begin(),a.end());
    vector<base>fb(b.begin(),b.end());
    fa.resize(n);
    fb.resize(n);
    fft(fa,false);
    fft(fb,false);
    for(int i=0; i<n; i++)fa[i]*=fb[i];
    fft(fa,true);
    vector<int> ret;
    sz = a.size()+b.size()-1;
    ret.resize(sz, 0);
    for(int i=0; i<sz; i++)
        ret[i]=((int)round(fa[i].x));
    return ret;
}
vector<vector<int>> multiply(vector<vector<int>> &a, vector<vector<int>> &b) {
    vector<vector<base>>fa(a.size()), fb(b.size());
    for(int i=0; i<a.size(); i++) {
        fa[i] = vector<base>(a[i].begin(), a[i].end());
    }
    for(int i=0; i<a.size(); i++) {
        fb[i] = vector<base>(b[i].begin(), b[i].end());
    }
    int nrow = 1, ncol = 1;
    int sz;
    sz = a.size()+b.size();
    while(nrow<sz) nrow<<=1;
    sz = a[0].size()+b[0].size();
    fa.resize(nrow);
    fb.resize(nrow);
    while(ncol<sz) ncol<<=1;
    for(int i=0; i<nrow; i++) {
        fa[i].resize(ncol);
        fb[i].resize(ncol);
    }
    fft2D(fa, false);
    fft2D(fb, false);
    for(int i=0; i<nrow; i++) {
        for(int j=0; j<ncol; j++) {
            fa[i][j] *= fb[i][j];
        }
    }
    fft2D(fa, true);
    nrow = a.size()+b.size()-1, ncol = a[0].size()+b[0].size()-1;
    vector<vector<int>> ret(nrow, vector<int>(ncol, 0));
    for(int i=0; i<nrow; i++) {
        for(int j=0; j<ncol; j++) {
            ret[i][j] = ( (int)round(fa[i][j].x) );
        }
    }
    return ret;
}
};




//////////////////

/**
/** araf vai.. slight modificattion in naming**/
/** problem: codeforces.com/contest/632/problem/E **/

#include<bits/stdc++.h>
using namespace std;
namespace FFT {
#define PI acos(-1.0)
struct base {
    /** x = real, y = imagine **/
    double x,y;
    base(double a=0,double b=0):x(a),y(b) {}
    base operator+(base c) {
        return base(x+c.x,y+c.y);
    }
    base operator-(base c) {
        return base(x-c.x,y-c.y);
    }
    base operator*(base c) {
        return base(x*c.x-y*c.y,x*c.y+y*c.x);
    }
    base operator/(double d) {
        return base(x/d,y/d);
    }
    void operator*=(base c) {
        double a=x*c.x-y*c.y,b=x*c.y+y*c.x;
        x=a,y=b;
    }
    void operator/=(double d) {
        x/=d,y/=d;
    }
};
void fft(vector<base>&a,bool inv) {
    int n=a.size();
    for(int i=1,j=0; i<n; i++) {
        int bit=n>>1;
        for(; bit&j; bit>>=1) j^=bit;
        j^=bit;
        if(i<j)swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1) {
        double ang=2*PI/len*(inv?-1:1);
        base wlen(cos(ang),sin(ang));
        for(int i=0; i<n; i+=len) {
            base w(1);
            for(int j=0; j<len/2; j++) {
                base u=a[i+j],v=a[i+j+len/2]*w;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(inv)for(auto &x:a)x/=n;
}
bool multiply(vector<int>&a,vector<int>&b, vector<int> &ret) {
    /**a^0+a^1+a^2+a^3+... format**/
    int sz=a.size()+b.size();
    int n=1;
    while(n<sz)n<<=1;
    vector<base>fa(a.begin(),a.end());
    vector<base>fb(b.begin(),b.end());
    fa.resize(n);
    fb.resize(n);
    fft(fa,false);
    fft(fb,false);
    for(int i=0; i<n; i++)fa[i]*=fb[i];
    fft(fa,true);
    ret.resize(n);
    for(int i=0; i<n; i++)
        ret[i]=((int)round(fa[i].x));
    return 1;
}

};
int main() {
    int i,j,k,n,m;
    cin>>n>>k;
    vector<int> v(1000+5,0);
    for(int i=0, u; i<n && cin >> u; i++) v[u]=1;
    vector<int> res = {1};
    while(k) {
        if(k&1) FFT::multiply(res, v, res);
        FFT::multiply(v, v, v);
        k/=2;
    }
    for(int i=0; i<res.size(); i++) {
        if(res[i]) cout << i <<" ";
    }


    return 0;
}
**/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/** 
// youknowwho
#include<bits/stdc++.h>
using namespace std;
//to store complex numbers
#define ld long double
#define PI acos(-1.0)
#define vi vector<int>
#define all(b) b.begin(), b.end()
#define ll long long
//inv=0 means Converting from coefficient form to point value form
//inv=1 means Converting from point value  form to coefficient form i.e. inverse fft
struct base {
    typedef double T;
    T re, im;
    base() :re(0), im(0) {}
    base(T re) :re(re), im(0) {}
    base(T re, T im) :re(re), im(im) {}
    base operator + (const base& o) const {
        return base(re + o.re, im + o.im);
    } base operator - (const base& o) const {
        return base(re - o.re, im - o.im);
    }
    base operator * (const base& o) const {
        return base(re * o.re - im * o.im, re * o.im + im * o.re);
    } base operator / (const T o) const {
        assert(0.0!=o);
        return base(re/o,im/o);
    } base operator * (ld k) const {
        return base(re * k, im * k);
    }
    base conj() const {
        return base(re, -im);
    }
};
void fft(vector<base> &a,bool inv) {
    int n=(int)a.size();
    //rearranging the elements to the leaf nodes of the tree
    for(int i=1,j=0; i<n; i++) {
        int bit=n>>1;
        for(; j>=bit; bit>>=1) j-=bit;
        j+=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len*=2) {
        ld ang=2*PI/len*(inv?-1:1);
        base wlen(cos(ang),sin(ang));
        //wlen=e^(2*PI*i/n)=cos(2*PI/n)+i*sin(2*PI/n)
        //bcz e^(i*theta)=cos(theta)+i*sin(theta)
        for(int i=0; i<n; i+=len) {
            base w=1;
            for(int j=0; j<len/2; j++) {
                base even=a[i+j],odd=a[i+j+len/2];
                a[i+j]=even+w*odd;
                a[i+j+len/2]=even-w*odd;
                w= w*wlen;
            }
        }
    }
    if(inv) for(int i=0; i<n; i++) a[i]=a[i]/n;
}
void multiply(vi& a,vi& b,vi& res) {
    vector<base>fa(all(a)),fb(all(b));
    int n=1;
    int mx=max((ll)a.size(),(ll)b.size());
    while(n<mx) n*=2;//making it power of 2
    n*=2;//making 2*n size
    fa.resize(n);
    fb.resize(n);
    //convolution
    fft(fa,0);
    fft(fb,0);
    for(int i=0; i<n; i++) fa[i]=fa[i]*fb[i];
    fft(fa,1);//inverse fft
    res.resize(n);
    for(int i=0; i<n; i++) res[i]=int(fa[i].re+0.5);
    for(int i=0; i<n; i++) if(res[i]>1) res[i]=1;
    while(res.size()>1&&res.back()==0) res.pop_back();
    return;
}

void getpow(vi &v,int k,vi &res) {
    res.push_back(1);
    while(k>0) {
        if(k&1) multiply(res,v,res);
        multiply(v,v,v);
        k>>=1;
    }
}
int main() {
    int i,j,k,n,m;
    cin>>n>>k;
    vi v(1000+5,0);
    for(int i=0, u; i<n && cin >> u; i++) v[u]=1;
    vi res = {1};
    while(k) {
        if(k&1) multiply(res, v, res);
        multiply(v, v, v);
        k/=2;
    }
    for(int i=0; i<res.size(); i++) {
        if(res[i]) cout << i <<" ";
    }


    return 0;
}
**/

////////////////////

//// FFT code
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace FFT {
typedef long double ld;
struct base {
    typedef double T;
    T re, im;
    base() :re(0), im(0) {}
    base(T re) :re(re), im(0) {}
    base(T re, T im) :re(re), im(im) {}
    base operator + (const base& o) const {
        return base(re + o.re, im + o.im);
    } base operator - (const base& o) const {
        return base(re - o.re, im - o.im);
    }
    base operator * (const base& o) const {
        return base(re * o.re - im * o.im, re * o.im + im * o.re);
    } base operator * (ld k) const {
        return base(re * k, im * k);
    }
    base conj() const {
        return base(re, -im);
    }
};


const int N = 21;
const int MAXN = (1 << N);
base w[MAXN];
base f1[MAXN];
int rev[MAXN];

void build_rev(int k) {
    static int rk = -1;
    if (k == rk)return;
    rk = k;
    int K=1<<k;
    for (int i = 1; i <= K; i++) {
        int j = rev[i - 1], t = k - 1;
        while (t >= 0 && ((j >> t) & 1)) {
            j ^= 1 << t;
            --t;
        }
        if (t >= 0) {
            j ^= 1 << t;
            --t;
        }
        rev[i] = j;
    }

}

void fft(base *a, int k) {
    build_rev(k);
    int n = 1 << k;
    for (int i = 0; i < n; i++) if (rev[i] > i) swap(a[i], a[rev[i]]);
    for (int l = 2, ll = 1; l <= n; l += l, ll += ll) {
        if (w[ll].re == 0 && w[ll].im == 0) {
            ld angle =  (1.0l * acos(-1.0l))/ ll;
            base ww(cosl(angle), sinl(angle));
            if (ll > 1) for (int j = 0; j < ll; ++j) {
                    if (j & 1) w[ll + j] = w[(ll + j) / 2] * ww;
                    else w[ll + j] = w[(ll + j) / 2];
                } else w[ll] = base(1, 0);
        }
        for (int i = 0; i < n; i += l) for (int j = 0; j < ll; j++) {
                base v = a[i + j], u = a[i + j + ll] * w[ll + j];
                a[i + j] = v + u;
                a[i + j + ll] = v - u;
            }
    }
}

vector<int> mul(const vector<int>& a, const vector<int>& b) {
    int k = 1;
    int ABsize=(int)(a.size()) + (int)(b.size());
    while ((1 << k) < ABsize) ++k;
    int n = (1 << k);
    for (int i = 0; i < n; i++) f1[i] = base(0, 0);
    int Asize=(int)(a.size());
    int Bsize=(int)(b.size());
    for (int i = 0; i < Asize; i++) f1[i] = f1[i] + base(a[i], 0);
    for (int i = 0; i < Bsize; i++) f1[i] = f1[i] + base(0, b[i]);
    fft(f1, k);
    for (int i = 0; i < 1 + n / 2; i++) {
        base p = f1[i] + f1[(n - i) % n].conj();
        base _q = f1[(n - i) % n] - f1[i].conj();
        base q(_q.im, _q.re);
        f1[i] = (p * q) * 0.25;
        if (i > 0) f1[(n - i)] = f1[i].conj();
    }
    for (int i = 0; i < n; i++) f1[i] = f1[i].conj();
    fft(f1, k);
    vector<int> r(ABsize);
    int Rsize=(int)(r.size());
    for (int i = 0; i < Rsize; i++) {
        r[i] = (int)(f1[i].re / n + 0.5);
    }

    return r;
}
};

using namespace FFT;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> bs(1000+1, 0);
    vector<int> res={1};
    int n, k;
    cin >> n >> k;
    int mn = 1e9;
    for(int i=0; i<n; i++) {
        int u;
        cin >> u;
        bs[u]=1;
        if(u<mn) mn = u;
    }
    mn*=k;
    while(k) {
        if(k&1) res = FFT::mul(res, bs);
        bs = FFT::mul(bs, bs);
        k/=2;
    }
    for(int i=0; i<res.size(); i++) {
        if(res[i]) cout << i <<" ";
    }
    cout << endl;
    return 0;
}
 


