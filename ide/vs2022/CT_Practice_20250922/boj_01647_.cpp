// 2026-03-09 (¿ù)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Find(int x);
bool Union(int a, int b);

vector<int> parent;

struct Edge {
	int dist, dep, arr;

	Edge(int ndist, int ndep, int narr)
		:dist(ndist), dep(ndep), arr(narr) {
	}

	bool operator<(const Edge& other) const {
		return dist < other.dist;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, ans = 0 ;
	cin >> n >> m;

	vector<Edge> edges;
	edges.reserve(m);
	parent.resize(n + 1);

	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		int dep, arr, dist;
		cin >> dep >> arr >> dist;

		edges.emplace_back(dist, dep, arr);
	}

	sort(edges.begin(), edges.end());

	int picked = 0;
	for(int i = 0; i < m; i++)
	{
		if (picked == n - 2) break;

		if (Union(edges[i].dep, edges[i].arr))
		{
			ans += edges[i].dist;
			picked++;
		}
	}

	cout << ans << '\n';
}

int Find(int x)
{
	if (x == parent[x]) return x;
	return parent[x] = Find(parent[x]);
}

bool Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return false;
	parent[b] = a;
	return true;
}