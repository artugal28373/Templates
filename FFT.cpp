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
        ret[i]=((int)round(fa[i].x+0.5));
    return 1;
}

}
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
