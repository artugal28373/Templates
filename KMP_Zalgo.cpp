#include<bits/stdc++.h>
using namespace std;
int KMP(string s, vector<int> &kmp) {

    int n = s.length();
    kmp = vector<int>(n);
    kmp[0] = -1;
    for(int i=1, node=-1; i<n; i++) {
        while(node!=-1 && s[node+1]!=s[i]) node = kmp[node];
        if(s[node+1]==s[i]) node++;
        kmp[i]=node; // till node's from 0 it is same.
    }
    return kmp.back();
}
void Z_algo(string s, vector<int> &z) {

/*
A solution is: compute the Z-function of  
$s$ , loop through all  
$i$  such that  
$i$  divides  
$n$ . Stop at the first  
$i$  such that  
$i + z[i] = n$ . Then, the string  
$s$  can be compressed to the length  
$i$ .
*/

    int n = s.length();
    z = vector<int>(n);
    for(int i=1, l=0, r=0; i<n; i++) {
        if(i<r) {
            z[i] = min(r-i, z[i-l]);
        }
        while(i+z[i]<n && s[ i+z[i] ] == s[ z[i] ]) z[i]++;
        if(i+z[i]>r) {
            l = i;
            r = i+z[i];
        }
    }

}

int32_t main() {

    string s;
    vector<int> z;
    cin >> s;
    Z_algo(s, z);
    z[0] = z.size();
    for(int &len : z) cout << len << " ";


}
