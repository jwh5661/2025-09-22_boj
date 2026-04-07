// 2026-04-07 (ȭ)

#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	int dep, arr;
	long long cost;

	Edge(int ndep, int narr, long long ncost)
		:dep(ndep), arr(narr), cost(ncost) {
	}

};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<Edge> edges;
	edges.reserve(m);
	vector<long long> dist(n + 1, 1e9);

	for (int i = 0; i < m; i++)
	{
		int dep, arr;
		long long cost;
		cin >> dep >> arr >> cost;

		edges.emplace_back(dep, arr, cost);
	}

	dist[1] = 0;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			auto cur = edges[j];

			if (dist[cur.dep] != 1e9 && dist[cur.arr] > dist[cur.dep] + cur.cost)
				dist[cur.arr] = dist[cur.dep] + cur.cost;
		}
	}

	for (int j = 0; j < m; j++)
	{
		auto cur = edges[j];

		if (dist[cur.dep] != 1e9 && dist[cur.arr] > dist[cur.dep] + cur.cost)
		{
			cout << -1 << '\n';
			return 0;
		}
	}

	for (int i = 2; i <= n; i++)
		cout << (dist[i] == 1e9 ? -1 : dist[i]) << '\n';
}