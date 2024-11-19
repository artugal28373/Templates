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
        basis = vector<int>(n, -1);
    }
    void insert(int msk) {
        for(int i=0; i<dimension; i++) {
            if((msk>>i)&1) {
                if(~basis[i]) {
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
        for(int i=0; i<dimension; i++) {
            if((msk>>i)&1) {
                if(~basis[i]) return 0;
                else msk ^= basis[i];
            }
        }
        return 1;
    }
    int getSize() {
        return sz;
    }

};

int32_t main(){
  int n;
  cin >>n;
  vectorBasis vb(64);
  for(int i=0; i<n; i++){
    int a;
    cin >> a;
    vb.insert(a);
  }
  int sz = vb.getSize();
  int temp = 1;
  while(sz--) temp *= 2;
  cout << temp - n;

}
