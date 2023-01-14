struct segtree {
	vector<int> tr; int n;
	segtree(vector<int> v) {
		n = v.size();
		tr.resize(n * 2);
		for (int i = 0; i < n; i++)
			tr[n + i] = v[i];
		for (int i = n - 1; i > 0; i--)
			pull(i);
	}
	void pull(int i) {
		tr[i] = max(tr[i * 2], tr[i * 2 + 1]);
	}
	int query(int l, int r) {
		int x = 0;
		
		for (l += n, r += n; l <= r; l /= 2, r /= 2) {
			if (l & 1)
				x = max(x, tr[l++]);
			if (~r & 1)
				x = max(x, tr[r--]);
		}
		return x;
	}
};
