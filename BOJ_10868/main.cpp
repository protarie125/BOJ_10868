#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

constexpr auto INF = numeric_limits<ll>::max();

ll N, M;
ll sz;
vl dat;

void update(ll x, ll i) {
	auto idx = i + sz - 1;
	dat[idx] = x;

	while (0 < idx) {
		idx = (idx - 1) / 2;
		dat[idx] = min(dat[idx * 2 + 1], dat[idx * 2 + 2]);
	}
}

ll queryPart(ll a, ll b, ll key, ll l, ll r) {
	if (b <= l || r <= a) {
		return INF;
	}

	if (a <= l && r <= b) {
		return dat[key];
	}

	const auto m = (l + r) / 2;
	const auto v1 = queryPart(a, b, key * 2 + 1, l, m);
	const auto v2 = queryPart(a, b, key * 2 + 2, m, r);
	return min(v1, v2);
}

ll query(ll a, ll b) {
	return queryPart(a, b, 0, 0, sz);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N >> M;
	sz = 1;
	while (sz < N) {
		sz *= 2;
	}

	dat = vl(2 * sz - 1, INF);

	for (auto i = 0LL; i < N; ++i) {
		ll x;
		cin >> x;
		update(x, i);
	}

	for (auto i = 0LL; i < M; ++i) {
		ll a, b;
		cin >> a >> b;
		cout << query(a - 1, b) << '\n';
	}

	return 0;
}