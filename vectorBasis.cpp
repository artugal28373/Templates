#include<bits/stdc++.h>
using namespace std;

struct vectorBasis{
    int dimension;
    vector<int> basis;
    int sz;
    vectorBasis(int n){
        dimension = n;
        sz = 0;
        basis = vector<int>(n, -1);
    }
   void addNewElement(int msk){
        for(int i=0; i<dimension; i++){
            if((msk>>i)&1){
                if(~basis[i]){
                    msk^=basis[i];
                }else{
                    basis[i] = msk;
                    sz++;
                    return;
                }
            }
        }
    }
    bool check(int msk){
       for(int i=0; i<dimension; i++){
        if((msk>>i)&1){
            if(~basis[i]) return 0;
            else msk ^= basis[i];
        }
       }
       return 1;
    }
    int currentBasisSize(){
        return sz;
    }

};
