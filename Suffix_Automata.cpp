#include<bits/stdc++.h>
using namespace std;
//#define int long long int

struct SM {
    struct state {
        int len, link;
        int next[26];
        state() {
            memset(next, -1, sizeof next);
        }

    };
    const static int mxn = 1000+2;
    state st[mxn+mxn];

    int sx=0, last=0;
    SM() {
        sa_init();
    }
    void sa_init() {
        sx = last = 0;
        st[0].len = 0;
        for(int i=0; i<26;  i++) st[0].next[i]=-1;
        st[0].link = -1;
        ++sx;
    }
    void sa_extend (char cc) {
        int c = cc - 97;
        int cur = sx++;

        st[cur].len = st[last].len + 1;
        int p;
        for (p=last; p!=-1 && st[p].next[c]==-1; p=st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = sx++;
                st[clone].len = st[p].len + 1;
                memcpy(st[clone].next, st[q].next, sizeof st[clone].next);
                st[clone].link = st[q].link;
                for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    vector<int> tree[mxn+mxn];
    long long int res[mxn+mxn];
    long long int pres[mxn+mxn];
    void build(int u) {
       for(int i=1; i<sx; i++) tree[st[i].link].push_back(i);
       function<void(int )> dfs = [&](int u){
                res[u] = 1;
                pres[u] = 0;
                bool ok = 1;
               for(int &x: tree[u]){
                  dfs(x);
                 res[u]+=res[x];
                 pres[u]+=pres[x];
               }
               pres[u]+=res[u];
               return;
       };
       dfs(0);
    }
    string s;
    void dfs(int u, long long int &k) {
        if(k<=0) {
            cout << s;
            exit(0);
        }
        for(int i=0; i<26; i++) {
            if(st[u].next[i]==-1) continue;
            cout << pres[st[u].next[i]] << " "<<pres[1]<<endl;
            if(k<=pres[st[u].next[i]]) {
                s.push_back(i+97);
                dfs(st[u].next[i], k-=res[st[u].next[i]]);
            } else k-=pres[st[u].next[i]];
        }
    }


};
int32_t main() {
    string s;
    cin >> s;
    SM sm;
    for(auto &x:s) sm.sa_extend(x);
    sm.build(0);
    long long int k;
    cin >> k;
    sm.dfs(0, k);
    cout <<"No such line.";




    return 0;
}
