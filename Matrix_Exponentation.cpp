namespace matrix {
int mod;
vector<vector<int>> identity_matrix(int n) {
    assert(n>0);
    vector<vector<int>> vec(n, vector<int>(n, 0));
    for(int i=0; i<n; i++) {
        vec[i][i] = 1;
    }
    return vec;
}
vector<vector<int>> add(vector<vector<int>> &a, vector<vector<int>> &b) {
    assert(a.size() == b.size() && a.size() > 0 && a[0].size() == b[0].size() && b[0].size() > 0);
    vector<vector<int>> vec(a.size(), vector<int>(a[0].size(), 0));
    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<a[0].size(); j++) {
            vec[i][j] = a[i][j] + b[i][j];
            vec[i][j] %= mod;
        }
    }
    return vec;
}
vector<vector<int>> mul(vector<vector<int>> &a, vector<vector<int>> &b) {
    assert(a.size() > 0  && b.size() > 0 && a[0].size() == b.size());
    vector<vector<int>> vec(a.size(), vector<int>(b[0].size(), 0));

    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<b[0].size(); j++) {
            for(int k=0; k<a[0].size(); k++) {
                vec[i][j] += a[i][k]*b[k][j];
                vec[i][j] %= mod;
            }
        }
    }
    return vec;
}
vector<vector<int>> bigmod(vector<vector<int>> &b, int p) {
    assert(b.size() > 0 && b.size() == b[0].size());
    vector<vector<int>> vec = identity_matrix(b.size());
    while(p) {
        if(p&1) vec = mul(vec, b);
        p/=2;
        if(p==0) break;
        b = mul(b, b);
    }
    return vec;
}
}
////////////////////
 
const int MOD = 1e9 + 7;
 
struct Matrix {
 
        int n, m;
        vector < vector < int > > mat;
 
        Matrix(vector < vector < int > > M) : mat(M), n(M.size()), m(M[0].size()) {}
 
        static Matrix id(int n) {
                vector < vector < int > > I(n, vector <int> (n, 0));
                for(int i = 0; i < n; i++)
                        I[i][i] = 1;
                return Matrix(I);
        }
 
        Matrix operator * (Matrix A) {
                int N = n;
                int M = A.m;
                int O = m;
                vector < vector < int > > Temp(N, vector <int> (M, 0));
 
                for(int i = 0; i < N; i++)
                        for(int j = 0; j < M; j++)
                                for(int k = 0; k < O; k++)
                                        Temp[i][j] = ((Temp[i][j] + mat[i][k] * A.mat[k][j]) % MOD + MOD) % MOD;
                return Matrix(Temp);
        }
 
        friend ostream& operator << (ostream &out, Matrix A) ;
 
 
};
 
ostream& operator << (ostream &out, Matrix A) {
        for(int i = 0; i < A.n; i++) {
                if(i) cout << '\n';
                for(int j = 0; j < A.m; j++)
                        cout << A.mat[i][j] << " ";
        }
}
 
Matrix BigMod(int n, Matrix M, int N) {
        Matrix ret = M.id(N);
        while(n) {
                if(n & 1)
                        ret = ret * M;
                n /= 2;
                M = M * M;
        }
        return ret;
}
