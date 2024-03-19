// https://lightoj.com/problem/tree-flip

#include<bits/stdc++.h>
using namespace std;
#define debugs(x, y) cout << x<<" "<<y<<endl
#define debug(x) cout <<x<<" debug"<<endl
const int mxn = 1e+5+5;
// problem input
vector<int> g[ mxn ];
int a[ mxn ], n, q;
// problem input
// segment tree
int seg[ 20 ][ 4*mxn ], lazy[ 20 ][ 4*mxn ];
// segment tree
// centroid decomposition
int level[ mxn ], centroid_parent[ 20 ][ mxn ];
int already_taken[ mxn ], how_many[ mxn ];
// centroid decomposition
// level wise euler tour
int start[ 20 ][ mxn ], finish[ 20 ][ mxn ];
int  who[ 20 ][ mxn ];
int representative[ 20 ][ mxn ];
int id[ 20 ];
// level wise euler tour
void destroy(int n) {

    for(int i=0; i<=n; i++) {
        g[ i ].clear();
        already_taken[ i ] = 0;
    }
    for(int lvl=0; lvl<20; lvl++) {
        id[ lvl ] = 0;
        for(int u=0; u<=4*n; u++) {
            seg[ lvl ][ u ] = 0;
            lazy[ lvl ][ u ] = 0;
        }
    }
}
void push(int lvl,int u, int l, int r) {


    lazy[ lvl ][ u*2+1 ] ^= lazy[ lvl ][ u ];
    lazy[ lvl ][ u*2+2 ] ^= lazy[ lvl ][ u ];

    if(lazy[ lvl ][ u ] == 1) {
        int m = ( l+r ) / 2;
        seg[ lvl ][ u*2+1 ] = (m-l+1)-seg[ lvl ][ u*2+1 ];
        seg[ lvl ][ u*2+2 ] = (r-m)-seg[ lvl ][ u*2+2 ];
    }

    lazy[ lvl ][ u ] = 0;
}
void update(int lvl, int u, int l, int r, int s, int t, int v) {
    if(s <= l && r <= t) {
        lazy[ lvl ][ u ] ^= v;
        if( v == 1 )
            seg[ lvl ][ u ] = r - l + 1 - seg[ lvl ][ u ];
        return;
    }
    if(r < s || t < l) return;
    int m = ( l + r ) / 2;
    push(lvl, u, l, r);
    update(lvl, u*2+1, l, m, s, t, v);
    update(lvl, u*2+2, m+1, r, s, t, v);
    seg[ lvl ][ u ] = seg[ lvl ][ u*2+1 ]+seg[ lvl ][ u*2+2 ];
}
int query(int lvl, int u, int l, int r, int s, int t) {
    if(s<=l && r<=t) {
        return seg[ lvl ][ u ];
    }
    if(r<s || t<l) return 0;
    int m = ( l+r )/2;
    push(lvl, u, l, r);
    return query(lvl, u*2+1, l, m, s, t) + query(lvl, u*2+2, m+1, r, s, t);
}

int subtree_size(int u, int p) {
    how_many[ u ] = 1;
    for(int &x: g[ u ]) {
        if( x ^ p ) {
            if( !already_taken[ x ] ) {
                how_many[ u ] += subtree_size( x, u );
            }
        }
    }
    return how_many[ u ];
}

int find_centroid(int u, int p, int how) {
    for(int &x: g[ u ]) {
        if( !already_taken[x ] ) {
            if( x ^ p ) {
                if( 2 * how_many[ x ] > how ) {
                    return find_centroid( x, u, how );
                }
            }
        }
    }
    return u;
}
void euler( int lvl, int u, int p ) {
    start[ lvl ][ u ] = ++id[ lvl ];
    who[ lvl ][ id[ lvl ] ] = u;
    for(int &x: g[ u ]) {
        if( !already_taken[ x ] ) {
            if( x ^ p ) {
                euler( lvl, x, u );
            }
        }
    }
    finish[ lvl ][ u ] = id[ lvl ];
}
void dfs_decomposition( int lvl, int u, int p, int v, int w ) {
    representative[ lvl ][ u ] = w;
    v ^= a[ u ];
    update( lvl, 0, 1, n, start[ lvl ][ u ], start[ lvl ][ u ], v );

    for(int &x: g[ u ]) {
        if(!already_taken[ x ]) {
            if( x ^ p ) {
                dfs_decomposition( lvl, x, u, v, (u==p ? x : w) );
            }
        }
    }
}
void centroid_decomposition(int u, int p, int lvl ) {
    subtree_size( u, p );
    int c = find_centroid( u, p, how_many[ u ] );

    already_taken[ c ] = 1;
    level[ c ] = lvl;
    centroid_parent[ lvl ][ c ] = c;
    for( int i = lvl - 1; i >= 0; i-- ) {
        centroid_parent[ i ][ c ] = centroid_parent[ i  ][ p ];
    }
    euler( lvl, c, c );
    dfs_decomposition( lvl, c, c, 0, c );
    for(int &x: g[c]) {
        if( !already_taken[ x ] ) {
            centroid_decomposition( x, c, lvl+1 );
        }
    }
}

void centroid_update(int u) {
    a[u] ^= 1;
    for(int i = level[ u ]; i >= 0; i-- ) {
        update( i, 0, 1, n, start[ i ][ u ], finish[ i ][ u ], 1 );
    }
}

int centroid_query(int u) {
    int res = query( level[ u ], 0, 1, n, start[ level[ u ] ][ u ], finish[ level[ u ] ][ u ] );
    int r, prv = u, p = u;
    for(int i=level[ u ]-1; i >= 0; i--) {
        prv = p;
        p = centroid_parent[ i ][ u ];
        r = representative[ i ][ prv ];
        int temp = query( i, 0, 1, n, start[ i ][ p ], finish[ i ][ p ] ) - query( i, 0, 1, n, start[ i ][ r ], finish[ i ][ r ]);
        int required = 1^a[ p ]^query( i, 0, 1, n, start[ i ][ u ], start[ i ][ u ] );
        if( required == 0 ) {
            temp = (finish[ i ][ p ] - start[ i ][ p ] + 1) - ( finish[ i ][ r ] - start[ i ][ r ] + 1 ) - temp;
            assert( temp >= 0 );
        }
        res = res + temp;
    }

    return res;
}


int32_t main() {
    ios_base :: sync_with_stdio( 0 );
    cin.tie( 0 );
//    freopen("inputf.in", "r", stdin);
    vector<int> v;

    int  totalTest=1;
    cin >> totalTest;
    for(int i=1; i<=totalTest; i++) {
        cin >> n;
        cin >> q;

        for(int i=1; i<=n; i++) {
            cin >> a[i];
        }

        for(int i=1; i<n; i++) {
            int u, v;
            cin >> u >> v;
            g[ u ].push_back( v );
            g[ v ].push_back( u );
        }
        centroid_decomposition( 1, 1, 0 );
        int root = 1;
        cout <<"Case "<<i<<":\n";
        while(q--) {
            int op;
            cin >> op;
            if(op==1) {
                int x;
                cin >> x;
                centroid_update( x );
            } else {
                cin >> root;
            }

              cout << centroid_query(root)<<"\n";
        }

        destroy( n );
    }


}

