struct dsu {
	vector<int> ds, wt;
	dsu(int n) {
		ds.assign(n, -1);
		wt.assign(n, INT_MAX);
	}
	int find(int i) {
		return ds[i] < 0 ? i : find(ds[i]);
	}
	void merge(int i, int j, int weight) {
		i = find(i), j = find(j);
		if (i != j) {
			if (ds[i] > ds[j])
				swap(i, j);
			ds[i] += ds[j], ds[j] = i; // a type of implementation that not need extra space for keep the size of each tree.
			wt[j] = weight; // weight is means time/how many when the merge operation is done.
// store time when it first loses itself as root means it is now under a tree that root is not itself.
		}
	}
	// find first same parent of i and j
	int weight(int i, int j) {
		int w = 0;

		while (i != j) {
			if (wt[i] < wt[j])
				w = wt[i], i = ds[i];
			else
				w = wt[j], j = ds[j];
		}
		return w;
	}

	// complexity is O(logN). faster than set implementation(heavy light technique) which complexity is O((logN)^2)
};
