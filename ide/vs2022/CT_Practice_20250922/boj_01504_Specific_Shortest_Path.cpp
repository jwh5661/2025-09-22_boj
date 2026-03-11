// 2026-03-11 (¼ö)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<long long> Dijkstra
(int start, int n, const vector<vector<pair<int, int>>>& con_list);

const int mx_dist = 1e9;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, e;
	cin >> n >> e;

	vector<vector<pair<int, int>>> con_list(n + 1);

	for (int i = 0; i < e; i++)
	{
		int dep, arr, dist;
		cin >> dep >> arr >> dist;

		con_list[dep].emplace_back(dist, arr);
		con_list[arr].emplace_back(dist, dep);
	}

	int v1, v2;
	cin >> v1 >> v2;

	vector<long long> p1, p2, p3;

	p1 = Dijkstra(1, n, con_list);
	p2 = Dijkstra(v1, n, con_list);
	p3 = Dijkstra(n, n, con_list);

	long long ans = min(p1[v1] + p2[v2] + p3[v2], p1[v2] + p2[v2] + p3[v1]);
	
	if (ans >= mx_dist) cout << -1 << '\n';
	else cout << ans << '\n';
}

vector<long long> Dijkstra(int start, int n, const vector<vector<pair<int, int>>>& con_list)
{
	vector<long long> d(n + 1, mx_dist);
	priority_queue
		<pair<long long, int>, vector<pair<long long, int>>,
		greater<pair<long long, int>>> pq;

	d[start] = 0;
	pq.emplace(0, start);

	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();
		long long cd = cur.first;
		int cnode = cur.second;

		if (cd > d[cnode]) continue;

		for (auto next : con_list[cnode])
		{
			long long nd = cd + next.first;
			int nnode = next.second;

			if (nd >= d[nnode]) continue;

			pq.emplace(nd, nnode);
			d[nnode] = nd;
		}
	}

	return d;
}