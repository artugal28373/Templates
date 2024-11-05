const ld PI = acos(-1.0);
 
bool bit(int mask, int i) {
	return (mask >> i) & 1;
}
 
struct cd {
	ld x, y;
 
	cd() : x(0), y(0) {}
 
	cd(ld x, ld y) : x(x), y(y) {}
 
	cd(ld z) : x(z), y(0) {}
 
	cd& operator *= (const cd& z) {
		tie(x, y) = mp(x * z.x - y * z.y, x * z.y + y * z.x);
		return *this;
	}
 
	cd operator * (const cd& z) const {
		cd tmp = z;
		tmp *= *this;
		return tmp;
	}
 
	cd& operator /= (const ld& z) {
		x /= z;
		y /= z;
		return *this;
	}
 
	cd& operator += (const cd& z) {
		x += z.x;
		y += z.y;
		return *this;
	}
 
	cd operator + (const cd& z) const {
		cd tmp = z;
		tmp += *this;
		return tmp;
	}
 
	cd operator - (const cd& z) const {
		return cd(x - z.x, y - z.y);
	}
 
	ld real() const {
		return x;
	}
 
	ld imag() const {
		return y;
	}
};
 
cd conj(const cd& z) {
	return cd(z.real(), -z.imag());
}
 
namespace FFT {
	const int B = 12;
	const int N = 1 << B;
 
	cd roots[N];
	int inv[N];
 
	cd get_root(int k, int n) {
		return roots[k * (N / n)];
	}
 
	void precalc() {
		forn(i, N) {
			ld ang = 2 * PI * i / N;
			roots[i] = cd(cos(ang), sin(ang));
		}
	}
 
	void precalc_inv(int n) {
		int b = 0;
		while ((1 << b) < n) ++b;
		assert((1 << b) == n);
		assert(b <= B);
 
		inv[0] = 0;
		int hb = -1;
		for (int i = 1; i < n; ++i) {
			if  (bit(i, hb + 1)) {
				++hb;
			}
			inv[i] = inv[i ^ (1 << hb)] ^ (1 << (b - hb - 1));
		}
	}
 
	void fft(vector<cd>& a, bool rev) {
		forn(i, sz(a)) {
			if  (i < inv[i]) {
				swap(a[i], a[inv[i]]);
			}
		}
 
		for (int len = 1; len * 2 <= sz(a); len *= 2) {
			for (int i = 0; i < sz(a); i += len * 2) {
				forn(j, len) {
					cd x = a[i + j];
					cd y = a[i + len + j];
					cd r = get_root(j, len * 2);
					if  (rev) {
						r = conj(r);
					}
					a[i + j] = x + r * y;
					a[i + len + j] = x - r * y;
					if  (rev) {
						a[i + j] /= 2;
						a[i + len + j] /= 2;
					}
				}
			}
		}
	}
 
	void fft_2d(vector<vector<cd>>& a, bool rev) {
		precalc_inv(sz(a[0]));
		for (auto& row : a) {
			fft(row, rev);
		}
		precalc_inv(sz(a));
		forn(j, sz(a.front())) {
			vector<cd> col;
			forn(i, sz(a)) {
				col.pb(a[i][j]);
			}
			fft(col, rev);
			forn(i, sz(a)) {
				a[i][j] = col[i];
			}
		}
	}
	
	vector<vector<cd>> mult(vector<vector<cd>> x, vector<vector<cd>> y) {
		int b_rows = 0;
		while ((1 << b_rows) <= max(sz(x), sz(y))) ++b_rows;
		++b_rows;
 
		int b_cols = 0;
		while ((1 << b_cols) <= max(sz(x.front()), sz(y.front()))) ++b_cols;
		++b_cols;
 
		x.resize(1 << b_rows);
		y.resize(1 << b_rows);
		for (auto& row : x) {
			row.resize(1 << b_cols, 0);
		}
		for (auto& row : y) {
			row.resize(1 << b_cols, 0);
		}
 
		fft_2d(x, 0);
		fft_2d(y, 0);
 
		forn(i, sz(x)) forn(j, sz(x[i])) {
			x[i][j] *= y[i][j];
		}
 
		fft_2d(x, 1);
 
		return x;
	}
 
	vector<vector<cd>> brut_mult(vector<vector<cd>> x, vector<vector<cd>> y) {
		vector<vector<cd>> res(sz(x) + sz(y));
		forn(i, sz(res)) {
			res[i].resize(sz(x.front()) + sz(y.front()));
		}
		forn(i, sz(x)) forn(j, sz(x[i])) forn(ii, sz(y)) forn(jj, sz(y[ii])) {
			res.at(i + ii).at(j + jj) += x[i][j] * y[ii][jj];
		}
		return res;
	}
};
