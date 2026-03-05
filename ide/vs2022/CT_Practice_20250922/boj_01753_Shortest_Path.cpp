// 2026-03-05 (¸ñ)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int v, e, k;
	cin >> v >> e >> k;

	vector<vector<pair<int, int>>> con_list(v + 1);
	vector<int> d(v + 1, 1e9);
	priority_queue<pair<int, int>, 
		vector<pair<int, int>>, greater<pair<int, int>>> pq;

	for (int i = 0; i < e; i++)
	{
		int dep, arr, dist;
		cin >> dep >> arr >> dist;

		con_list[dep].emplace_back(dist, arr);
	}

	pq.emplace(0, k);
	d[k] = 0;

	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();
		int cd = cur.first;
		int carr = cur.second;

		if (d[carr] < cd) continue;

		for (auto next : con_list[carr])
		{
			int nd = next.first;
			int narr = next.second;

			if (cd + nd >= d[narr]) continue;

			pq.emplace(cd + nd, narr);
			d[narr] = cd + nd;
		}
	}

	for (int i = 1; i <= v; i++)
	{
		if (d[i] == 1e9)
			cout << "INF" << '\n';
		else
			cout << d[i] << '\n';
	}
}