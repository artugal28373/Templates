#include<bits/stdc++.h>
using namespace std;
#define int long long
struct vectorBasis {
    int dimension;
    vector<int> basis;
    int sz;
    vectorBasis(int n) {
        dimension = n;
        sz = 0;
        basis = vector<int>(n, 0);
    }
    void insert(int msk) {
        for(int i=dimension-1; i>=0; i--) {
            if((msk>>i)&1) {
                if(basis[i]) {
                    msk^=basis[i];
                } else {
                    basis[i] = msk;
                    sz++;
                    return;
                }
            }
        }
    }
    bool find(int msk) {
        for(int i=dimension-1; i>=0; i--) {
            msk = min(msk, msk^basis[i]);
        }
        return msk==0;
    }
    int maxXor(int ans = 0) {
        for(int i=dimension-1; i>=0; i--) {
            ans = max(ans, ans^basis[i]);
        }
        return ans;
    }
    int getSize() {
        return sz;
    }

};

int32_t main() {
    vectorBasis vb(64);
    int n;
    cin >> n;
    while(n--){
        int a;
        cin >> a;
        vb.insert(a);
    }
    cout << vb.maxXor() << "\n";

}
