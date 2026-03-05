// 2026-03-04 (¼ö)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Find(int a);
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

	int v, e;
	cin >> v >> e;

	long long ans = 0;
	vector<Edge> edges;
	edges.reserve(e);
	parent.resize(v + 1);

	for (int i = 0; i < e; i++)
	{
		int dep, arr, dist;
		cin >> dep >> arr >> dist;
		edges.push_back(Edge(dist, dep, arr));
	}

	sort(edges.begin(), edges.end());
	
	for (int i = 1; i <= v; i++)
		parent[i] = i;

	int picked = 0;
	for (int i = 0; i < e; i++)
	{
		if (Union(edges[i].dep, edges[i].arr))
		{
			ans += edges[i].dist;
			picked++;
			if (picked == v - 1) break;
		}
	}

	cout << ans << '\n';
}

int Find(int a)
{
	if (a == parent[a]) return a;
	return parent[a] = Find(parent[a]);
}

bool Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return false;
	parent[b] = a;
	return true;
}