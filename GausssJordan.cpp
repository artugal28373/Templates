#include<bits/stdc++.h>
using namespace std;

#define int long long

int bigmod(int b, int p, int mod) {
    b=b%mod;
    int res = 1;
    for(; p; res=(p&1?(1ll*res*b)%mod:res),b=(1ll*b*b)%mod, p/=2);
//    for(; p; res=(p&1?(1ll*res*b):res),b=(1ll*b*b), p/=2);
    return res;
}


/**
 output : determination, solution, solution type, rank(who are contribute in liner combination), row echlo form.
**/

// https://lightoj.com/problem/graph-coloring

int gaussJordan(vector<vector<double>> &mat, vector<int> &ans) {
    // mat contain all coef and last column contains right side value.
    const double eps = 1e-9;
    int n = mat.size();
    int m = mat[0].size()-1;
    vector<int> pos(m, -1);
    double det = 1;
    int rank = 0;
    for(int col = 0, row = 0; col < m && row < n; col++) {
        int mx = row;
        for(int i = row; i<n; i++) {
            if(fabs(mat[i][col]) > fabs(mat[mx][col])) mx = i;
        }
        if(fabs(mat[mx][col]) < eps) {
            det = 0;
            continue;
        }
        for(int i=col; i<=m; i++) {
            swap(mat[row][i], mat[mx][i]);
        }
        if(row!=mx) det = -det;
        det *= mat[row][col];
        pos[col] = row;
        for(int i=0; i<n; i++) {
            if(i!=row && fabs(mat[i][col]) > eps) {
                double c = mat[i][col]/mat[row][col];
                for(int j=col; j<=m; j++) mat[i][j] -= mat[row][j]*c;
            }
        }
        row++, rank++;
    }
    ans.assign(m, 0);
    int free_var = 0;
    for(int i=0; i<m; i++) {
        if(pos[i]!=-1) {
            ans[i] = mat[pos[i]][m]/mat[pos[i]][i];
        } else {
            free_var++;
        }
    }
    //check the result
    for(int i=0; i<n; i++) {
        double sum = 0;
        for(int j=0; j<m; j++) {
            sum += mat[i][j]*ans[j];
        }
        if(fabs(sum - mat[i][m]) > eps) return -1;//no solution
    }
    return free_var;// 0 means unique sol. positive means sol.
}
int gaussJordan(vector<vector<int>> &mat, vector<int> &ans, const int mod, vector<vector<int>> &sol_basis) {
    int n = mat.size();
    int m = mat[0].size() - 1;
    vector<int> pos(m, -1);
    int det = 1;
    int rank = 0;
//    const int MODSQ = mod*mod;
    for(int col = 0, row = 0; col<m && row<n; col++) {
        int mx = row;
        for(int i=row; i<n; i++) {
            if(mat[i][col] > mat[mx][col]) mx = i;
        }
        if(mat[mx][col]==0) {
            det = 0;
            continue;
        }
        for(int j=col; j<=m; j++) swap(mat[mx][j], mat[row][j]);
        if(row != mx) det = mod - det;
        if(det==mod) det = 0;
        det = 1ll * det * mat[row][col]%mod;
        pos[col] = row;
        if(mat[row][col] == 0) assert(0);
        int inv =  bigmod(mat[row][col], mod-2, mod);
        if(inv>0) {
            for(int i=0; i<n; i++) {
                if(i!=row && mat[i][col]) {
                    int x = (mat[i][col] * inv)%mod;
                    if(x>0) {
                        for(int j=col; j<=m; j++) {
                            if(mat[row][j]) {
                                mat[i][j] = (mod+mat[i][j] - (mat[row][j]*x%mod))%mod;
                            }
                        }
                    }
                }
            }
        }
        row++, rank++;
    }
    ans.assign(m, 0);
    int free_var=0;
    for(int i=0; i<m; i++) {
        if(pos[i] == -1) free_var++;
        else ans[i] = (mat[ pos[i] ][m] * bigmod(mat[ pos[i] ][i], mod-2, mod))%mod;
    }
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=0; j<m; j++) {
            sum = (sum + mat[i][j]*ans[j])%mod;
        }
        if(sum ^ mat[i][m]) return -1; /** no solution **/
    }

    /**
      keeping all free is equal to 0 we  get particular sol.
      take any one free is equal to 1 and rest is equal to zero.
      now x1 - 2*x2 = b0 then basis is for x2 = 2
    **/

    sol_basis = vector<vector<int>>(free_var, vector<int>(m, 0));
    for(int i=0; i<m; i++) {
        if(pos[i]!=-1) { // taking a variable that is not free
            int inv = bigmod(mat[ pos[i] ][i], mod-2, mod);
            for(int j=0, col=0; j<m; j++) {
                if(pos[j]==-1) { // taking a variable that is free
                    int b = (mat[ pos[i] ][j]*inv)%mod;
                    b = mod-b;
                    if(b==mod) b=0;
                    sol_basis[col][i] = b;
                    sol_basis[col][j] = 1;
                    col++; // colth free variable
                }
            }
        }
    }
    return free_var;// free variable number. 0 means unique sol. positive means infinite sol.
}


int32_t main() {
    cin.tie(0) ->sync_with_stdio(0);
    int t;
    cin >> t;
    int tc=0;
    while(t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<int>> mat(n, vector<int>(n+1, 0)), basis;
        vector<int> ans;
        for(int i=0; i<m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            mat[u][v] = 1;
            mat[v][u] = 1;
        }
        for(int i=0; i<n; i++) {
            mat[i][i] = (k-1);
        }

        int free_var = gaussJordan(mat, ans,k,  basis);
        cout << "Case " << ++tc << ": ";
        if(free_var==-1) cout << "0\n";
        else {
            cout << bigmod(k, free_var, 1e9+7)<<"\n";
        }
    }
}
