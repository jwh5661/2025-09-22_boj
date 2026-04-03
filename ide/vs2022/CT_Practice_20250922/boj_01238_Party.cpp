// 2026-04-03 (±Ý)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> Dijkstra(vector<vector<pair<int, int>>>& con_list);

int n, m, x;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m >> x;

	vector<vector<pair<int, int>>> con_list(n + 1);
	vector<vector<pair<int, int>>> rcon_list(n + 1);

	for (int i = 0; i < m; i++)
	{
		int dep, arr, cost;
		cin >> dep >> arr >> cost;

		con_list[dep].emplace_back(cost, arr);
		rcon_list[arr].emplace_back(cost, dep);
	}

	vector<int> result1 = Dijkstra(con_list);
	vector<int> result2 = Dijkstra(rcon_list);

	int ans = -1;
	for (int i = 1; i <= n; i++)
	{
		result1[i] += result2[i];

		ans = max(result1[i], ans);
	}
	
	cout << ans << '\n';
}

vector<int> Dijkstra(vector<vector<pair<int, int>>>& con_list)
{
	vector<int> visited(n + 1, 1e9);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	visited[x] = 0;
	pq.emplace(visited[x], x);

	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();
		int cost = cur.first;
		int village = cur.second;

		if (cost > visited[village]) continue;

		for (auto next : con_list[village])
		{
			int ncost = cost + next.first;
			int nvillage = next.second;

			if (ncost >= visited[nvillage]) continue;

			pq.emplace(ncost, nvillage);
			visited[nvillage] = ncost;
		}
	}

	return visited;
}