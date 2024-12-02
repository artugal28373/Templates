// cp -algo
struct TwoSatSolver {
    int n_vars;
    int n_vertices;
    vector<vector<int>> adj, adj_t;
    vector<bool> used;
    vector<int> order, comp;
    vector<bool> assignment;

    TwoSatSolver(int _n_vars) : n_vars(_n_vars), n_vertices(2 * n_vars), adj(n_vertices),
        adj_t(n_vertices), used(n_vertices), order(), comp(n_vertices, -1), assignment(n_vars) {
        order.reserve(n_vertices);
    }
    void dfs1(int v) {
        used[v] = true;
        for (int u : adj[v]) {
            if (!used[u])
                dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : adj_t[v]) {
            if (comp[u] == -1)
                dfs2(u, cl);
        }
    }

    bool solve_2SAT() {
        order.clear();
        used.assign(n_vertices, false);
        for (int i = 0; i < n_vertices; ++i) {
            if (!used[i])
                dfs1(i);
        }

        comp.assign(n_vertices, -1);
        for (int i = 0, j = 0; i < n_vertices; ++i) {
            int v = order[n_vertices - i - 1];
            if (comp[v] == -1)
                dfs2(v, j++);
        }

        assignment.assign(n_vars, false);
        for (int i = 0; i < n_vertices; i += 2) {
            if (comp[i] == comp[i + 1])
                return false;
            assignment[i / 2] = comp[i] > comp[i + 1];
        }
        return true;
    }

    int convert_into_node(int a, bool na) {
        a = 2 * a ^ na;
        return a;
    }

    void add_disjunction(int a, bool na, int b, bool nb) {
        // Or clause  A or B
        // na and nb signify whether a and b are to be negated
        a = convert_into_node(a, na);
        b = convert_into_node(b, nb);
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        adj[neg_a].push_back(b);
        adj[neg_b].push_back(a);
        adj_t[b].push_back(neg_a);
        adj_t[a].push_back(neg_b);
    }
    void add_must_true(int a, bool na) {
        // must true
        add_disjunction(a, na, a, na);
    }
    void add_one_true(int a, bool na, int b, bool nb) {
        // X-or clause
        // A xor B
        // exactly one is true
        add_disjunction(a, na, b, !nb);
        add_disjunction(a, !na, b, nb);
    }

    void add_conjuction(int a, bool na, int b, bool nb) {
        // And clause
        // A and B
        // exactly two variable is true
        add_must_true(a, na);
        add_must_true(b, nb);
    }
};
