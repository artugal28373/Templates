const int N = 2*30005;
int sg1[4*N], sg2[4*N];
int lazy1[4*N], lazy2[4*N];

struct sgTree {
    int *sg, *lazy;
    int n;
    int (*com)(int, int);
    sgTree(int *sg, int *lazy,int n,int initval, int (* comm)(int, int)) {
        this ->sg = sg;
        this ->lazy = lazy;
        com = comm;
        this->n = n;
        init(initval);

    }
    void init(int v) {
        for(int i=0; i<=4*n; i++) {
            lazy[i] = -1;
            sg[i] = v;
        }
    }
    void propagate(int n, int lft, int rgt) {
        if(lazy[lft]==-1) lazy[lft] = lazy[n];
        if(lazy[rgt]==-1) lazy[rgt] = lazy[n];
        lazy[lft] = com(lazy[n], lazy[lft]);
        lazy[rgt] = com(lazy[n], lazy[rgt]);
        sg[lft]  = com(lazy[n], sg[lft]);
        sg[rgt]  = com(lazy[n], sg[rgt]);
        lazy[n] = -1;
        return;
    }
    int update(int n, int l, int r, int s, int t, int v) {
//        cout <<s <<" "<<t<<endl;
        if(r<s || t<l) {

            return sg[n];
        }
        if(s<=l && r<=t) {
            if(lazy[n]==-1) {
                lazy[n] = v;
            }
            lazy[n] = com(lazy[n], v);
            sg[n] = com(sg[n], v);
            return sg[n];
        }
        int m = (l+r)/2;
        int lft = n*2+1, rgt=n*2+2;
        if(lazy[n]!=-1) propagate(n, n*2+1, n*2+2);
        int a = update(lft, l, m, s, t, v);
        int b = update(rgt, m+1, r, s, t, v);
        return sg[n] = com(a,b);
    }
    int query(int n, int l, int r,int s, int t, int notrangevalue) {
        if(r<s || t<l) return notrangevalue;
        if(s<=l && r<=t) {
//        cout <<l <<" "<<r<<" "<<n<<" "<<endl;
            return sg[n];
        }
        int m = (l+r)/2;
        int lft = n*2+1, rgt=n*2+2;
        if(lazy[n]!=-1) propagate(n, lft=n*2+1, rgt=n*2+2);
        return sg[n] = com(query(lft, l, m, s, t, notrangevalue), query(rgt, m+1, r, s, t, notrangevalue));
    }
};
int main(){
  sgTree MiN(sg1, lazy1, N+5, (1e9)+5, [](int a, int b) {
        return  min(a, b);
    });
    sgTree MaX(sg2, lazy2, N, -1, [](int a, int b) {
        return max(a, b);
    });
}
