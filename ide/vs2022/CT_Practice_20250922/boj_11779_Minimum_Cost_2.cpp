// 2026-04-02 (¸ñ)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> con_list(n + 1);
	vector<int> visited(n + 1, 1e9);
	vector<int> parent(n + 1, -1);
	vector<int> path;
	path.reserve(n);
	priority_queue<pair<int ,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	for (int i = 0; i < m; i++)
	{
		int dep, arr, cost;
		cin >> dep >> arr >> cost;

		con_list[dep].emplace_back(cost, arr);
	}

	int start, end;
	cin >> start >> end;

	pq.emplace(0, start);
	visited[start] = 0;

	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();
		int cost = cur.first;
		int city = cur.second;

		if (city == end) break;

		if (visited[city] < cost) continue;

		for (auto next : con_list[city])
		{
			int ncost = cost + next.first;
			int ncity = next.second;

			if (visited[ncity] <= ncost) continue;

			pq.emplace(ncost, ncity);
			visited[ncity] = ncost;
			parent[ncity] = city;
		}
	}

	int i = end;
	while (i != -1)
	{
		path.push_back(i);
		i = parent[i];
	}

	reverse(path.begin(), path.end());

	cout << visited[end] << '\n';
	cout << path.size() << '\n';
	for (int p : path)
		cout << p << ' ';
	cout << '\n';
}