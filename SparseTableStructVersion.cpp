struct spTable {

    static const  int arraysize = 10000+5;
    int *sp[20];
    int (*com)(int,int );
    int n;
    int *bit;
    //           sparse table       value table   maximum bit size   operational function
    spTable(int a[][arraysize], int b[arraysize],int bit[],  int n, int (*comm)(int , int )) {

        com = comm;
        for(int i=0; i<20; i++) {
            sp[i] = a[i];
        }
        for(int i=1; i<=n; i++) {
            sp[0][i] = b[i];
        }
        this->n = n;
        this->bit = bit;
        build();
    }
    void build() {
        for(int i=1; (1<<i)<=n; i++) {
            int l = (1<<i);
            for(int j=1; j+l-1<=n; j++) {
                sp[i][j] = com(sp[i-1][j], sp[i-1][j+l/2]);
            }
        }

    }
    int query(int i, int j) {

        int l = bit[j-i+1];
        // need to be changed
        return com(sp[l][i], sp[l][j-(1<<l)+1]);
    }
};
