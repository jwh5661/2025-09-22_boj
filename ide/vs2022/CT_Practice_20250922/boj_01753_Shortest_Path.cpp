// 2026-04-10 (±Ý)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int dist, arr;

	Edge(int ndist, int narr)
		:dist(ndist), arr(narr) {
	};

	bool operator>(const Edge& other) const {
		return dist > other.dist;
	}
};

const int max_v = 20001;
const int INF = 1e9;
vector<Edge> adj_list[max_v];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int v, e, k;
	cin >> v >> e >> k;

	vector<int> total_dist(v + 1, INF);
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

	for (int i = 0; i < e; i++)
	{
		int dep, arr, dist;
		cin >> dep >> arr >> dist;

		adj_list[dep].emplace_back(dist, arr);
	}
	
	total_dist[k] = 0;
	pq.emplace(total_dist[k], k);

	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();
		
		if (cur.dist > total_dist[cur.arr]) continue;

		for (const auto& next : adj_list[cur.arr])
		{
			if (next.dist + cur.dist >= total_dist[next.arr]) continue;

			total_dist[next.arr] = next.dist + cur.dist;
			pq.emplace(cur.dist + next.dist, next.arr);
		}
	}

	for (int i = 1; i <= v; i++)
	{
		if (total_dist[i] != INF)
			cout << total_dist[i] << '\n';
		else
			cout << "INF" << '\n';
	}
}


// 2026-03-05 (¸ñ)

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int v, e, k;
// 	cin >> v >> e >> k;
// 
// 	vector<vector<pair<int, int>>> con_list(v + 1);
// 	vector<int> d(v + 1, 1e9);
// 	priority_queue<pair<int, int>, 
// 		vector<pair<int, int>>, greater<pair<int, int>>> pq;
// 
// 	for (int i = 0; i < e; i++)
// 	{
// 		int dep, arr, dist;
// 		cin >> dep >> arr >> dist;
// 
// 		con_list[dep].emplace_back(dist, arr);
// 	}
// 
// 	pq.emplace(0, k);
// 	d[k] = 0;
// 
// 	while (!pq.empty())
// 	{
// 		auto cur = pq.top(); pq.pop();
// 		int cd = cur.first;
// 		int carr = cur.second;
// 
// 		if (d[carr] < cd) continue;
// 
// 		for (auto next : con_list[carr])
// 		{
// 			int nd = next.first;
// 			int narr = next.second;
// 
// 			if (cd + nd >= d[narr]) continue;
// 
// 			pq.emplace(cd + nd, narr);
// 			d[narr] = cd + nd;
// 		}
// 	}
// 
// 	for (int i = 1; i <= v; i++)
// 	{
// 		if (d[i] == 1e9)
// 			cout << "INF" << '\n';
// 		else
// 			cout << d[i] << '\n';
// 	}
// }