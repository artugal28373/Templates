for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        for (int t = 0; t < n; ++t) {
            if (d[i][t] < INF && d[t][t] < 0 && d[t][j] < INF)
               // d[t][t] < 0 means negative cycle exist
              // if the codition hold then (i, j) pair has negtive cycle.
                d[i][j] = - INF; 
        }
    }
}
