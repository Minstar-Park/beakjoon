#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
using ll = long long;

ll pw(ll x, ll p){
	ll ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		ll t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		ll k = -(x[i] - t) * pw(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}

int get_nth(vector<int> rec, vector<int> dp, ll n){
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	ll ret = 0;
	for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}

int guess_nth_term(vector<int> x, ll n){
	if(n < x.size()) return x[n];
	vector<int> v = berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v, x, n);
}

using matrix = vector<vector<ll>>;

matrix operator * (const matrix &a, const matrix &b){
	matrix ret(a.size(), vector<ll>(b[0].size()));
	for(int i=0; i<a.size(); i++){
		for(int j=0; j<b[0].size(); j++){
			for(int k=0; k<b.size(); k++){
				ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % mod;
			}
		}
	}
	return ret;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;
	matrix arr(N, vector<ll>(N)), tmp(N, vector<ll>(N)), res(N, vector<ll>(N));
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
			cin >> arr[i][j];
		}
		tmp[i][i] = 1;
    }
	
	vector<int> v = {0};
	for(int c=1; c<300; c++){
		res = tmp * arr;
		ll t = 0;
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				t = (t + res[i][j]) % mod;
			}
		}
		v.push_back(t);
		tmp = res;
	}
	cout << guess_nth_term(v, K) << '\n';

	return 0;
}