///***     https://codeforces.com/contest/621/problem/E


#include <bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename temp>
using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
#define PB push_back
#define PP pop_back
#define int long long int
#define MP make_pair
#define sxof sizeof
#define sx size()
using pii =  pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
const int mod =1e9+7;
const int mxn = (1e2)+5;
int bigmod(int b, int p) {
    int res = 1;
    while(p) {
        if(p&1) res = (res * b)%mod;
        b = (b*b)%mod;
        p/=2;
    }
    return res;
}
int res[3][3], b[3][3], h[3][3], mul[3][3], cop[3][3], bs[3][3];
deque<pii> block[3];
vector<pii> init[3];
void print(int b[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << b[i][j]<<" * ";
        }
        cout << endl;
    }
}
void copy(int dest[3][3], int sour[3][3]) {
    for(int i=0; i< 3; i++) {
        for(int j=0; j<3; j++) {
            dest[i][j] =sour[i][j];
        }
    }
}
void identity(int cop[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(i^j) cop[i][j]=0;
            else cop[i][j] = 1;
        }
    }
}
void multiply(int b[3][3], int c[3][3], int res[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            res[i][j] = 0;
        }
    }
    for(int i=0; i< 3; i++) {
        for(int j=0; j<3; j++) {
            for(int k=0; k<3; k++) {
                res[i][j] = (res[i][j]+ (b[i][k]*c[k][j])%mod)%mod;
            }
        }
    }
    return;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i=0, row, l, r; i<n; i++) {
        cin >> row >> l >> r;
        row--;
        init[row].push_back({l, r});
    }
    for(int i=0; i<3; i++) init[i].push_back({m+2,m+2});
    for(int i=0; i<3; i++) {
        sort(init[i].begin(), init[i].end());
        block[i].push_back(init[i][0]);
        for(int j=1; j< init[i].sx; j++) {
            if(block[i].back().second+1<init[i][j].first) block[i].PB(init[i][j]);
            else {

                block[i][block[i].sx-1].second= max(block[i][block[i].sx-1].second, init[i][j].second);
            }
        }
    }
    int point = 1;
    res[1][1] = 1;
    while(point<m) {
        int endp = m+2;
        vector<int> sit(3);
        for(int i=0; i<3; i++) {
            if(block[i].front().first>point) {
                endp = min(endp, block[i].front().first-1);
            } else {
                endp = min(endp, block[i].front().second);
                sit[i] = 1;
            }
        }

        if(point==1) {
            sit[0] = sit[2] = 1;
            endp = 1;
        }
        if(endp>m) endp = m;
        for(int i=0; i< 3; i++) {
            if(block[i].front().second<=endp) block[i].pop_front();
        }
        if(point^endp) {
            memset(b, 0, sxof b);
            for(int i=0; i<3; i++) {
                if(sit[i]) continue;
                for(int j=-1; j<=1; j++) {
                    int from = i, go = i+j;
                    if(go>=0 && go<=2) {
                        if(sit[go]^1) {
                            b[from][go]++;
                        }
                    }
                }
            }
            identity(cop);
            copy(bs, b);

            int pw = point-endp;
            while(pw) {
                if(pw&1) {
                    multiply(bs, cop, h);
                    copy(cop, h);
                }
                multiply(bs, bs, h);
                copy(bs, h);
                pw/=2;
            }
            multiply(res, cop, h);
            copy(res, h);
        }

        if(endp<m) {
            vector<int> newsit(3);
            for(int i=0; i<3; i++) {
                if(block[i].front().first>endp+1) {

                } else {
                    newsit[i] = 1;
                }

            }
            memset(b, 0, sxof b);
            for(int i=0; i<3; i++) {
                if(sit[i]) continue;
                for(int j=-1; j<=1; j++) {
                    int from = i, go = i+j;
                    if(go>=0 && go<=2) {
                        if(newsit[go]^1) {
                            b[from][go]++;
                        }
                    }
                }
            }
            multiply(res, b, h);
            copy(res, h);

        }
        point = endp+1;
    }
    int sum = 0;
    for(int i=0; i<3; i++) sum = (sum + res[i][1])%mod;
    cout << sum;

}
int32_t main() {

    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int tc, t;
//    for(cin >> tc, t = 1; t<=tc; t++)

    {
//        cout << "Case "<<t<<":\n";
        solve();
    }
    return 0;
}
/*
a
z
q
!
~
`
*/
//////**************************************************************************************************///////////////
const int N = 30;

int b[N][N], h[N][N], res[N][N], x[N][N], y[N][N], fnl[N][N];
int  initia[N][N], cons[N][N];
//int power[30][N][N], sum[30][N][N];
void identity(int b[N][N], int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            b[i][j] = (i^j?0:1);
        }
    }
    return;
}
void copy(int dest[N][N], int source[N][N], int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            dest[i][j] = source[i][j];
        }
    }
    return;
}
void add(int a[N][N], int b[N][N], int res[N][N], int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            res[i][j] = (a[i][j] + b[i][j])%mod;
        }
    }
    return ;
}
void sub(int a[N][N], int b[N][N], int res[N][N], int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            res[i][j] = (a[i][j] - b[i][j])%mod;
            res[i][j] = (res[i][j] + mod)%mod;
        }
    }
    return ;
}
void mul(int a[N][N], int b[N][N], int res[N][N], int n, int m, int nn) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<nn; j++) {
            res[i][j] = 0;
            for(int k=0; k<m; k++) {
                res[i][j] = (res[i][j]+a[i][k]*b[k][j])%mod;
            }
        }
    }
    return;
}
void bigmod(int b[N][N], int pw, int res[N][N], int n) {
    int cop[N][N], bs[N][N];
    copy(bs, b, n, n);
    identity(res, n);
    while(pw) {
        if(pw&1) {
            mul(bs, res, cop, n, n, n);
            copy(res, cop, n, n);
        }
        mul(bs, bs, cop, n, n, n);
        copy(bs, cop, n, n);
        pw>>=1;
    }

}
//void bigmod(int b[N][N], int pw, int res[N][N], int n) {
//
//    identity(res, n);
//    for(int i=0; i<30; i++) {
//        if((pw>>i)&1) {
//            mul(res, power[i], h, n);
//            copy(res, h,n);
//        }
//    }
//    return;
//}
void print(int b[N][N], int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) cout << b[i][j]<<" * ";
        cout <<endl;
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
