// 2026-03-07 (≈‰)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	const int mx_cost = 1e9;

	vector<vector<pair<int, int>>> con_list(n + 1);
	vector<int> cost(n + 1, mx_cost);
	priority_queue<pair<int, int>, vector<pair<int, int>>, 
		greater<pair<int, int>>> q;

	for (int i = 0; i < m; i++)
	{
		int dep, arr, c;
		cin >> dep >> arr >> c;

		con_list[dep].emplace_back(c, arr);
	}

	int start, end;
	cin >> start >> end;

	q.emplace(0, start);
	cost[start] = 0;

	while (!q.empty())
	{
		auto cur = q.top(); q.pop();
		int cur_cost = cur.first;
		int cur_node = cur.second;

		if (cur_cost > cost[cur_node]) continue;

		if (cur_node == end) break;

		for (auto next : con_list[cur_node])
		{
			int n_cost = cur_cost + next.first;
			int n_node = next.second;

			if (n_cost >= cost[n_node]) continue;

			q.emplace(n_cost, n_node);
			cost[n_node] = n_cost;
		}
	}

	cout << cost[end] << '\n';
}