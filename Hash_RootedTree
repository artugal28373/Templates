ll b[2] = {179, 191};
ll mod[2] = {916969619, 999999937};
vi pw[2];
 
vi siz;
vector<pll> myHash;
 
void calc(int u, int f = -1) {
	siz[u] = 1;
	vector<pair<pll, int>> subs;
 
	for (int v : g[u]) if (v != f) {
		calc(v, u);
		subs.pb({myHash[v], v});
		siz[u] += siz[v];
	}
 
	sort(all(subs));
 
	myHash[u] = {1, 1};
	for (auto [h, v] : subs) {
		myHash[u].fi *= pw[0][siz[v] + siz[v]];
		myHash[u].fi %= mod[0];
		myHash[u].fi += h.fi;
		if (myHash[u].fi >= mod[0]) myHash[u].fi -= mod[0];
 
		myHash[u].se *= pw[1][siz[v] + siz[v]];
		myHash[u].se %= mod[1];
		myHash[u].se += h.se;
		if (myHash[u].se >= mod[1]) myHash[u].se -= mod[1];
	}
 
	myHash[u].fi <<= 1;
	if (myHash[u].fi >= mod[0]) myHash[u].fi -= mod[0];
	myHash[u].fi += 2;
	if (myHash[u].fi >= mod[0]) myHash[u].fi -= mod[0];
 
	myHash[u].se <<= 1;
	if (myHash[u].se >= mod[1]) myHash[u].se -= mod[1];
	myHash[u].se += 2;
	if (myHash[u].se >= mod[1]) myHash[u].se -= mod[1];
 
	dd(u);
	dd(myHash[u]);
}
